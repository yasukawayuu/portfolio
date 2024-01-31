#include "stage_nomal2.h"


#define DIVIDE_X 8	//���̕�����
#define DIVIDE_Y 8	//�c�̕�����

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

void STAGE_NOMAL2::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagenormal2bg.jpg");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagenormal2footing.png");
	m_Texturerock = LoadTexture((char*)"data/TEXTURE/stage/stagenormal2rock.png");

	// 1-2-1
	m_pos[0] = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh [0] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	// 1-2-2
	m_pos[1] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh [1] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);


	// 1-2-3
	m_pos[2] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh [2] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	m_pos[3] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT - 253);
	m_wh [3] = D3DXVECTOR2(SCREEN_WIDTH / 2, 128.0f);

	m_pos[4] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH * 0.875f, SCREEN_HEIGHT - 381);
	m_wh [4] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	// 1-2-4
	m_pos[5] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 8, SCREEN_HEIGHT - 190);
	m_wh [5] = D3DXVECTOR2(SCREEN_WIDTH / 4, 512.0f);

	m_pos[6] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT - 125);
	m_wh [6] = D3DXVECTOR2(SCREEN_WIDTH / 2, 128.0f);

	m_blocktype = 0;
}

void STAGE_NOMAL2::Uninit(void)
{
	
}

void STAGE_NOMAL2::Draw(void)
{
	//�X�e�[�W�`��
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	
	
	for (int i = 0; i < 15; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}


//---------------------------------------------------------------------
	for (int i = 0; i < 2; i++)
	{

		
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE3 + SCREEN_WIDTH / 2 + (396 * i),
			m_base->y + SCREEN_HEIGHT - 340.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE3 + SCREEN_WIDTH / 2 + 1 + (396 * i),
			m_base->y + SCREEN_HEIGHT - 124.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		
	}

	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE3 + SCREEN_WIDTH / 2 + 480 + (396 * i),
			m_base->y + SCREEN_HEIGHT / 2 + 70,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE3 + SCREEN_WIDTH / 2 + 481 + (396 * i),
			m_base->y + SCREEN_HEIGHT / 2 + 286,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE3 + SCREEN_WIDTH / 2 + 481 + (396 * i),
			m_base->y + SCREEN_HEIGHT / 2 + 286 + 216,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE4,
			m_base->y + SCREEN_HEIGHT / 2 + 286 + 216 + (216.0f * (i + 1)),
			480.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + 290,
		m_base->y + SCREEN_HEIGHT / 2 + 70,
		190.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE4 + 290,
			m_base->y + SCREEN_HEIGHT / 2 + 60 + (216.0f * (i + 1)),
			190.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	
	for (int i = 0; i < 3; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE4 + SCREEN_WIDTH / 2 + (396 * i),
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	/*for (int i = 0; i < NUM_BLOCKNORMAL2; i++)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos[i].x,
			m_base->y + m_pos[i].y,
			m_wh[i].x, m_wh[i].y,
			0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
	}*/

//----------------------------------------------------------------------------
	

	
}

D3DXVECTOR2 * STAGE_NOMAL2::GetStagePos(void)
{
	return m_pos;
}

D3DXVECTOR2 * STAGE_NOMAL2::GetStageWh(void)
{
	return m_wh;
}

