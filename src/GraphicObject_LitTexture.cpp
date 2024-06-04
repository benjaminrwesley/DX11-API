#include "GraphicObject_LitTexture.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include <assert.h>

GraphicObject_LitTexture::GraphicObject_LitTexture(ShaderTextureLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();

	MeshTextures = new Texture * [n];

	MeshAmbient = new Vect[n];
	MeshDiffuse = new Vect[n];
	MeshSpecular = new Vect[n];

	for (int i = 0; i < n; i++) {
		MeshAmbient[i] = Vect(0, 0, 0);
		MeshDiffuse[i] = Vect(0, 0, 0);
		MeshSpecular[i] = Vect(0, 0, 0);
	}
}

GraphicObject_LitTexture::~GraphicObject_LitTexture()
{
	delete[] MeshTextures;

	delete[] MeshAmbient;
	delete[] MeshDiffuse;
	delete[] MeshSpecular;;
}

void GraphicObject_LitTexture::SetTexture(Texture* tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshTextures[i] = tex;
}

void GraphicObject_LitTexture::SetTexture(Texture* tex, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshTextures[meshnum] = tex;
}

void GraphicObject_LitTexture::SetMat(const Vect& amb, const Vect& dif, const Vect& spec)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		MeshAmbient[i] = amb;
		MeshDiffuse[i] = dif;
		MeshSpecular[i] = spec;
	}
}

void GraphicObject_LitTexture::SetMat(const Vect& amb, const Vect& dif, const Vect& spec, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshAmbient[meshnum] = amb;
	MeshDiffuse[meshnum] = dif;
	MeshSpecular[meshnum] = spec;
}

void GraphicObject_LitTexture::SetWorld(const Matrix& m)
{
	World = m;
}

Matrix GraphicObject_LitTexture::GetWorld()
{
	return World;
}

ShaderTextureLight* GraphicObject_LitTexture::GetShader()
{
	return pShader;
}

void GraphicObject_LitTexture::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(MeshTextures[i]);
		pShader->SendWorldAndMaterial(World, MeshAmbient[i], MeshDiffuse[i], MeshSpecular[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}