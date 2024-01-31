
#include "main.h"
#include "renderer.h"
#include "meshField.h"
#include "shader.h"


float g_FieldHeight[21][21] = {
	/*{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f},
	{5.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 5.0f},
	{5.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 5.0f},
	{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f}*/
};

void MeshField::Init()
{	
	Renderer* renderer = Renderer::GetInstance();
	// ���_�o�b�t�@����
	{
		for (int x = 0; x <= 20; x++)
		{
			for (int z = 0; z <= 20; z++)
			{
				m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, g_FieldHeight[z][x], (z - 10) * -5.0f);
				m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@���x�N�g��
				m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
			}
		}

		for (int x = 1; x <= 19; x++)
		{
			for (int z = 1; z <= 19; z++)
			{
				D3DXVECTOR3 vx, vz, vn;
				vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;
				vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;

				D3DXVec3Cross(&vn, &vz, &vx);
				D3DXVec3Normalize(&vn, &vn);
				m_Vertex[x][z].Normal = vn;
			}
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		renderer->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}




	// �C���f�b�N�X�o�b�t�@����
	{
		unsigned int index[(22 * 2) * 20 - 2 ];

		int i = 0;
		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				index[i] = x * 21 + z;
				i++;

				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19)
				break;

			//�k�ރ|���S��
			index[i] = (x + 1) * 21 + 20;
			i++;

			index[i] = (x + 1) * 21;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		renderer->GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}




	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(renderer->GetDevice(),
											"asset/texture/flooring.dds",
											NULL,
											NULL,
											&m_Texture,
											NULL);
	assert( m_Texture );

	AddComponent<Shader>()->Init("shader\\pixelLightingVS.cso", "shader\\pixelLightingPS.cso");

}


void MeshField::Uninit()
{
	GameObject::Uninit();

	if (m_VertexBuffer != NULL)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	if (m_IndexBuffer != NULL)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = NULL;
	}
	
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}


}


void MeshField::Update()
{

}


void MeshField::Draw()
{
	GameObject::Draw();

	Renderer* renderer = Renderer::GetInstance();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );

	// �C���f�b�N�X�o�b�t�@�ݒ�
	renderer->GetDeviceContext()->IASetIndexBuffer( m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory( &material, sizeof(material) );
	material.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	material.TextureEnable = true;
	renderer->SetMaterial( material );

	// �e�N�X�`���ݒ�
	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	ID3D11ShaderResourceView* depthshadowTexture = Renderer::GetInstance()->GetDepthShadowTexture();
	Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(1, 1, &depthshadowTexture);

	for (int i = 0; i < 6; i++)
	{
		ID3D11ShaderResourceView* depthshadowTexture2 = Renderer::GetInstance()->GetDepthPointShadowTexture(i);
		Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(i + 2, 1, &depthshadowTexture2);
	}

	ID3D11ShaderResourceView* depthshadowTexture3 = Renderer::GetInstance()->GetDepthSpotShadowTexture();
	Renderer::GetInstance()->GetDeviceContext()->PSSetShaderResources(8, 1, &depthshadowTexture3);


	// �v���~�e�B�u�g�|���W�ݒ�
	renderer->GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// �|���S���`��
	renderer->GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);

}

float MeshField::GetHeight(D3DXVECTOR3 Position)
{
	int x, z;

	//�@�u���b�N�ԍ������߂�
	x = Position.x / 5.0f + 10.0f;
	z = Position.z / -5.0f + 10.0f;

	//�A����E������
	D3DXVECTOR3 pos0, pos1, pos2, pos3;

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos2 = m_Vertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;
	//v12�͕����x�N�g���@�I�_-�n�_
	v12 = pos2 - pos1;
	//v1p�͕����x�N�g��  �I�_-�n�_
	v1p = Position - pos1;

	//�x�N�g��c�̕���
	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;
	//�������ゾ�����獶��@���͉E��
	if (c.y > 0.0f)
	{
		//����|���S��
		D3DXVECTOR3 v10;
		//v10�͕����x�N�g���@�I�_-�n�_
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{
		//�E���|���S��
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	//�����擾
	py = -((Position.x - pos1.x) * n.x
		+ (Position.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;

}
