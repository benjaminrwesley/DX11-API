#include "GraphicObject_LitColor.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_LitColor::GraphicObject_LitColor(ShaderColorLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();

	MeshAmbient = new Vect[n];
	MeshDiffuse = new Vect[n];
	MeshSpecular = new Vect[n];

	for (int i = 0; i < n; i++) {
		MeshAmbient[i] = Vect(0, 0, 0);
		MeshDiffuse[i] = Vect(0, 0, 0);
		MeshSpecular[i] = Vect(0, 0, 0);
	}
}

GraphicObject_LitColor::~GraphicObject_LitColor()
{
	delete[] MeshAmbient;
	delete[] MeshDiffuse;
	delete[] MeshSpecular;;
}

void GraphicObject_LitColor::SetMat(const Vect& amb, const Vect& dif, const Vect& spec)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		MeshAmbient[i] = amb;
		MeshDiffuse[i] = dif;
		MeshSpecular[i] = spec;
	}
}

void GraphicObject_LitColor::SetMat(const Vect& amb, const Vect& dif, const Vect& spec, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshAmbient[meshnum] = amb;
	MeshDiffuse[meshnum] = dif;
	MeshSpecular[meshnum] = spec;
}

void GraphicObject_LitColor::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_LitColor::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, MeshAmbient[i], MeshDiffuse[i], MeshSpecular[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}