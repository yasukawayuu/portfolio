//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	g_TextureNo = 0;	// �e�N�X�`�����
static int	g_TextureStart = 0;	// �e�N�X�`�����
static int	g_TextureExit = 0;	// �e�N�X�`�����
static int  g_TextureSelect = 0;
static int	g_TextureBg = 0;

static D3DXVECTOR2  g_SelectPos;
static int	g_BGMNo = 0;		// BGM���ʎq

								//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	//�e�N�X�`������
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/freefighter.png");

	g_TextureStart = LoadTexture((char*)"data/TEXTURE/start.png");

	g_TextureExit = LoadTexture((char*)"data/TEXTURE/exit.png");

	g_TextureSelect = LoadTexture((char*)"data/TEXTURE/select.png");

	g_TextureBg = LoadTexture((char*)"data/TEXTURE/bg.jpeg");

	g_BGMNo = LoadSound((char*)"data/BGM/sample000.wav");

	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_BGMNo, -1);

	g_SelectPos = D3DXVECTOR2(SCREEN_WIDTH / 2 - 120.0f, SCREEN_HEIGHT / 2 + 70.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	StopSoundAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_S) && g_SelectPos.y == SCREEN_HEIGHT / 2 + 70.0f)
	{
		g_SelectPos.y += 70.0f;
	}

	if (GetKeyboardTrigger(DIK_W) && g_SelectPos.y == SCREEN_HEIGHT / 2 + 140.0f)
	{ 
		g_SelectPos.y -= 70.0f;
	}

	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		if(g_SelectPos.y == SCREEN_HEIGHT / 2 + 70.0f)
			SceneTransition(SCENE_GAME);

		if (g_SelectPos.y == SCREEN_HEIGHT / 2 + 140.0f)
			exit(0);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(g_TextureBg, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,0.0f , 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureNo, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 300.0f, 300.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureStart, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 75.0f, 200.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureExit, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150.0f, 200.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(g_TextureSelect,g_SelectPos.x,g_SelectPos.y, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f);

}

