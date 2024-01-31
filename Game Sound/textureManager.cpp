
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "textureManager.h"

TextureManager* TextureManager::m_pInstance{};


void TextureManager::Init()
{
	Renderer* renderer = Renderer::GetInstance();


	//頂点バッファ生成 GPU上に保存できる
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	renderer->GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	{
		D3DXVECTOR3* pos = new D3DXVECTOR3[10000];
		int i = 0;
		for (int x = 0; x < 100; x++)
		{
			for (int z = 0; z < 100; z++)
			{
				pos[i] = D3DXVECTOR3(x, 0.0f, z);
				i++;
			}
		}

		//ストラクチャードバッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(D3DXVECTOR3) * 10000;
		bd.StructureByteStride = sizeof(D3DXVECTOR3);
		bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pos;

		renderer->GetDevice()->CreateBuffer(&bd, &sd, &m_PositionBuffer);
		delete[] pos;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = DXGI_FORMAT_UNKNOWN;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.NumElements = 10000;
		renderer->GetDevice()->CreateShaderResourceView(m_PositionBuffer, &srvd, &m_PositionSRV);
	}
	
}

void TextureManager::Draw2D(std::string texName, float X, float Y,float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color)
{
	Renderer* renderer = Renderer::GetInstance();

	renderer->SetWorldViewProjection2D();

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	renderer->GetDeviceContext()->Map(m_VertexBuffer, 0, //mapを呼び出し
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;



	vertex[0].Position = D3DXVECTOR3(X ,Y , 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width,Y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	renderer->GetDeviceContext()->Unmap(m_VertexBuffer, 0); //Umapを呼び出す

	//頂点バッファ
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	material.TextureEnable = true;
	renderer->SetMaterial(material);

	if (!texName.empty())
	{
		ID3D11ShaderResourceView* texture = m_Texture[texName]->GetTexture();
		//テクスチャ設定
		renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
	}
	else
	{

			ID3D11ShaderResourceView* texture = renderer->GetDepthPointShadowTexture(1);
			renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
	

	}
	//プリミティブトボロジ設定
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描写
	renderer->GetDeviceContext()->Draw(4, 0);
}




void TextureManager::Draw3D(std::string texName, D3DXVECTOR3 position, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color)
{
	Renderer* renderer = Renderer::GetInstance();


	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	renderer->GetDeviceContext()->Map(m_VertexBuffer, 0, //mapを呼び出し
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;



	vertex[0].Position = D3DXVECTOR3(position.x - Width, position.y + Height, position.z);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(position.x + Width, position.y + Height, position.z);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(position.x - Width, position.y - Height, position.z);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(position.x + Width, position.y - Height, position.z);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	renderer->GetDeviceContext()->Unmap(m_VertexBuffer, 0); //Umapを呼び出す

	//頂点バッファ
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	material.TextureEnable = true;
	renderer->SetMaterial(material);

	ID3D11ShaderResourceView* texture = m_Texture[texName]->GetTexture();
	//テクスチャ設定
	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	//プリミティブトボロジ設定
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描写
	renderer->GetDeviceContext()->Draw(4, 0);
}

void TextureManager::Draw3DLeftTop(std::string texName, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color)
{
	Renderer* renderer = Renderer::GetInstance();


	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	renderer->GetDeviceContext()->Map(m_VertexBuffer, 0, //mapを呼び出し
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;



	vertex[0].Position = D3DXVECTOR3(-Width, Height, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(Width, Height, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(-Width,0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(Width, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	renderer->GetDeviceContext()->Unmap(m_VertexBuffer, 0); //Umapを呼び出す

	//頂点バッファ
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	material.TextureEnable = true;
	renderer->SetMaterial(material);

	ID3D11ShaderResourceView* texture = m_Texture[texName]->GetTexture();
	//テクスチャ設定
	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	renderer->GetDeviceContext()->VSSetShaderResources(2, 1, &m_PositionSRV);

	//プリミティブトボロジ設定
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描写
	renderer->GetDeviceContext()->DrawInstanced(4, 10000,0,0);
}

void TextureManager::Load()
{
	m_Texture["loading"] = new Texture();
	m_Texture["loading"]->Load("asset\\texture\\loading.jpg");

	m_Texture["title"] = new Texture();
	m_Texture["title"]->Load("asset\\texture\\title.png");

	m_Texture["result"] = new Texture();
	m_Texture["result"]->Load("asset\\texture\\result.png");

	m_Texture["fade"] = new Texture();
	m_Texture["fade"]->Load("asset\\texture\\black.png");

	m_Texture["num"] = new Texture();
	m_Texture["num"]->Load("asset\\texture\\num.png");

	m_Texture["tree"] = new Texture();
	m_Texture["tree"]->Load("asset\\texture\\tree.dds");

	m_Texture["flooring"] = new Texture();
	m_Texture["flooring"]->Load("asset\\texture\\flooring.dds");

	m_Texture["maru"] = new Texture();
	m_Texture["maru"]->Load("asset\\texture\\maru.png");

	m_Texture["title"] = new Texture();
	m_Texture["title"]->Load("asset\\texture\\logo.png");

	m_Texture["grass"] = new Texture();
	m_Texture["grass"]->Load("asset\\texture\\grass.png");

	m_LoadFinish = true;
}

void TextureManager::Unload()
{
	for (auto texture : m_Texture)
	{
		texture.second->Unload();
		delete texture.second;
	}

	m_Texture.clear();

	if (m_VertexBuffer != NULL)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	m_PositionSRV->Release();
	m_PositionBuffer->Release();

}

