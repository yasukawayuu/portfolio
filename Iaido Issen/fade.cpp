//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// 
//
//=============================================================================
#include "fade.h"
#include "texture.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FADE_RATE					(0.01f)			// �t�F�[�h�W��


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	g_TextureFade;				// �e�N�X�`���ԍ�
static int	g_TextureFadeL;				// �e�N�X�`���ԍ�
static int	g_TextureFadeR;				// �e�N�X�`���ԍ�


FADE_STATE	g_FadeState = FADE_NONE;	// �t�F�[�h�̏��
SCENE		g_SceneNext;				// ���̃V�[��
//D3DXCOLOR	g_Color;					// �t�F�[�h�̃J���[
float g_move;
int g_flag;
float g_count;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade(void)
{
	//�e�N�X�`������
	//g_TextureFade = LoadTexture((char*)"data/TEXTURE/husuma.jpg");
	g_TextureFadeL = LoadTexture((char*)"data/TEXTURE/husuma/husumaL.jpg");
	g_TextureFadeR = LoadTexture((char*)"data/TEXTURE/husuma/husumaR.jpg");

	//������
	g_FadeState = FADE_NONE;
	g_SceneNext = SCENE_NONE;
	//g_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	g_move = 0.0f;
	g_flag = 0;
	g_count = 0.0f;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	

	// �t�F�[�h������
	if (g_FadeState != FADE_NONE)
	{
		
		if (g_FadeState == FADE_OUT)
		{// �t�F�[�h�A�E�g����

			g_move += 20;
			if (g_move >= SCREEN_WIDTH / 2 && g_flag == 0)
			{
				g_flag = 1;
				g_move = 0;

			}
			if (g_flag == 1)
			{
				// �t�F�[�h�C�������ɐ؂�ւ�
				g_FadeState = FADE_IN;

				// ���[�h��ݒ�
				SetScene(g_SceneNext);
				
			}

			
		}
		else if (g_FadeState == FADE_IN)
		{// �t�F�[�h�C������

			g_move += 20;
			if (g_move >= SCREEN_WIDTH / 2)
			{
				g_move = 0;
				g_flag = 0;
				g_FadeState = FADE_NONE;
			}
		}		
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade(void)
{
	// �t�F�[�h���������Ă��Ȃ��̂Ȃ�`�悵�Ȃ�
	if (g_FadeState == FADE_NONE)
		return;

	if (g_flag == 0)
	{
		DrawSprite(g_TextureFadeL, (-SCREEN_WIDTH / 4 + g_move), SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawSprite(g_TextureFadeR, (SCREEN_WIDTH + (SCREEN_WIDTH / 4)) - g_move, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	if (g_flag == 1)
	{
		DrawSprite(g_TextureFadeL, (SCREEN_WIDTH / 4 - g_move), SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawSprite(g_TextureFadeR, ((SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4) + g_move), SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	

}

/*------------------------------------------------------------------------------
   �t�F�[�h�A�E�g�E�t�F�[�h�C�����������Ȃ���V�[���J�ڂ���֐�
------------------------------------------------------------------------------*/
void SceneTransition(SCENE nextScene)
{
	g_SceneNext = nextScene;
	g_FadeState = FADE_OUT;

	// FADE_OUT �� FADE_IN
}

/*------------------------------------------------------------------------------
   �t�F�[�h�C�����������Ȃ���V�[�����J�n����֐�
------------------------------------------------------------------------------*/
void SceneFadeIn(SCENE nextScene)
{
	//g_Color.a = 1.0f;
	g_FadeState = FADE_IN;
	SetScene(nextScene);

	// �����Ȃ� FADE_IN
}

/*------------------------------------------------------------------------------
   �t�F�[�h�����̏󋵂�Ԃ��֐�
------------------------------------------------------------------------------*/
FADE_STATE GetFadeState(void)
{
	return g_FadeState;
}

/*------------------------------------------------------------------------------
   �t�F�[�h�J���[�ݒ肷��֐�
------------------------------------------------------------------------------*/
void SetFadeColor(float r, float g, float b)
{
	//g_Color = D3DXCOLOR(r, g, b, 1.0f);
}

