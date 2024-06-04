// GraphicObject_LitColor
#ifndef _GraphicObject_LitColor
#define _GraphicObject_LitColor

#include "GraphicObject_Base.h"
#include "ShaderColorLight.h"
#include "Vect.h"

class GraphicObject_LitColor : public GraphicObject_Base
{
public:
	GraphicObject_LitColor(const GraphicObject_LitColor&) = delete;				 // Copy constructor
	GraphicObject_LitColor(GraphicObject_LitColor&&) = default;                    // Move constructor
	GraphicObject_LitColor& operator=(const GraphicObject_LitColor&) & = default;  // Copy assignment operator
	GraphicObject_LitColor& operator=(GraphicObject_LitColor&&) & = default;       // Move assignment operator
	~GraphicObject_LitColor();		  											 // Destructor

	GraphicObject_LitColor() = delete;

	void SetMat(const Vect& amb, const Vect& dif, const Vect& spec);
	void SetMat(const Vect& amb, const Vect& dif, const Vect& spec, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_LitColor(ShaderColorLight* shader, Model* mod);

private:
	ShaderColorLight* pShader;
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	Vect* MeshAmbient;
	Vect* MeshDiffuse;
	Vect* MeshSpecular;

	Matrix World;
};

#endif _GraphicObject_LitColor
