/*****************************************************************************
*
*    �Q�[���I�[�o�[��ʁ@[GameOver.cpp]
*    �쐬�ҁ@�@�܏\�����
******************************************************************************/
#include "GameOver.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "fade.h"
#include "sound1.h"

/*****************************************************************************
* �}�N����`
******************************************************************************/

/*****************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/


/*****************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
static int g_GameOverBGTexture;  // �e�N�X�`���̎��ʎq
static int g_GameOverForTitleTexture;  // �e�N�X�`���̎��ʎq
static int g_GameOverForRetryTexture;  // �e�N�X�`���̎��ʎq
static int g_GameOverSelectTexture;  // �e�N�X�`���̎��ʎq


static float g_s; // �X�^�[�g�{�^���̊ɋ}
static float g_amount; // �X�^�[�g�{�^���̊ɋ}
static float g_pos; // �X�^�[�g�{�^���̃|�W�V����


static int g_select;

static int g_GAMEOVERSOUND;
static int g_GAMEOVERSOUND2;


static int g_flame;

/*****************************************************************************
* ����������
******************************************************************************/
void GAMEOVER::InitGameOver(void)
{
	
	g_s = 0.0f;
	g_amount = 0.0f;

	g_select = SELECT_FOR_RETRY;

	g_flame = 0.0f;

	GAMEOVERSoundFlag2 = false;
	

	// �^�C�g����ʗp�e�N�X�`���̓ǂݍ���
	g_GameOverBGTexture = LoadTexture((char*)"data/TEXTURE/GameOver/GameOver.jpg");
	g_GameOverForTitleTexture = LoadTexture((char*)"data/TEXTURE/GameOver/forTitle.png");
	g_GameOverForRetryTexture = LoadTexture((char*)"data/TEXTURE/GameOver/retry.png");
	g_GameOverSelectTexture = LoadTexture((char*)"data/TEXTURE/title/kursol.png");

	g_GAMEOVERSOUND = LoadSound((char*)"data/SE/GAMEOVER.wav"); 
	g_GAMEOVERSOUND2= LoadSound((char*)"data/SE/game_overBGM.wav"); 

	
}

/*****************************************************************************
* �I������
******************************************************************************/
void GAMEOVER::UninitGameOver(void)
{
	StopSoundAll();
}

/*****************************************************************************
* �X�V����
******************************************************************************/
void GAMEOVER::UpdateGameOver(void)
{
	g_s = 0.15f; // �X�^�[�g�{�^���̊ɋ}�l
	

	switch (g_select)
	{
	case SELECT_FOR_RETRY:

		g_amount += g_s * g_s;

		g_pos += g_amount;

		if (g_pos >= 50)
		{
			g_amount = 0.0;
			g_pos = 0.0f;
		}
		break;
	case SELECT_FOR_TITLE:
		g_pos = 0.0f;
		break;
	default:
		break;
	}


	if ((GetKeyboardTrigger(DIK_X)) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_DPAD_DOWN) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_DPAD_UP))
	{
		if (g_select == SELECT_FOR_RETRY)
		{
			g_select = SELECT_FOR_TITLE;
		}
		else
		{
			g_select = SELECT_FOR_RETRY;
		}
	}

	if (g_select == SELECT_FOR_RETRY && ((GetKeyboardTrigger(DIK_SPACE)) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_A) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_B)))
	{
		m_challenge = true;
	}
	if (g_select == SELECT_FOR_TITLE && ((GetKeyboardTrigger(DIK_SPACE)) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_A) || IsButtonTriggered_X(0, XINPUT_GAMEPAD_B)))
	{
		SceneTransition(SCENE_TITLE);
	}




	/*if ()
	{

		if (GAMEOVERSoundFlag == false)
		{
			StopSoundAll;
			PlaySound(g_GAMEOVERSOUND, 0);
			GAMEOVERSoundFlag = true;
		}
		else
		{
			GAMEOVERSoundFlag = false;
		}
	}*/
	//BGM�؂�ւ��܂ŃJ�E���g

	if (GAMEOVERSoundFlag2 == false)
	{
		StopSoundAll();
		PlaySound(g_GAMEOVERSOUND, 0);
		GAMEOVERSoundFlag2 = true;

	}
	if (g_flame == 600)
	{
		GAMEOVERSoundFlag = true;
	}
	g_flame++;

	//BGM�؂�ւ�
	if (GAMEOVERSoundFlag == true)
	{
		PlaySound(g_GAMEOVERSOUND2, -1);
		GAMEOVERSoundFlag = false;
	}
}



/*****************************************************************************
* �`�揈��
******************************************************************************/
void GAMEOVER::DrawGameOver(void)
{
	// �e�N�X�`���̕`��
	DrawSpriteLeftTop(g_GameOverBGTexture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(g_GameOverForTitleTexture, SCREEN_WIDTH/2 + 50 , 600 , 768.0f, 256.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(g_GameOverForRetryTexture, SCREEN_WIDTH/2 , 800, 768.0f + g_pos, 256.0f + g_pos, 0.0f, 0.0f, 1.0f, 1.0f);

	
	switch (g_select)
	{
	case SELECT_FOR_TITLE:
		DrawSprite(g_GameOverSelectTexture, SCREEN_WIDTH / 2 - 250, 600.0f, 128.0f, 128.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case SELECT_FOR_RETRY:
		DrawSprite(g_GameOverSelectTexture, SCREEN_WIDTH / 2 - 250, 800.0f, 128.0f, 128.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

}
