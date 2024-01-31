#include "stage_tutorial.h"


#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 8	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

void STAGE_TUTORIAL::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1bg.jpg");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1footing.png");
	m_Texturerock = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1rock.png");

	// 0-1
	m_pos[0] = D3DXVECTOR2(SCREEN_WIDTH / 5 - 48.0f , SCREEN_HEIGHT - 125);
	m_wh[0] = D3DXVECTOR2((120.0f * 6), 128.0f);

	m_pos[1] = D3DXVECTOR2(SCREEN_WIDTH / 5 * 4 + 48, SCREEN_HEIGHT - 125);
	m_wh[1] = D3DXVECTOR2((120.0f * 6), 128.0f);

	//// 0-2
	m_pos[2] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[2] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	m_pos[3] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 6 * 2, SCREEN_HEIGHT - 265);
	m_wh[3] = D3DXVECTOR2(SCREEN_WIDTH / 2, 140.0f);

	m_pos[4] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 6 * 3 - 80, SCREEN_HEIGHT - 410);
	m_wh[4] = D3DXVECTOR2(SCREEN_WIDTH / 4, 140.0f);

	//// 0-3

	m_pos[5] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[5] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	//// 0-4

	m_pos[6] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[6] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	m_pos[7] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 80);
	m_wh[7] = D3DXVECTOR2(SCREEN_WIDTH / 6, 128.0f);

	m_blocktype = 0;

}

void STAGE_TUTORIAL::Uninit(void)
{

}

void STAGE_TUTORIAL::Draw(void)
{
	//ステージ描画
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < 3; i++)
	{
		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE4 + SCREEN_WIDTH / 2 - 160,
			m_base->y + SCREEN_HEIGHT / 2 - 180 + (216.0f * (i + 1)),
			320.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		396.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + 396.0f,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		300.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	

	for (int i = 0; i < 17; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + SCREEN_WIDTH / 2 + 265 + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	//-------------------------------------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE2 + 160 + 396 * i,
			m_base->y + SCREEN_HEIGHT - 360.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE2 + 160 + 396 * i,
			m_base->y + SCREEN_HEIGHT - 360.0f + 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE2 + SCREEN_WIDTH / 2 - 320,
		m_base->y + SCREEN_HEIGHT - 510.0f,
		480.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE2 + SCREEN_WIDTH / 2 - 320,
			m_base->y + SCREEN_HEIGHT - 510.0f + (216.0f * (i + 1)),
			480.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	//------------------------------------------------------------------------
	
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + SCREEN_WIDTH / 2 - 160,
		m_base->y + SCREEN_HEIGHT / 2 - 180,
		320.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	


	/*for (int i = 0; i < NUM_BLOCKTUTORIAL; i++)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos[i].x,
			m_base->y + m_pos[i].y,
			m_wh[i].x, m_wh[i].y,
			0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
	}*/
}

D3DXVECTOR2 * STAGE_TUTORIAL::GetStagePos(void)
{
	return m_pos;
}

D3DXVECTOR2 * STAGE_TUTORIAL::GetStageWh(void)
{
	return m_wh;
}


