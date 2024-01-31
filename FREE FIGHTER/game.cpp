/*==============================================================================

   �Q�[������ [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "shadow.h"
#include "wall.h"
#include "color.h"
#include "effect.h"

/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;


/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// �J�����̏�����
	InitCamera();

	// �e�̏�����
	InitShadow();

	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 100.0f, 100.0f);

	//�ǂ̏�����
	InitWall();

	// �v���C���[�̏�����
	InitPlayer();

	// �G�l�~�[�̏�����
	//InitEnemy();

	//�G�t�F�N�g�̏�����
	InitEffect();

	// �e�̏�����
	InitBullet();

	// �X�R�A�̏�����
	InitScore();

	//�F�̏�����
	InitColor();

	SetLightEnable(true);

	g_BGMNo = LoadSound((char*)"data/BGM/sample001.wav");

	SetVolume(g_BGMNo, 1.0f);
	PlaySound(g_BGMNo, -1);
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitGame()
{
	//�������Ƃ͋t���ɏI���������s��
	UninitScore();
	UninitShadow();
	UninitBullet();
	//UninitEnemy();
	UninitWall();
	UninitPlayer();
	UninitColor();
	UninitMeshField();
	UninitEffect();
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	// �J�����X�V
	UpdateCamera();

	// �n�ʂ̍X�V����
	UpdateMeshField();

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// �G�l�~�[�̍X�V����
	//UpdateEnemy();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�ǂ̍X�V����
	UpdateWall();

	// �e�̍X�V����
	UpdateBullet();

	// �e�̍X�V����
	UpdateShadow();

	// �X�R�A�̍X�V����
	UpdateScore();

	//�F�̍X�V����
	UpdateColor();
	
	// �����蔻��̍X�V����
	UpdateCollision();

}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// �v���C���[���_
	D3DXVECTOR3 pos = GetPlayer()->pos;
	pos.y = 0.0f;			// �J����������h�����߂ɃN���A���Ă���
	//SetCameraAT(pos);
	SetCamera();

	// �[�x�e�X�g�L��
	SetDepthEnable(true);

	// ���C�e�B���O�L��
	SetLightEnable(true);

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �n�ʂ̕`�揈��
	DrawMeshField();

	//�ǂ̕`�揈��
	DrawWall();

	// �e�̕`�揈��
	DrawShadow();

	// �G�l�~�[�̕`�揈��
	//DrawEnemy();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �e�̕`�揈��
	DrawBullet();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// �X�R�A�̕`�揈��
	DrawScore(D3DXVECTOR2(900.0f, 30.0f));

	//�@�F�̕`�揈��
	DrawColor();
}

