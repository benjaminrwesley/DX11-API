#include "Mirror.h"
#include "Model.h"
#include "d3dUtil.h"
#include "GraphicObject_LitTexture.h"
#include "ShaderTextureLight.h"
#include "Texture.h"

Mirror::Mirror(ID3D11Device* dev, GraphicObject_LitTexture* pObj)
{
	NumReflectedObjs = 0;
	ppReflectedObjs = nullptr;
	pObjMirror = pObj;
	// ***** Mirror Preliminaries ************

	HRESULT hr = S_OK;

	D3D11_DEPTH_STENCIL_DESC mirrorDesc;
	ZeroMemory(&mirrorDesc, sizeof(mirrorDesc));
	mirrorDesc.DepthEnable = true;								// Use the depth test
	mirrorDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;	// but don't write to the depth buffer
	mirrorDesc.DepthFunc = D3D11_COMPARISON_LESS;
	mirrorDesc.StencilEnable = true;							// Use the stencil test
	mirrorDesc.StencilReadMask = 0xff;
	mirrorDesc.StencilWriteMask = 0xff;

	mirrorDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	mirrorDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	mirrorDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;		// When passing the test (Always) replace
	mirrorDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;	// the color value with the reference value (int 1)


	// Back faces are culled, so these don't matter 
	mirrorDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	mirrorDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	mirrorDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	mirrorDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = dev->CreateDepthStencilState(&mirrorDesc, &MarkMirrorDSS);
	assert(SUCCEEDED(hr));

	D3D11_DEPTH_STENCIL_DESC drawReflectionDesc;
	ZeroMemory(&drawReflectionDesc, sizeof(drawReflectionDesc));
	drawReflectionDesc.DepthEnable = true;								// Use the depth test
	drawReflectionDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;		// normally
	drawReflectionDesc.DepthFunc = D3D11_COMPARISON_LESS;
	drawReflectionDesc.StencilEnable = true;							// Use the stencil test
	drawReflectionDesc.StencilReadMask = 0xff;
	drawReflectionDesc.StencilWriteMask = 0xff;

	drawReflectionDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	drawReflectionDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	drawReflectionDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;		// When passing the stencil comparison test,
	drawReflectionDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// do not modify the stencil

	// Back faces are culled, so these don't matter
	drawReflectionDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	drawReflectionDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	drawReflectionDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	drawReflectionDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;

	hr = dev->CreateDepthStencilState(&drawReflectionDesc, &DrawReflectionDSS);
	assert(SUCCEEDED(hr));

	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;   // D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;
	rd.AntialiasedLineEnable = false;

	hr = dev->CreateRasterizerState(&rd, &MirrorFrontFaceAsClockWiseRS);
	assert(SUCCEEDED(hr));

	// These settings implement the standard alpha blending: c_src*(a_src) + c_dst*(1-a_src) 
	D3D11_BLEND_DESC bd;
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = dev->CreateBlendState(&bd, &TransparentBS);
	assert(SUCCEEDED(hr));

	// These setting prevent all writings to the render target 
	// (the key is that RenderTargetWriteMask = 0, so nothing is allowed)
	// see https://msdn.microsoft.com/en-us/library/windows/desktop/bb204901(v=vs.85).aspx
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;
	bd.RenderTarget[0].BlendEnable = false;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = 0;

	hr = dev->CreateBlendState(&bd, &NoWriteToRenderTargetBS);
	assert(SUCCEEDED(hr));

	// *********************************
}

void Mirror::SetReflectedObjs(GraphicObject_LitTexture** reflectedObjs, int numObjs)
{
	NumReflectedObjs = numObjs;
	ppReflectedObjs = new GraphicObject_LitTexture * [numObjs];
	for (int i = 0; i < numObjs; i++) {
		ppReflectedObjs[i] = reflectedObjs[i];
	}
}

Mirror::~Mirror()
{
	delete[] ppReflectedObjs;

	ReleaseAndDeleteCOMobject(MarkMirrorDSS);
	ReleaseAndDeleteCOMobject(DrawReflectionDSS);
	ReleaseAndDeleteCOMobject(MirrorFrontFaceAsClockWiseRS);
	ReleaseAndDeleteCOMobject(TransparentBS);
	ReleaseAndDeleteCOMobject(NoWriteToRenderTargetBS);
}


void Mirror::Render(ID3D11DeviceContext* context, ID3D11RasterizerState* pRasterizerState)
{
	SetMirrorStencil(context);
	RenderReflectedObjs(context);
	RenderMirror(context, pRasterizerState);
}

