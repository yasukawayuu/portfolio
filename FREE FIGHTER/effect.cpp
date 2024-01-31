//=============================================================================
//
// �e���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "effect.h"
#include "camera.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// ���_�o�b�t�@

static EFFECT		g_Effect;	// �e�f�[�^
static MATERIAL		g_Material;
static int			g_texNo = 0;

static float g_anime[3]
			{
				0.0f,
				0.3333,
				0.6666
			};

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	// �e�N�X�`������
	g_texNo = LoadTexture((char*)"data/TEXTURE/Effect_preview_0.png");

	// �}�e���A��������
	ZeroMemory(&g_Material, sizeof(g_Material));
	g_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ������

	g_Effect.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Effect.use = false;


	g_Effect.u = 0.0f;
	g_Effect.v = 0.0f;
	g_Effect.uw = 0.333;
	g_Effect.vh = 0.333;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	if (g_VertexBuffer != NULL)
	{// ���_�o�b�t�@�̉��
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	if (g_Effect.use)
	{
		//���ŏ���
		if (g_Effect.frame > 5.0f)
		{
			g_Effect.u++;
			if (g_Effect.u > 3)
			{
				g_Effect.u = 0;
				g_Effect.v++;
			}
			
			if (g_Effect.v > 3)
			{
				g_Effect.use = false;
			}
			
			g_Effect.frame = 0;
		}

		//���Ԍo��
		g_Effect.frame += 1.0f;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float width = 50.0f;
		float height = 50.0f;

		// ���_���W�̐ݒ�
		vertex[0].Position = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		vertex[2].Position = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// ���_�J���[�̐ݒ�
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = D3DXVECTOR2(g_anime[g_Effect.u], g_anime[g_Effect.v] + g_Effect.vh);
		vertex[1].TexCoord = D3DXVECTOR2(g_anime[g_Effect.u], g_anime[g_Effect.v]);
		vertex[2].TexCoord = D3DXVECTOR2(g_anime[g_Effect.u] + g_Effect.uw, g_anime[g_Effect.v] + g_Effect.vh);
		vertex[3].TexCoord = D3DXVECTOR2(g_anime[g_Effect.u] + g_Effect.uw, g_anime[g_Effect.v]);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	// ���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if (g_Effect.use)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Effect.mtxWorld);

		CAMERA *cam = GetCamera();

		// �|���S���𐳖ʂɌ�����
#if 0
			// �r���[�}�g���b�N�X�̋t�s����擾
		g_Effect.mtxWorld = cam->mtxInvView;
		g_Effect.mtxWorld._41 = 0.0f;
		g_Effect.mtxWorld._42 = 0.0f;
		g_Effect.mtxWorld._43 = 0.0f;
#else
			// �r���[�}�g���b�N�X���擾
		D3DXMATRIX mtxView = cam->mtxView;

		g_Effect.mtxWorld._11 = mtxView._11;
		g_Effect.mtxWorld._12 = mtxView._21;
		g_Effect.mtxWorld._13 = mtxView._31;
		g_Effect.mtxWorld._21 = mtxView._12;
		g_Effect.mtxWorld._22 = mtxView._22;
		g_Effect.mtxWorld._23 = mtxView._32;
		g_Effect.mtxWorld._31 = mtxView._13;
		g_Effect.mtxWorld._32 = mtxView._23;
		g_Effect.mtxWorld._33 = mtxView._33;
#endif


		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_Effect.pos.x,
			g_Effect.pos.y,
			g_Effect.pos.z);
		D3DXMatrixMultiply(&g_Effect.mtxWorld, &g_Effect.mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_Effect.mtxWorld);

		// �}�e���A���ݒ�
		SetMaterial(g_Material);

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_texNo));

		// �|���S���̕`��
		GetDeviceContext()->Draw(4, 0);
	}


	// ���C�e�B���O��L����
	SetLightEnable(true);

	// ���e�X�g�𖳌���
	SetAlphaTestEnable(false);
}


//=============================================================================
// �e�̃p�����[�^���Z�b�g
//=============================================================================
void SetEffect(D3DXVECTOR3 pos)
{

	if (g_Effect.use == false)
	{
		g_Effect.pos = pos;
		g_Effect.frame = 0.0f;

		g_Effect.use = true;

	}

}
