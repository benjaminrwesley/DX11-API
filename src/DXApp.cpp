#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_LitTexture.h"
#include "GraphicObject_Texture.h"
#include "GraphicObject_Color.h"
#include "Mirror.h"
#include "Skybox.h"

void DXApp::InitDemo()
{
	pShaderTexLight = new ShaderTextureLight(md3dDevice);
	pShaderTexLight->SetDirectionalLightParameters(Vect(-1, -25, 1).getNorm(), .25 * Vect(1, 1, 1), .25 * Vect(1, 1, 1), .25 * Vect(1, 1, 1));

	pShaderTex = new ShaderTexture(md3dDevice);
	pShaderColor = new ShaderColor(md3dDevice);

	pTexWater = new Texture(md3dDevice, L"../Assets/Textures/Water.tga");
	pTexSnow = new Texture(md3dDevice, L"../Assets/Textures/Snow.tga");
	pTexSkyBox = new Texture(md3dDevice, L"../Assets/Textures/NightSkyBox.tga", D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT);
	pTexPenguin = new Texture(md3dDevice, L"../Assets/Textures/Penguin.tga");
	pTexCrate = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga");
	pTexShip = new Texture(md3dDevice, L"../Assets/Textures/Ship.tga");
	pTexCabin1 = new Texture(md3dDevice, L"../Assets/Textures/Cabin1.tga");
	pTexCabin2 = new Texture(md3dDevice, L"../Assets/Textures/Cabin2.tga");
	pTexIceBrick = new Texture(md3dDevice, L"../Assets/Textures/IceBrick.tga");

	// Mirror object
	pTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/TerrainHeight.tga", 500, 7.5f, 0, 30, 30);
	pPlane = new FlatPlane(md3dDevice, 500, 3, 3);
	pSkybox = new SkyBox(md3dDevice, 500);
	pPenguin = new Model(md3dDevice, "../Assets/Models/Penguin.azul");
	pShip = new Model(md3dDevice, "../Assets/Models/Ship.azul");
	pSphere = new Model(md3dDevice, Model::PreMadeModels::UnitSphere);
	pCube = new Model(md3dDevice, Model::PreMadeModels::UnitBoxRepeatedTexture);
	pCabin = new Model(md3dDevice, "../Assets/Models/Cabin.azul");
	pPyramid = new Model(md3dDevice, Model::PreMadeModels::UnitPyramidRepeatedTexture);

	mMirror = Matrix(TRANS, 0, 0.1, 0);
	mTerrain = Matrix(IDENTITY);
	mShip = Matrix(ROT_Y, -0.12f) * Matrix(TRANS, 56, -0.5f, -55);
	mPenguin1 = Matrix(ROT_Y, 1.75f) * Matrix(TRANS, 2, 7.28f, -27.5f);
	mPenguin2 = Matrix(ROT_Y, 1.25f) * Matrix(TRANS, 3, 6.8f, -29);
	mShipPoint1 = Matrix(SCALE, 0.125f, 0.125f, 0.125f) * Matrix(ROT_Y, -0.12f) * Matrix(TRANS, 53, 4.62f, -47);
	mShipPoint2 = Matrix(SCALE, 0.125f, 0.125f, 0.125f) * Matrix(ROT_Y, -0.12f) * Matrix(TRANS, 57.275f, 4.62f, -46.5f);
	mSkyBox = Matrix(TRANS, 0, -30, 0);
	mCrate1 = Matrix(ROT_Y, 1) * Matrix(TRANS, 59, 1.15f, -37);
	mCrate2 = Matrix(ROT_Y, .8f) * Matrix(TRANS, 58.25, 0.9f, -38);
	mCrate3 = Matrix(ROT_X, -0.1f) * Matrix(TRANS, 58.5f, 1.05f, -36);
	mCabin = Matrix(ROT_Y, 1.75f) * Matrix(TRANS, 0, 7.15f, -24);
	mCabinPoint = Matrix(SCALE, 0.1f, 0.1f, 0.1f) * Matrix(ROT_Y, 1.75f) * Matrix(TRANS, 2.425f, 10, -24.425f);
	mIcePyramid = Matrix(ROT_Y, -0.25f) * Matrix(ROT_Z, 0.5f) * Matrix(TRANS, -4, 7.75f, -20.5f);

	vCabinPointPos = mCabinPoint.get(MatrixRowType::ROW_3);

	GraphObjTerrain = new GraphicObject_LitTexture(pShaderTexLight, pTerrain->GetModel());
	GraphObjTerrain->SetTexture(pTexSnow);
	GraphObjTerrain->SetWorld(mTerrain);
	GraphObjTerrain->SetMat(Vect(1, 1, 1), Vect(1, 1, 1), Vect(1, 1, 1));

	GraphObjMirror = new GraphicObject_LitTexture(pShaderTexLight, pPlane->GetModel());
	GraphObjMirror->SetTexture(pTexWater);
	GraphObjMirror->SetWorld(mMirror);
	GraphObjMirror->SetMat(Vect(1, 1, 1, 0.175f), Vect(1, 1, 1, 0.01f), Vect(1, 1, 1, 0.01f));

	GraphObjPenguin1 = new GraphicObject_LitTexture(pShaderTexLight, pPenguin);
	GraphObjPenguin1->SetTexture(pTexPenguin);
	GraphObjPenguin1->SetWorld(mPenguin1);
	GraphObjPenguin1->SetMat(Vect(1, 1, 1, 1), 4 * Vect(1, 1, 1, 1), 4 * Vect(1, 1, 1, 1));

	GraphObjPenguin2 = new GraphicObject_LitTexture(pShaderTexLight, pPenguin);
	GraphObjPenguin2->SetTexture(pTexPenguin);
	GraphObjPenguin2->SetWorld(mPenguin2);
	GraphObjPenguin2->SetMat(Vect(1, 1, 1, 1), 2.5f * Vect(1, 1, 1, 1), 2.5f * Vect(1, 1, 1, 1));

	GraphObjShip = new GraphicObject_LitTexture(pShaderTexLight, pShip);
	GraphObjShip->SetTexture(pTexShip);
	GraphObjShip->SetWorld(mShip);
	GraphObjShip->SetMat(Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), Vect(1, 1, 1, 1));

	GraphObjCrate1 = new GraphicObject_LitTexture(pShaderTexLight, pCube);
	GraphObjCrate1->SetTexture(pTexCrate);
	GraphObjCrate1->SetWorld(mCrate1);
	GraphObjCrate1->SetMat(Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), Vect(1, 1, 1, 1));

	GraphObjCrate2 = new GraphicObject_LitTexture(pShaderTexLight, pCube);
	GraphObjCrate2->SetTexture(pTexCrate);
	GraphObjCrate2->SetWorld(mCrate2);
	GraphObjCrate2->SetMat(Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), Vect(1, 1, 1, 1));

	GraphObjCrate3 = new GraphicObject_LitTexture(pShaderTexLight, pCube);
	GraphObjCrate3->SetTexture(pTexCrate);
	GraphObjCrate3->SetWorld(mCrate3);
	GraphObjCrate3->SetMat(Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), Vect(1, 1, 1, 1));

	GraphObjCabin = new GraphicObject_LitTexture(pShaderTexLight, pCabin);
	GraphObjCabin->SetTexture(pTexCabin1, 0);
	GraphObjCabin->SetTexture(pTexCabin2, 1);
	GraphObjCabin->SetWorld(mCabin);
	GraphObjCabin->SetMat(Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), 0);
	GraphObjCabin->SetMat(Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), Vect(1, 1, 1, 1), 1);

	GraphObjPyramid = new GraphicObject_LitTexture(pShaderTexLight, pPyramid);
	GraphObjPyramid->SetTexture(pTexIceBrick);
	GraphObjPyramid->SetWorld(mIcePyramid);
	GraphObjPyramid->SetMat(Vect(1, 1, 1, 1), 2 * Vect(1, 1, 1, 1), 2 * Vect(1, 1, 1, 1));

	GraphObjShipLight1 = new GraphicObject_Color(pShaderColor, pSphere);
	GraphObjShipLight1->SetColor(Colors::White);
	GraphObjShipLight1->SetWorld(mShipPoint1);

	GraphObjShipLight2 = new GraphicObject_Color(pShaderColor, pSphere);
	GraphObjShipLight2->SetColor(Colors::White);
	GraphObjShipLight2->SetWorld(mShipPoint1);

	GraphObjCabinLight = new GraphicObject_Color(pShaderColor, pSphere);
	GraphObjCabinLight->SetColor(Colors::White);
	GraphObjCabinLight->SetWorld(mCabinPoint);

	GraphObjSkybox = new GraphicObject_Texture(pShaderTex, pSkybox->GetModel());
	GraphObjSkybox->SetTexture(pTexSkyBox);
	GraphObjSkybox->SetWorld(mSkyBox);

	GraphicObject_LitTexture* reflectedObjs[] = { GraphObjCabin, GraphObjCrate1, GraphObjCrate2, GraphObjCrate3, GraphObjTerrain, GraphObjShip, GraphObjPenguin1, GraphObjPenguin2, GraphObjPyramid };

	pMirror = new Mirror(md3dDevice, GraphObjMirror);
	pMirror->GenerateReflectionMat();
	pMirror->SetReflectedObjs(reflectedObjs, 9);

	// Initialize the projection matrix
	mCam.setPerspective(3.14159 / 3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(39, 3, -30.5f));
	mCam.TurnLeftRight(3.415f);
	mCam.TiltUpDown(.15f);

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	mShipMove = mShip * Matrix(TRANS, 0.1f * cosf(mTimer.TotalTime()), 0.3f * cosf(mTimer.TotalTime()), 0.2f * cosf(mTimer.TotalTime()));

	mShipPoint1Move = mShipPoint1 * Matrix(TRANS, 0.1f * cosf(mTimer.TotalTime()), 0.3f * cosf(mTimer.TotalTime()), 0.2f * cosf(mTimer.TotalTime()));
	vShipPoint1MovePos = mShipPoint1Move.get(MatrixRowType::ROW_3);

	mShipPoint2Move = mShipPoint2 * Matrix(TRANS, 0.1f * cosf(mTimer.TotalTime()), 0.3f * cosf(mTimer.TotalTime()), 0.2f * cosf(mTimer.TotalTime()));
	vShipPoint2MovePos = mShipPoint2Move.get(MatrixRowType::ROW_3);

	mPenguin1 = Matrix(ROT_Y, 1 * (sinf(mTimer.TotalTime() * 3.75f))) * Matrix(TRANS, 2, 7.28f, -27.5f);
	mPenguin2 = Matrix(ROT_Y, 1.25f) * Matrix(ROT_X, 0.25f * (sinf(mTimer.TotalTime() * 3.4f))) * Matrix(TRANS, 3, 6.8f, -29);

	float camSpeed = 0.2f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.025f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	// Clear the back buffer
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	// Clear the depth stencil;
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Render Using Lit Texture Shader
	pShaderTexLight->SetToContext(md3dImmediateContext);
	pShaderTexLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTexLight->SendFog(1.0f, 125.0f, Colors::Black);
	//pShaderTexLight->SendFog();

	pShaderTexLight->SetPointLightParameters(vShipPoint1MovePos, 50000, .475f * Vect(1,1,1), .1f * Vect(1, 0.984, 0.941), 1 * Vect(1, 0.984, 0.941), 0.5f * Vect(1, 0.984, 0.941), 0);
	pShaderTexLight->SetSpotLightParameters(vShipPoint1MovePos, 4000, 1 * Vect(1, 0, 0), Vect(-1, -3, 5).getNorm(), 50, .2 * Vect(1, 0.984, 0.941), 3 * Vect(1, 0.984, 0.941), 1 * Vect(1, 0.984, 0.941), 0);

	pShaderTexLight->SetPointLightParameters(vShipPoint2MovePos, 50000, .475f * Vect(1, 1, 1), .1f * Vect(1, 0.984, 0.941), 1 * Vect(1, 0.984, 0.941), 0.5f * Vect(1, 0.984, 0.941), 1);
	pShaderTexLight->SetSpotLightParameters(vShipPoint2MovePos, 4000, 1 * Vect(1, 0, 0), Vect(0, -3, 5).getNorm(), 50, .2 * Vect(1, 0.984, 0.941), 3 * Vect(1, 0.984, 0.941), 1 * Vect(1, 0.984, 0.941),1);

	pShaderTexLight->SetPointLightParameters(vCabinPointPos, 50000, .5f * Vect(1, 1, 1), .1f * Vect(1, 0.984, 0.941), 2 * Vect(1, 0.984, 0.941), 1 * Vect(1, 0.984, 0.941), 2);

	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderTexLight->SendLightParameters(eyepos);

	//Render Objs
	GraphObjShip->SetWorld(mShipMove);
	GraphObjShip->Render();

	GraphObjPenguin1->SetWorld(mPenguin1);
	GraphObjPenguin1->Render();

	GraphObjPenguin2->SetWorld(mPenguin2);
	GraphObjPenguin2->Render();

	GraphObjCrate1->Render();
	GraphObjCrate2->Render();
	GraphObjCrate3->Render();
	GraphObjCabin->Render();
	GraphObjPyramid->Render();

	//Render mirror
	pMirror->Render(md3dImmediateContext, FrontFaceAsCCWRS);

	GraphObjTerrain->Render();

	//Render Using Unlit Texture Shader
	pShaderTex->SetToContext(md3dImmediateContext);
	pShaderTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	GraphObjSkybox->Render();

	//Render Using Unlit Color Shader
	pShaderColor->SetToContext(md3dImmediateContext);
	pShaderColor->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	GraphObjShipLight1->SetWorld(mShipPoint1Move);
	GraphObjShipLight1->Render();

	GraphObjShipLight1->SetWorld(mShipPoint2Move);
	GraphObjShipLight1->Render();

	GraphObjCabinLight->Render();

	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(SyncInterval, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	CHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pShaderTexLight;
	delete pShaderTex;
	delete pShaderColor;

	delete pMirror;

	delete GraphObjSkybox;
	delete GraphObjMirror;
	delete GraphObjTerrain;
	delete GraphObjShip;
	delete GraphObjPenguin1;
	delete GraphObjPenguin2;
	delete GraphObjShipLight1;
	delete GraphObjShipLight2;
	delete GraphObjCrate1;
	delete GraphObjCrate2;
	delete GraphObjCrate3;
	delete GraphObjCabin;
	delete GraphObjCabinLight;
	delete GraphObjPyramid;

	delete pSkybox;
	delete pTerrain;
	delete pPlane;
	delete pShip;
	delete pPenguin;
	delete pSphere;
	delete pCube;
	delete pCabin;
	delete pPyramid;

	delete pTexWater;
	delete pTexSnow;
	delete pTexSkyBox;
	delete pTexShip;
	delete pTexPenguin;
	delete pTexCrate;
	delete pTexCabin1;
	delete pTexCabin2;
	delete pTexIceBrick;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);
	ReleaseAndDeleteCOMobject(FrontFaceAsCCWRS);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));
	assert(SUCCEEDED(hr));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = false;

	//ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &FrontFaceAsCCWRS);

	md3dImmediateContext->RSSetState(FrontFaceAsCCWRS);
	//ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	UNREFERENCED_PARAMETER(delta);
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}