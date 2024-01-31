#pragma once

class Texture;
#include <string>
#include <unordered_map>

class TextureManager
{
private:
	static TextureManager* m_pInstance;
	std::unordered_map<std::string, Texture*> m_Texture;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	bool m_LoadFinish = false;
	ID3D11Buffer* m_PositionBuffer{};
	ID3D11ShaderResourceView* m_PositionSRV{};
private:
	TextureManager() {};
	~TextureManager() {};
public:
	static TextureManager* GetInstance(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new TextureManager;
		}

		return m_pInstance;
	}

	static void DeleteInstance(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void Init();
	void Draw2D(std::string texName, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void Draw3D(std::string texName,D3DXVECTOR3 position, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void Draw3DLeftTop(std::string texName, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	void Load();
	void Unload();
	bool GetLoadFinish(void) { return m_LoadFinish; }
};