#ifndef _ShaderColorLight
#define _ShaderColorLight

#include "ShaderBase.h"
#include "Matrix.h"
#include "d3dUtil.h"
#include "ShaderTextureLight.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderColorLight : public ShaderBase
{

public:
	ShaderColorLight(const ShaderColorLight&) = delete;				 // Copy constructor
	ShaderColorLight(ShaderColorLight&&) = default;                    // Move constructor
	ShaderColorLight& operator=(const ShaderColorLight&) & = default;  // Copy assignment operator
	ShaderColorLight& operator=(ShaderColorLight&&) & = default;       // Move assignment operator
	~ShaderColorLight();		  							         // Destructor

	ShaderColorLight(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), int pointNum = 0);
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), int spotNum = 0);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFog(float start = 0.0f, float range = -1.0f, const Vect& color = Colors::Black);

private:

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

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range = 0;
	};

	PointLight PointLightData[NUMPOINTS];

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp = 0;
		float Range = 0;
	};

	SpotLight SpotLightData[NUMSPOTS];

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*  mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer*	mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight[NUMPOINTS];
		SpotLight SptLight[NUMSPOTS];
		Vect EyePosWorld;
	};

	ID3D11Buffer*  mpBufferLightParams;

	struct Data_Fog 
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	ID3D11Buffer* mpBufferFog;

};

#endif _ShaderColorLight

