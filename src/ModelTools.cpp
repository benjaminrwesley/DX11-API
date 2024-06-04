#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, Vect(0, 0, 1), Colors::White);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, Vect(0, 0, 1), Colors::White);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, Vect(0, 0, 1), Colors::White);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, Vect(0, 0, 1), Colors::White);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, Vect(0, 0, -1), Colors::White);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, Vect(0, 0, -1), Colors::White);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, Vect(0, 0, -1), Colors::White);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, Vect(0, 0, -1), Colors::White);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, Vect(1, 0, 0), Colors::White);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, Vect(1, 0, 0), Colors::White);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, Vect(1, 0, 0), Colors::White);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, Vect(1, 0, 0), Colors::White);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, Vect(-1, 0, 0), Colors::White);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, Vect(-1, 0, 0), Colors::White);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, Vect(-1, 0, 0), Colors::White);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, Vect(-1, 0, 0), Colors::White);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, Vect(0, 1, 0), Colors::White);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, Vect(0, 1, 0), Colors::White);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, Vect(0, 1, 0), Colors::White);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, Vect(0, 1, 0), Colors::White);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, Vect(0, -1, 0), Colors::White);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, Vect(0, -1, 0), Colors::White);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, Vect(0, -1, 0), Colors::White);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, Vect(0, -1, 0), Colors::White);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0.0f, 0.375f, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0.0f, 0.625f, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	//Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1.0f, 0.625f, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1.0f, 0.375f, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	//Makes sure vslice and hslice are within minimum needed;
	vslice = vslice < 2 ? 2 : vslice;
	hslice = hslice < 2 ? 2 : hslice;

	float horRadIncrease = MATH_2PI / vslice;
	//We want vertical increase about the entire unit circle even though we use half 
	float vertRadIncrease = MATH_2PI / (hslice * 2);

	//We can just use point since we're at the origin
	Vect unitVector = Vect(0, -1, 0, 1);

	int numRings = hslice - 1;
	//# of rings * number of points in ring + top and bottom point
	nverts = (numRings * vslice) + 2;
	pVerts = new StandardVertex[nverts];
	Vect pos;

	//Set Bottom Point
	pos = Vect(0, -1, 0);
	pVerts[0].set(pos, pos.getNorm(), Colors::White);

	//Set Rings
	int vertIndex = 1;
	float vertRads = vertRadIncrease;
	float horRads = 0;

	//Rotate around half unit circle - top and bottom about the z axis
	for (int i = 1; i < hslice; i++) {
		//Roate around unit circle about the y axis 
		for (int j = 0; j < vslice; j++) {
			pos = Vect(unitVector * Matrix(ROT_Z, vertRads) * Matrix(ROT_Y, horRads));
			pVerts[vertIndex].set(pos, pos.getNorm(), Colors::White);
			horRads += horRadIncrease;
			vertIndex++;
		}
		horRads = 0;
		vertRads += vertRadIncrease;
	}

	//Set Top Point
	pos = Vect(0, 1, 0);
	pVerts[vertIndex].set(pos, pos.getNorm(), Colors::White);

	//Set Tris
	int numQuads = (numRings - 1) * vslice;
	//num of quads + num tris forming top or bottom * 2  
	ntri = (numQuads + vslice) * 2;
	pTriList = new TriangleByIndex[ntri];

	int triIndex = 0;

	//Set Bottom Tris
	int firstTriIndex = 0;
	int secondTriIndex = 1;
	int thirdTriIndex = vslice;

	for (int i = 0; i < vslice; i++) {
		pTriList[triIndex].set(firstTriIndex, secondTriIndex, thirdTriIndex);

		thirdTriIndex = secondTriIndex;
		secondTriIndex++;
		triIndex++;
	}

	firstTriIndex = 1;
	secondTriIndex = vslice + vslice;
	thirdTriIndex = vslice;

	//Build up our horizontal quads strips each with vslice faces
	int hquadSlices = hslice - 2;

	for (int i = 0; i < hquadSlices; i++) {
		for (int j = 0; j < vslice; j++) {
			pTriList[triIndex].set(firstTriIndex, secondTriIndex, thirdTriIndex);
			triIndex++;

			//Change our indices for the second triangle
			thirdTriIndex = secondTriIndex;
			secondTriIndex = firstTriIndex + vslice;

			pTriList[triIndex].set(firstTriIndex, secondTriIndex, thirdTriIndex);
			triIndex++;

			//Change our indices for the next first triangle
			thirdTriIndex = firstTriIndex;
			firstTriIndex++;
		}

		//Move up to our next strip
		secondTriIndex = (firstTriIndex - 1) + vslice + vslice;
		thirdTriIndex = (firstTriIndex - 1) + vslice;
	}

	//Set Top Tris
	firstTriIndex = nverts - 1;
	secondTriIndex = firstTriIndex - 1;
	thirdTriIndex = firstTriIndex - vslice;

	for (int i = 0; i < vslice; i++) {
		pTriList[triIndex].set(firstTriIndex, secondTriIndex, thirdTriIndex);

		secondTriIndex = thirdTriIndex;
		thirdTriIndex++;
		triIndex++;
	}
}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri) {
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	//Bottom Face
	pVerts[0].set(+0.5f, -0.5f, -0.5f, 0, -1, 0);
	pVerts[1].set(-0.5f, -0.5f, -0.5f, 0, -1, 0);
	pVerts[2].set(-0.5f, -0.5f, +0.5f, 0, -1, 0);
	pVerts[3].set(+0.5f, -0.5f, +0.5f, 0, -1, 0);

	pTriList[0].set(3, 2, 1);
	pTriList[1].set(1, 0, 3);

	//Front Tri
	Vect p1;
	Vect p2;
	Vect p3;

	Vect v1;
	Vect v2;

	Vect n;

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(-0.5f, -0.5f, +0.5f);
	p3 = Vect(+0.5f, -0.5f, +0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	pVerts[4].set(p1, n, Colors::White);
	pVerts[5].set(p2, n, Colors::White);
	pVerts[6].set(p3, n, Colors::White);

	pTriList[2].set(4, 5, 6);

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(+0.5f, -0.5f, -0.5f);
	p3 = Vect(-0.5f, -0.5f, -0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	//Back Tri
	pVerts[7].set(p1, n, Colors::White);
	pVerts[8].set(p2, n, Colors::White);
	pVerts[9].set(p3, n, Colors::White);

	pTriList[3].set(7, 8, 9);

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(-0.5f, -0.5f, -0.5f);
	p3 = Vect(-0.5f, -0.5f, +0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	//Left Tri
	pVerts[10].set(p1, n, Colors::White);
	pVerts[11].set(p2, n, Colors::White);
	pVerts[12].set(p3, n, Colors::White);

	pTriList[4].set(10, 11, 12);

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(+0.5f, -0.5f, +0.5f);
	p3 = Vect(+0.5f, -0.5f, -0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	//Right Tri
	pVerts[13].set(p1, n, Colors::White);
	pVerts[14].set(p2, n, Colors::White);
	pVerts[15].set(p3, n, Colors::White);

	pTriList[5].set(13, 14, 15);
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	//Bottom Face
	pVerts[0].set(+0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0, -1, 0);
	pVerts[1].set(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0, -1, 0);
	pVerts[2].set(-0.5f, -0.5f, +0.5f, 1.0f, 1.0f, 0, -1, 0);
	pVerts[3].set(+0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 0, -1, 0);

	pTriList[0].set(3, 2, 1);
	pTriList[1].set(1, 0, 3);

	//Front Tri
	Vect p1;
	Vect p2;
	Vect p3;

	Vect v1;
	Vect v2;

	Vect n;

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(-0.5f, -0.5f, +0.5f);
	p3 = Vect(+0.5f, -0.5f, +0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	pVerts[4].set(p1, 0.5f, 0.0f, n);
	pVerts[5].set(p2, 0.0f, 1.0f, n);
	pVerts[6].set(p3, 1.0f, 1.0f, n);

	pTriList[2].set(4, 5, 6);

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(+0.5f, -0.5f, -0.5f);
	p3 = Vect(-0.5f, -0.5f, -0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	//Back Tri
	pVerts[7].set(p1, 0.5f, 0.0f, n);
	pVerts[8].set(p2, 0.0f, 1.0f, n);
	pVerts[9].set(p3, 1.0f, 1.0f, n);

	pTriList[3].set(7, 8, 9);

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(-0.5f, -0.5f, -0.5f);
	p3 = Vect(-0.5f, -0.5f, +0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	//Left Tri
	pVerts[10].set(p1, 0.5f, 0.0f, n);
	pVerts[11].set(p2, 0.0f, 1.0f, n);
	pVerts[12].set(p3, 1.0f, 1.0f, n);

	pTriList[4].set(10, 11, 12);

	p1 = Vect(0.0f, +0.5f, 0.0f);
	p2 = Vect(+0.5f, -0.5f, +0.5f);
	p3 = Vect(+0.5f, -0.5f, -0.5f);

	n = CalculateTriNormal(p1, p2, p3);

	//Right Tri
	pVerts[13].set(p1, 0.5f, 0.0f, n);
	pVerts[14].set(p2, 0.0f, 1.0f, n);
	pVerts[15].set(p3, 1.0f, 1.0f, n);

	pTriList[5].set(13, 14, 15);
}

Vect ModelTools::CalculateTriNormal(Vect p1, Vect p2, Vect p3)
{
	return ((p2 - p1).cross((p3 - p1))).getNorm();
}


