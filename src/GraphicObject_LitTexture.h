#ifndef _GraphicObject_LitTexture
#define _GraphicObject_LitTexture

#include "GraphicObject_Base.h"
#include "ShaderTextureLight.h"
#include "Vect.h"
#include "Texture.h"

class GraphicObject_LitTexture : public GraphicObject_Base
{
public:
	GraphicObject_LitTexture(const GraphicObject_LitTexture&) = delete;				 // Copy constructor
	GraphicObject_LitTexture(GraphicObject_LitTexture&&) = default;                    // Move constructor
	GraphicObject_LitTexture& operator=(const GraphicObject_LitTexture&) & = default;  // Copy assignment operator
	GraphicObject_LitTexture& operator=(GraphicObject_LitTexture&&) & = default;       // Move assignment operator
	~GraphicObject_LitTexture();		  											 // Destructor

	GraphicObject_LitTexture() = delete;

	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, int meshnum);
	void SetMat(const Vect& amb, const Vect& dif, const Vect& spec);
	void SetMat(const Vect& amb, const Vect& dif, const Vect& spec, int meshnum);
	void SetWorld(const Matrix& m);
	Matrix GetWorld();
	ShaderTextureLight* GetShader();
	virtual void Render() override;

	GraphicObject_LitTexture(ShaderTextureLight* shader, Model* mod);

private:
	ShaderTextureLight* pShader;

	Vect* MeshAmbient;
	Vect* MeshDiffuse;
	Vect* MeshSpecular;
	Texture** MeshTextures;

	Matrix World;
};

#endif _GraphicObject_LitTexture
