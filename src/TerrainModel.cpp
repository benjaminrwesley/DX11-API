#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>

TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square

	int nverts = side * side; //n^2 verts
	StandardVertex* pVerts = new StandardVertex[nverts];

	int nfacePerSide = side - 1;
	int nface = (nfacePerSide) * (nfacePerSide);
	int ntri = nface * 2; //(n - 1)^2 * 2 tris
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float xStart = -0.5f;
	float xPos = -0.5f; //Start pos in top left
	float zPos = -0.5f;

	float xzOffset = 1.0f / (float)nfacePerSide;
	int vertIndex = 0;

	float uPos = 0.0f;
	float vPos = 0.0f;

	float uOffset = (float)RepeatU / (float)nfacePerSide;
	float vOffset = (float)RepeatV / (float)nfacePerSide;

	//Construct verts by looping from Top to Bottom / Left to Right 
	//Itterate Top to Bottom
	for (int y = 0; y < side; y++) {
		//Itterate Left to Right
		for (int x = 0; x < side; x++) {
			pVerts[vertIndex].set(xPos * len, GetVertHeight(hgtmap->pixels[TexelIndex(side, x, y)], maxheight) + ytrans, zPos * len, uPos, vPos, Colors::Black);
			xPos += xzOffset;
			uPos += uOffset;
			vertIndex++;
		}
		xPos = xStart;
		zPos += xzOffset;
		uPos = 0.0f;
		vPos += vOffset;
	}

	//Loop through verts that aren't edges
	vertIndex = 0;
	int edgeSide = side - 1;

	for (int y = 1; y < edgeSide; y++) {
		for (int x = 1; x < edgeSide; x++) {
			pVerts[VertIndex(side, x, y)].normal = CalculateNormal(pVerts, side, x, y);
		}
	}

	int topLeftIndex;
	int topRightIndex;
	int bottomLeftIndex;
	int bottomRightIndex;

	int triIndex = 0;
	vertIndex = 0;
	int indexAtEdge = nfacePerSide;

	//Construct tri list 
	for (int i = 0; i < nface; i++) {

		topLeftIndex = vertIndex;
		topRightIndex = vertIndex + 1;
		bottomLeftIndex = topLeftIndex + side;
		bottomRightIndex = topRightIndex + side;

		pTriList[triIndex].set(topRightIndex, topLeftIndex, bottomLeftIndex);
		triIndex++;
		pTriList[triIndex].set(topRightIndex, bottomLeftIndex, bottomRightIndex);
		triIndex++;

		vertIndex++;

		//Check if we should move down to next row if at edge
		if (vertIndex == indexAtEdge) {
			indexAtEdge += side;
			vertIndex++;
		}
	}

	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

Model* TerrainModel::GetModel()
{
	return pModTerrain;
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

int TerrainModel::TexelIndex(int sideLength, int x, int y) const
{
	return 4 * (y * sideLength + x);
}

int TerrainModel::VertIndex(int sideLength, int x, int y) const
{
	return (y * sideLength + x);
}

float TerrainModel::GetVertHeight(int h_val, float maxheight) const
{
	return (h_val / 255.0f) * maxheight;
}

Vect TerrainModel::CalculateNormal(StandardVertex* pVerts, int sideLength, int x, int y)
{
	Vect p0 = pVerts[VertIndex(sideLength, x, y)].Pos;
	Vect p1 = pVerts[VertIndex(sideLength, x, y + 1)].Pos;
	Vect p2 = pVerts[VertIndex(sideLength, x + 1, y + 1)].Pos;
	Vect p3 = pVerts[VertIndex(sideLength, x + 1, y)].Pos;
	Vect p4 = pVerts[VertIndex(sideLength, x, y - 1)].Pos;
	Vect p5 = pVerts[VertIndex(sideLength, x - 1, y - 1)].Pos;
	Vect p6 = pVerts[VertIndex(sideLength, x - 1, y)].Pos;

	Vect v1 = p1 - p0;
	Vect v2 = p2 - p0;
	Vect v3 = p3 - p0;
	Vect v4 = p4 - p0;
	Vect v5 = p5 - p0;
	Vect v6 = p6 - p0;

	return (((v1.cross(v2).getNorm() + v2.cross(v3).getNorm() + v3.cross(v4).getNorm() + v4.cross(v5).getNorm() + v5.cross(v6).getNorm() + v6.cross(v1).getNorm()) * (1.0f / 6.0f)).getNorm());
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}