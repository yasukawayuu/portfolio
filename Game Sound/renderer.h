#pragma once

struct VERTEX_3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR2 TexCoord;
};



struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	BOOL		TextureEnable;
	float		Dummy[2];
};



struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
	D3DXMATRIX  ViewMatrix; //ライトカメラ行列
	D3DXMATRIX  ProjectionMatrix; //ライトプロジェクション行列
};

struct POINTLIGHT
{
	D3DXVECTOR4 Position;
	D3DXVECTOR4 Attenuation;
	D3DXCOLOR	Color;
	D3DXMATRIX  ViewMatrix[6]; //ライトカメラ行列
	D3DXMATRIX  ProjectionMatrix; //ライトプロジェクション行列
};

struct  SPOTLIGHT
{
	D3DXVECTOR4 Position;
	D3DXVECTOR4 Attenuation;
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Color;
	D3DXMATRIX  ViewMatrix; //ライトカメラ行列
	D3DXMATRIX  ProjectionMatrix; //ライトプロジェクション行列
};

struct PARAMETER
{
	D3DXVECTOR4 hp;
	D3DXCOLOR	lostColor;
	D3DXCOLOR	baseColor;
	D3DXCOLOR	diffColor;
};

struct FOG
{
	D3DXVECTOR4	FogP;
	D3DXCOLOR	FogC;
	D3DXCOLOR	FogGC;
};

class Renderer
{
private:
	static Renderer* m_pInstance;

	D3D_FEATURE_LEVEL       m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	ID3D11Device* m_Device{};
	ID3D11DeviceContext* m_DeviceContext{};
	IDXGISwapChain* m_SwapChain{};
	ID3D11RenderTargetView* m_RenderTargetView{};
	ID3D11DepthStencilView* m_DepthStencilView{};

	ID3D11Buffer* m_WorldBuffer{};
	ID3D11Buffer* m_ViewBuffer{};
	ID3D11Buffer* m_ProjectionBuffer{};
	ID3D11Buffer* m_MaterialBuffer{};
	ID3D11Buffer* m_LightBuffer{};
	ID3D11Buffer* m_PointLightBuffer{};
	ID3D11Buffer* m_SpotLightBuffer{};

	ID3D11Buffer* m_CameraBuffer{};
	ID3D11Buffer* m_ParameterBuffer{};
	ID3D11Buffer* m_FogBuffer{};


	ID3D11DepthStencilState* m_DepthStateEnable{};
	ID3D11DepthStencilState* m_DepthStateDisable{};

	ID3D11DepthStencilView* m_DepthShadowDepthStencilView{};
	ID3D11ShaderResourceView* m_DepthShadowShaderResourceView{};
	float					m_ShadoSize{};

	ID3D11BlendState* m_BlendState{};
	ID3D11BlendState* m_BlendStateATC{};


	ID3D11DepthStencilView* m_DepthPointShadowDepthStencilView[6]{};
	ID3D11ShaderResourceView* m_DepthPointShadowShaderResourceView[6]{};

	ID3D11DepthStencilView* m_DepthSpotShadowDepthStencilView{};
	ID3D11ShaderResourceView* m_DepthSpotShadowShaderResourceView{};

public:
	static Renderer* GetInstance(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new Renderer;
		}

		return m_pInstance;
	}

	static void DeleteInstance(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}


	void Init();
	void Uninit();
	void Begin();
	void BeginDepth();
	void BeginDepthPoint(int index);
	void BeginDepthSpot();
	void End();

	void SetDepthEnable(bool Enable);
	void SetATCEnable(bool Enable);
	void SetWorldViewProjection2D();
	void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	void SetMaterial(MATERIAL Material);
	void SetLight(LIGHT Light);
	void SetPointLight(POINTLIGHT PointLight);
	void SetSpotLight(SPOTLIGHT SpotLight);

	void SetCameraPosition(D3DXVECTOR3 CameraPosition);
	void SetParameter(PARAMETER param);
	void SetFog(FOG Fog);

	ID3D11Device* GetDevice(void) { return m_Device; }
	ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }
	IDXGISwapChain* GetSwapChain(void) { return m_SwapChain; }

	void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);
	ID3D11ShaderResourceView* GetDepthShadowTexture() { return m_DepthShadowShaderResourceView; }
	ID3D11ShaderResourceView* GetDepthPointShadowTexture(int index){ return m_DepthPointShadowShaderResourceView[index];}
	ID3D11ShaderResourceView* GetDepthSpotShadowTexture() { return m_DepthSpotShadowShaderResourceView; }

	void SetDefaultViewport();
	void SetDepthViewport();
	void SetDefaultSamplerState();
	void SetDepthSamplerState();
};
