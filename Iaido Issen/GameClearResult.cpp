/*****************************************************************************
*
*    �Q�[���N���A��ʁ@[GameClereResult.cpp]
*    �쐬�ҁ@�@�܏\�����
*
*    SE BGM�����@�E�G�}�c
******************************************************************************/
#include "GameClearResult.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "fade.h"
#include "sound1.h"

/*****************************************************************************
* �}�N����`
******************************************************************************/
enum SELECT
{
	SELECT_NONE,		// �V�[���ݒ�Ȃ�
	SELECT_START,	//�@�^�C�g��
	SELECT_END,		// �Q�[���{��

	SELECT_NUM,		// �I�[�R�[�h
};

/*****************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/


/*****************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
static int   g_GameClereResultTexture;  // �e�N�X�`���̎��ʎq

static int   g_select;
static float g_count;

static int   g_GameClereSE = 0;		// BGM���ʎq

static int   g_Sound_husuma_op = 0;
static int   g_Sound_husuma_cl = 0;


/*****************************************************************************
* ����������
******************************************************************************/
void InitGameClearResult(void)
{
	g_count = 0.0f;

	g_select = SELECT_START;

	// �^�C�g����ʗp�e�N�X�`���̓ǂݍ���
	g_GameClereResultTexture = LoadTexture((char*)"data/TEXTURE/result.jpg");
	
	g_GameClereSE = LoadSound((char*)"data/SE/GAMEClEAR.wav"); //�^�C�g��BGM

	g_Sound_husuma_op = LoadSound((char*)"data/SE/���̊J����.wav");
	g_Sound_husuma_cl = LoadSound((char*)"data/SE/���̕܂鉹.wav");


	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_GameClereSE, 0);


}

/*****************************************************************************
* �I������
******************************************************************************/
void UninitGameClearResult(void)
{

}

/*****************************************************************************
* �X�V����
******************************************************************************/
void UpdateGameClearResult(void)
{

	g_count += 0.5;

	if (g_count > 150)
	{
		SceneTransition(SCENE_TITLE);
		PlaySound(g_Sound_husuma_cl, 0); //���̕��鉹
		PlaySound(g_Sound_husuma_op, 0); //���̊J����
	}


}

/*****************************************************************************
* �`�揈��
******************************************************************************/
void DrawGameClearResult(void)
{
	// �e�N�X�`���̕`��
	DrawSpriteLeftTop(g_GameClereResultTexture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}