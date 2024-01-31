//=============================================================================
//
// �|���S���\������ [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "wall.h"
#include "texture.h"
#include "model.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model[4];			// ���f���ǂݍ���
static WALL			g_Wall[ALL_WALL_NUM][WALL_NUM];				// �Ǐ��		
static float		g_fream;
static float		g_speed;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitWall(void)
{
	for (int n = 0; n < ALL_WALL_NUM; n++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		for (int i = 0; i < WALL_NUM; i++)
		{
			switch (i)
			{
			case 0:
				g_Wall[n][i].pos = D3DXVECTOR3(-195.0f, 110.0f, 1000.0f + 1000.0f * n);
				//obj���f���̓ǂݍ���
				LoadModel((char*)"data/MODEL/red.obj", &g_Model[i]);
				g_Wall[n][i].color = 0;
				break;
			case 1:
				g_Wall[n][i].pos = D3DXVECTOR3(195.0f, 110.0f, 1000.0f + 1000.0f * n);
				//obj���f���̓ǂݍ���
				LoadModel((char*)"data/MODEL/green.obj", &g_Model[i]);
				g_Wall[n][i].color = 1;
				break;
			case 2:
				g_Wall[n][i].pos = D3DXVECTOR3(-195.0f, -110.0f, 1000.0f + 1000.0f * n);
				//obj���f���̓ǂݍ���
				LoadModel((char*)"data/MODEL/blue.obj", &g_Model[i]);
				g_Wall[n][i].color = 2;
				break;
			case 3:
				g_Wall[n][i].pos = D3DXVECTOR3(195.0f, -110.0f, 1000.0f + 1000.0f * n);
				//obj���f���̓ǂݍ���
				LoadModel((char*)"data/MODEL/yellow.obj", &g_Model[i]);
				g_Wall[n][i].color = 3;
				break;
			}
			g_Wall[n][i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Wall[n][i].scl = D3DXVECTOR3(39.0f, 22.0f, 1.0f);
			g_Wall[n][i].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Wall[n][i].use = true;

			g_Wall[n][i].size = D3DXVECTOR3(400.0f, 200.0f, 50.0f);

			//������P�ʃx�N�g��������
			D3DXVec3Normalize(&g_Wall[n][i].dir, &g_Wall[n][i].dir);


		}
	}

	g_speed = 5.0f;



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	//obj���f���̉��
	for (int i = 0; i < WALL_NUM; i++)
	{
		UnloadModel(&g_Model[i]);
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{
	g_fream++;

	if (g_fream > 200.0f)
	{
		g_speed += 0.1f;
		g_fream = 0.0f;
	}
		
	
	for (int n = 0; n < ALL_WALL_NUM; n++)
	{
		for (int i = 0; i < WALL_NUM; i++)
		{
			g_Wall[n][i].pos.z -= g_speed;
			if (g_Wall[n][i].pos.z < -1000.0f)
			{
				g_Wall[n][i].pos.z = 10000.0f + 1000.0f * n;
				g_Wall[n][i].use = true;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for (int n = 0; n < ALL_WALL_NUM; n++)
	{
		for (int i = 0; i < WALL_NUM; i++)
		{
			//use�t���O���I�t�̏ꍇ�̓X�L�b�v����5
			if (g_Wall[n][i].use == false)
				continue;

			// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
			D3DXMatrixIdentity(&g_Wall[n][i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_Wall[n][i].scl.x, g_Wall[n][i].scl.y, g_Wall[n][i].scl.z);
			D3DXMatrixMultiply(&g_Wall[n][i].mtxWorld, &g_Wall[n][i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[n][i].rot.y, g_Wall[n][i].rot.x, g_Wall[n][i].rot.z);
			D3DXMatrixMultiply(&g_Wall[n][i].mtxWorld, &g_Wall[n][i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Wall[n][i].pos.x, g_Wall[n][i].pos.y, g_Wall[n][i].pos.z);
			D3DXMatrixMultiply(&g_Wall[n][i].mtxWorld, &g_Wall[n][i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_Wall[n][i].mtxWorld);

			//obj���f���̕`��
			DrawModel(&g_Model[i]);
		}
	}
}


//=============================================================================
// �Ǐ����擾
//=============================================================================
WALL *GetWall(int i)
{
	return &g_Wall[i][0];
}

