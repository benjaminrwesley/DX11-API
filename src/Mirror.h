// Mirror.h

#ifndef _Mirror
#define _Mirror

#include <d3d11.h>
#include "d3dUtil.h"
#include "Vect.h"
#include "Matrix.h"
class GraphicObject_LitTexture;
struct ID3D11DeviceContext;
struct ID3D11Device;
class Texture;
class ShaderTextureLight;

class Mirror
{
private:
	GraphicObject_LitTexture* pObjMirror;
	GraphicObject_LitTexture** ppReflectedObjs;

	ID3D11DepthStencilState* MarkMirrorDSS;
	ID3D11DepthStencilState* DrawReflectionDSS;

	ID3D11RasterizerState* MirrorFrontFaceAsClockWiseRS;

	ID3D11BlendState* NoWriteToRenderTargetBS;
	ID3D11BlendState* TransparentBS;

	Matrix ReflectionMat;
	void SetMirrorStencil(ID3D11DeviceContext* context);
	void RenderReflectedObjs(ID3D11DeviceContext* context);
	void RenderMirror(ID3D11DeviceContext* context, ID3D11RasterizerState* pRasterizerState);


	int NumReflectedObjs;

public:
	Mirror(const Mirror&) = delete;				// Copy constructor
	Mirror(Mirror&&) = delete;                    // Move constructor
	Mirror& operator=(const Mirror&) & = delete;  // Copy assignment operator
	Mirror& operator=(Mirror&&) & = delete;       // Move assignment operator
	~Mirror();

	Mirror(ID3D11Device* dev, GraphicObject_LitTexture* pObj);

	void SetReflectedObjs(GraphicObject_LitTexture* reflectedObjs[], int numObjs);

	void GenerateReflectionMat();

	void Render(ID3D11DeviceContext* context, ID3D11RasterizerState* pRasterizerState);
};

#endif _Mirror
