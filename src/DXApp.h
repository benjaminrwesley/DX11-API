// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderTextureLight.h"
#include "ShaderTexture.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class SkyBox;
class GraphicObject_LitTexture;
class GraphicObject_Texture;
class GraphicObject_Color;
class Mirror;

class DXApp : public Align16
{
private:
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;
	int SyncInterval = 1;  // 1 for sync to monitor refresh rate, 0 for no sync

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	ShaderTextureLight* pShaderTexLight;
	ShaderTexture* pShaderTex;
	ShaderColor* pShaderColor;

	Texture* pTexWater;
	Texture* pTexSnow;
	Texture* pTexSkyBox;
	Texture* pTexShip;
	Texture* pTexPenguin;
	Texture* pTexCrate;
	Texture* pTexCabin1;
	Texture* pTexCabin2;
	Texture* pTexIceBrick;

	Matrix mTerrain;
	Matrix mMirror;
	Matrix mSkyBox;

	Matrix mShip;
	Matrix mShipMove;

	Matrix mShipPoint1;
	Matrix mShipPoint1Move;
	Vect vShipPoint1MovePos;

	Matrix mShipPoint2;
	Matrix mShipPoint2Move;
	Vect vShipPoint2MovePos;

	Matrix  mCabinPoint;
	Vect vCabinPointPos;

	Matrix mPenguin1;
	Matrix mPenguin2;
	Matrix mCrate1;
	Matrix mCrate2;
	Matrix mCrate3;
	Matrix mCabin;
	Matrix mIcePyramid;

	TerrainModel* pTerrain;
	FlatPlane* pPlane;
	Model* pShip;
	Model* pPenguin;
	Model* pSphere;
	Model* pCube;
	Model* pCabin;
	Model* pPyramid;

	GraphicObject_LitTexture* GraphObjMirror;
	GraphicObject_LitTexture* GraphObjTerrain;
	GraphicObject_LitTexture* GraphObjShip;
	GraphicObject_LitTexture* GraphObjPenguin1;
	GraphicObject_LitTexture* GraphObjPenguin2;
	GraphicObject_LitTexture* GraphObjCrate1;
	GraphicObject_LitTexture* GraphObjCrate2;
	GraphicObject_LitTexture* GraphObjCrate3;
	GraphicObject_LitTexture* GraphObjCabin;
	GraphicObject_LitTexture* GraphObjPyramid;

	GraphicObject_Texture* GraphObjSkybox;

	GraphicObject_Color* GraphObjShipLight1;
	GraphicObject_Color* GraphObjShipLight2;
	GraphicObject_Color* GraphObjCabinLight;

	Mirror* pMirror;
	SkyBox* pSkybox;

	ID3D11RasterizerState* FrontFaceAsCCWRS;

public:
	DXApp(HWND hwnd);
	virtual ~DXApp();

	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp