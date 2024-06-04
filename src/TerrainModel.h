#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;
class StandardVertex;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;

	int TexelIndex(int sideLength, int x, int y) const;
	int VertIndex(int sideLength, int x, int y) const;

	float GetVertHeight(int h_val, float maxheight) const;

	Vect CalculateNormal(StandardVertex* pVerts, int sideLength, int x, int y);

public:
	TerrainModel(const TerrainModel&) = delete;				// Copy constructor
	TerrainModel(Model&&) = delete;						// Move constructor
	TerrainModel& operator=(const TerrainModel&) & = delete;  // Copy assignment operator
	TerrainModel& operator=(TerrainModel&&) & = delete;       // Move assignment operator
	~TerrainModel();

	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	Model* GetModel();

	void Render(ID3D11DeviceContext* context);
};



#endif _TerrainModel