void Mirror::GenerateReflectionMat()
{
	// Create Reflection matrix for mirror plane.
	// Uses the mirror's normal N and position
	Vect N = pObjMirror->GetWorld().get(ROW_1); // Mirror normal
	Vect p = pObjMirror->GetWorld().get(ROW_3); // point on mirror
	float d = -p.dot(N);
	Matrix NTN(N[x] * N, N[y] * N, N[z] * N, d * N);  // Set the 4 rows
	NTN[m3] = 0;	// Zero out the #$#@$! 1 that's defaulted in the w position
	NTN[m7] = 0;
	NTN[m11] = 0;
	ReflectionMat = Matrix(IDENTITY) - 2 * NTN;
	ReflectionMat[m15] = 1; // correcting the corner entry
	// See also: https://en.wikipedia.org/wiki/Transformation_matrix
	// and http://ami.ektf.hu/uploads/papers/finalpdf/AMI_40_from175to186.pdf
	// And of course http://facweb.cs.depaul.edu/andre/GAM325/Week3.htm
}

void Mirror::SetMirrorStencil(ID3D11DeviceContext* context)
{
	// **** mirror effect ***** See also http://richardssoftware.net/Home/Post/18
	//Marking the mirror pixels
	// BLEND STATE: Stop writing to the render target 
	context->OMSetBlendState(NoWriteToRenderTargetBS, nullptr, 0xffffffff);
	// STENCIL: Set up the stencil for marking ('1' for all pixels that passed the depth test. See comment at line 35)
	context->OMSetDepthStencilState(MarkMirrorDSS, 1);

	// Render the mirror 
	pObjMirror->Render();

	// STENCIL: stop using the stencil
	context->OMSetDepthStencilState(0, 0);
	// BLEND STATE: Return the blend state to normal (writing to render target)
	context->OMSetBlendState(0, nullptr, 0xffffffff);
}

void Mirror::RenderReflectedObjs(ID3D11DeviceContext* context)
{
	// Render objects (to render target) that should be reflected in the mirror
// WINDINGS: face winding will appear inside out after reflection. Switching to CW front facing
	context->RSSetState(MirrorFrontFaceAsClockWiseRS);

	// STENCIL: Use the stencil test (reference value 1) and only pass the test if the stencil already had a one present
	context->OMSetDepthStencilState(DrawReflectionDSS, 1);

	for (int i = 0; i < NumReflectedObjs; i++) {
		ShaderTextureLight* pObjShader = ppReflectedObjs[i]->GetShader();
		pObjShader->SetToContext(context);

		Data_LightParams prevParams = pObjShader->GetLightParameters();
		Data_LightParams reflectedParams = prevParams;

		reflectedParams.DirLight.Direction.W() = 0;
		reflectedParams.DirLight.Direction *= ReflectionMat;

		for (int i = 0; i < NUMPOINTS; i++) {
			reflectedParams.PntLight[i].Position *= ReflectionMat;
		}

		for (int i = 0; i < NUMSPOTS; i++) {
			reflectedParams.SptLight[i].Position *= ReflectionMat;

			reflectedParams.SptLight[i].Direction.W() = 0;
			reflectedParams.SptLight[i].Direction *= ReflectionMat;
		}

		reflectedParams.EyePosWorld *= ReflectionMat;

		Matrix prevWorld = ppReflectedObjs[i]->GetWorld();
		Matrix reflectedWorld = prevWorld * ReflectionMat;

		ppReflectedObjs[i]->SetWorld(reflectedWorld);
		pObjShader->SetLightParameters(reflectedParams);
		pObjShader->SendLightParameters();

		ppReflectedObjs[i]->Render();

		ppReflectedObjs[i]->SetWorld(prevWorld);
		pObjShader->SetLightParameters(prevParams);
		pObjShader->SendLightParameters();
	}
}

void Mirror::RenderMirror(ID3D11DeviceContext* context, ID3D11RasterizerState* pRasterizerState)
{
	// STENCIL: Stop using the stencil
	context->OMSetDepthStencilState(0, 0);
	// WINDING: back to normal windings
	context->RSSetState(pRasterizerState);

	// Render the mirror again, using alpha blending to 'see' the reflection 'through' it
	context->OMSetBlendState(TransparentBS, nullptr, 0xffffffff);

	pObjMirror->Render();

	// BLENDING: Back to normal blending (turn off transparent blending)
	context->OMSetBlendState(0, nullptr, 0xffffffff);
}
