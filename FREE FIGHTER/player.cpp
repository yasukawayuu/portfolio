//=============================================================================
//
// �|���S���\������ [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "shadow.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model;	// ���f���ǂݍ���
static PLAYER		g_Player;	// �v���C���[���		
static LIGHT		g_DirectionalLight;	// �f�B���N�V���i�����C�g
static LIGHT		g_PointLight[5];		// �|�C���g���C�g


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.spd = 5.0f;
	g_Player.use = true;
	g_Player.Rot = 0.1f;
	g_Player.Rotate = 0.0f;
	g_Player.fream = 0;
	g_Player.RotateFlag = false;

	//�����蔻��p�T�C�Y�̏����ݒ�
	g_Player.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/f15.obj", &g_Model);

	// ���s�����̐ݒ�i���E���Ƃ炷���j
	g_DirectionalLight.Type = LIGHT_TYPE_DIRECTIONAL;				// ���s����
	g_DirectionalLight.Enable = true;								// ���̃��C�g��ON
	g_DirectionalLight.Direction = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);// ���̌���
	g_DirectionalLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	SetLight(0, &g_DirectionalLight);								// ����Őݒ肵�Ă���

	// �_�����̐ݒ�
	g_PointLight[0].Type = LIGHT_TYPE_POINT;						// ���s����
	g_PointLight[0].Enable = true;									// ���̃��C�g��ON
	g_PointLight[0].Position = D3DXVECTOR4(0.0f, 0.0f, -400.0f, 0.0f);// ���̍��W
	g_PointLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	g_PointLight[0].Attenuation = 500000.0f;						// ��������
	SetLight(1, &g_PointLight[0]);									// ����Őݒ肵�Ă���


	// �e�̃Z�b�g�i�e�͍�����0�ɂ��ĕ\��������j
	g_Player.shadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z), 80.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	if (g_Player.use)
	{
		//��������
		if (g_Player.RotateFlag == false)
		{
			g_Player.rot.z *= 0.9f;
			g_Player.rot.x *= 0.9f;


			if (GetKeyboardPress(DIK_A) && g_Player.pos.x > -SCREEN_WIDTH / 3)
			{
				g_Player.pos.x += -VALUE_MOVE;
				g_Player.rot.z += g_Player.Rot;
			}

			if (GetKeyboardPress(DIK_D) && g_Player.pos.x < SCREEN_WIDTH / 3)
			{
				g_Player.pos.x += VALUE_MOVE;
				g_Player.rot.z -= g_Player.Rot;
			}

			if (GetKeyboardPress(DIK_W) && g_Player.pos.y < SCREEN_HEIGHT / 3)
			{
				g_Player.pos.y += VALUE_MOVE;
				g_Player.rot.x -= g_Player.Rot;
			}

			if (GetKeyboardPress(DIK_S) && g_Player.pos.y > -SCREEN_HEIGHT / 3)
			{
				g_Player.pos.y += -VALUE_MOVE;
				g_Player.rot.x += g_Player.Rot;
			}

		}
		
		if (GetKeyboardTrigger(DIK_LSHIFT) && GetKeyboardPress(DIK_D))
		{
			g_Player.RotateFlag = true;
			g_Player.spd = 10.0f;
			g_Player.Rotate = -0.1f;
		}


		if (GetKeyboardTrigger(DIK_LSHIFT) && GetKeyboardPress(DIK_A))
		{
			g_Player.RotateFlag = true;
			g_Player.spd = -10.0f;
			g_Player.Rotate = 0.1f;
		}

		if (g_Player.pos.x + g_Player.spd > SCREEN_WIDTH / 3 || g_Player.pos.x + -g_Player.spd < -SCREEN_WIDTH / 3)
			g_Player.spd = 0.0f;


		if (g_Player.RotateFlag == true)
		{
			g_Player.pos.x += g_Player.spd;
			g_Player.rot.z += g_Player.Rotate;
			g_Player.fream++;
			if (g_Player.fream >= 30)
			{
				g_Player.fream = 0;
				g_Player.RotateFlag = false;
			}
		}



		// �e������
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			D3DXVECTOR3 dir;
			dir.x = cos(g_Player.rot.y - (D3DX_PI / 2));
			dir.y = 0.0f;
			dir.z = sin(g_Player.rot.y + (D3DX_PI / 2));
			SetBullet(g_Player.pos, dir);
		}

		// �e�̈ʒu���X�V
		SetPositionShadow(g_Player.shadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
	}
	

#ifdef _DEBUG	// �f�o�b�O����\������
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Player.rot.x, g_Player.rot.y);

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	if (g_Player.use)
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_Player.mtxWorld);

		//�J�����O�Ȃ�(�~�N���񃂃f���̔��̑Ή�)
		SetCullingMode(CULL_MODE_NONE);

		//obj���f���̕`��
		DrawModel(&g_Model);

		//�J�����O�����ɖ߂�
		SetCullingMode(CULL_MODE_BACK);
	}
	
}

//=============================================================================
// �v���C���[�����擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}
