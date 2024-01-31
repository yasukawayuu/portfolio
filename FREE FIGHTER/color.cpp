//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(50)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(50)	// 


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static bool						g_Use;						// true:�g���Ă���  false:���g�p
static float					g_w, g_h;					// ���ƍ���
static D3DXVECTOR3				g_Pos;						// �|���S���̍��W
static int						g_TexNo;					// �e�N�X�`���ԍ�
static int						g_TexNow;
static D3DXCOLOR				g_rgba[4];

static int						g_Color;					// ���F��
static int						g_Color2;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitColor(void)
{
	//�e�N�X�`������
	g_TexNo = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_TexNow = LoadTexture((char*)"data/TEXTURE/nowcolor.png");

	//������
	g_Use = true;
	g_w = TEXTURE_WIDTH;
	g_h = TEXTURE_HEIGHT;
	g_Pos = D3DXVECTOR3(200.0f, 50.0f, 0.0f);

	g_rgba[0] = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
	g_rgba[1] = D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f);
	g_rgba[2] = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	g_rgba[3] = D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f);

	g_Color = 0;	// �X�R�A�̏�����

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitColor(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateColor(void)
{
	g_Color2 = g_Color;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawColor(void)
{
	//�L�����t���O��ON�Ȃ�`�悷��
	if (g_Use)
	{

		// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
		float px = g_Pos.x;	// �\���ʒuX
		float py = g_Pos.y;				// �\���ʒuY
		float pw = g_w;					// �\����
		float ph = g_h;					// �\������

		float tw = 0.0f;		// �e�N�X�`���̕�
		float th = 0.0f;		// �e�N�X�`���̍���
		float tx = 1.0f;			// �e�N�X�`���̍���X���W
		float ty = 1.0f;			// �e�N�X�`���̍���Y���W

	
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�

		DrawSpriteColor(g_TexNo, px, py, pw, ph, tx, ty, tw, th, g_rgba[g_Color]);

	
		DrawSprite(g_TexNow, 100.0f, 50.0f, 150.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f);


	}


	
	
}

//=============================================================================
// �X�R�A�����Z����
// ����:add :�ǉ�����_���B�}�C�i�X���\
//=============================================================================
void AddColor(int add)
{
	g_Color = add;
}
