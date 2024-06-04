#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderTexture.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();

	MeshTextures = new Texture* [n];
}

GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] MeshTextures;
}

void GraphicObject_Texture::SetTexture(Texture* tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshTextures[i] = tex;
}

void GraphicObject_Texture::SetTexture(Texture* tex, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshTextures[meshnum] = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

Matrix GraphicObject_Texture::GetWorld()
{
	return World;
}

ShaderTexture* GraphicObject_Texture::GetShader()
{
	return pShader;
}

void GraphicObject_Texture::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorld(World);
		pShader->SetTextureResourceAndSampler(MeshTextures[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}