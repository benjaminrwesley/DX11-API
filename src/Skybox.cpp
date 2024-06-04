#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"

SkyBox::SkyBox(ID3D11Device* dev, float len)
{
	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	int vind = 0;
	int tind = 0;

	// Top
	pVerts[vind].set(0.5f * len, 0.5f * len, 0.5f * len, 0.5f, 0.0f);
	pVerts[vind + 1].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.25f, 0.0f);
	pVerts[vind + 2].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.25f, 0.333f);
	pVerts[vind + 3].set(0.5f * len, 0.5f * len, -0.5f * len, 0.5f, 0.333f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * len, -0.5f * len, -0.5f * len, 0.5f, 0.666f);
	pVerts[vind + 1].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.25f, 0.666f);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, 0.5f * len, 0.25f, 1.0f);
	pVerts[vind + 3].set(0.5f * len, -0.5f * len, 0.5f * len, 0.5f, 1.0f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Front
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * len, 0.5f * len, 0.5f * len, 0.75f, 0.333f);
	pVerts[vind + 1].set(-0.5f * len, 0.5f * len, 0.5f * len, 1.0f, 0.333f);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, 0.5f * len, 1.0f, 0.666f);
	pVerts[vind + 3].set(0.5f * len, -0.5f * len, 0.5f * len, 0.75f, 0.666f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * len, 0.5f * len, -0.5f * len, 0.5f, 0.333f);
	pVerts[vind + 1].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.25f, 0.333f);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.25f, 0.666f);
	pVerts[vind + 3].set(0.5f * len, -0.5f * len, -0.5f * len, 0.5f, 0.666f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	//Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * len, 0.5f * len, 0.5f * len, 0.75f, 0.333f);
	pVerts[vind + 1].set(0.5f * len, 0.5f * len, -0.5f * len, 0.5f, 0.333f);
	pVerts[vind + 2].set(0.5f * len, -0.5f * len, -0.5f * len, 0.5f, 0.666f);
	pVerts[vind + 3].set(0.5f * len, -0.5f * len, 0.5f * len, 0.75f, 0.666f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.25f, 0.333f);
	pVerts[vind + 1].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.0f, 0.333f);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, 0.5f * len, 0.0f, 0.666f);
	pVerts[vind + 3].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.25f, 0.666f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pPlane = new Model(dev, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

Model* SkyBox::GetModel()
{
	return pPlane;
}

SkyBox::~SkyBox()
{
	delete pPlane;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	pPlane->SetToContext(context);
	pPlane->Render(context);
}