#ifndef _ShaderTextureLight
#define _ShaderTextureLight

#include "ShaderBase.h"
#include "Matrix.h"
#include "d3dUtil.h"

struct ID3D11Buffer;
struct ID3D11Device;
struct Texture;

struct Material
{
	Vect Ambient;
	Vect Diffuse;
	Vect Specular;
};

struct PhongADS
{
	Vect Ambient;
	Vect Diffuse;
	Vect Specular;
};

struct DirectionalLight
{
	PhongADS Light;
	Vect Direction;
};

struct SpotLight
{
	PhongADS Light;
	Vect Position;
	Vect Attenuation;
	Vect Direction;
	float SpotExp;
	float Range;
};

struct PointLight
{
	PhongADS Light;
	Vect Position;
	Vect Attenuation;
	float Range;
};

static const int  NUMPOINTS = 3;
static const int NUMSPOTS = 2;

struct Data_LightParams
{
	DirectionalLight DirLight;
	PointLight PntLight[NUMPOINTS];
	SpotLight SptLight[NUMSPOTS];
	Vect EyePosWorld;
};

class ShaderTextureLight : public ShaderBase
{
public:
	ShaderTextureLight(const ShaderTextureLight&) = delete;				 // Copy constructor
	ShaderTextureLight(ShaderTextureLight&&) = default;                    // Move constructor
	ShaderTextureLight& operator=(const ShaderTextureLight&) & = default;  // Copy assignment operator
	ShaderTextureLight& operator=(ShaderTextureLight&&) & = default;       // Move assignment operator
	~ShaderTextureLight();		  							         // Destructor

	ShaderTextureLight(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), int pointNum = 0);
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), int spotNum = 0);
	void SetLightParameters(Data_LightParams params);
	Data_LightParams GetLightParameters();

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters();
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFog(float start = 0.0f, float range = -1.0f, const Vect& color = Colors::Black);
private:
	DirectionalLight DirLightData;

	PointLight PointLightData[NUMPOINTS];

	SpotLight SpotLightData[NUMSPOTS];

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;

	Data_LightParams LightParamData;

	ID3D11Buffer* mpBufferLightParams;

	struct Data_Fog
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	ID3D11Buffer* mpBufferFog;
};

#endif _ShaderTextureLight

