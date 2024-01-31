#include "stage_nomal4.h"


#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 8	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

void STAGE_NOMAL4::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagenormal4bg.jpg");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1footing.png");
	m_Texturerock = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1rock.png");

	// 1-4-1
	m_pos[0] = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[0] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	// 1-4-2
	m_pos[1] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[1] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	m_pos[2] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 8, SCREEN_HEIGHT - 701);
	m_wh[2] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	// 1-4-3

	m_pos[3] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH / 8, SCREEN_HEIGHT - 125);
	m_wh[3] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	m_pos[4] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[4] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	m_pos[5] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH * 0.875f, SCREEN_HEIGHT - 125);
	m_wh[5] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	// 1-4-4

	m_pos[6] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 8, SCREEN_HEIGHT - 125);
	m_wh[6] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	m_pos[7] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH * 0.625f, SCREEN_HEIGHT - 317);
	m_wh[7] = D3DXVECTOR2(SCREEN_WIDTH / 4, 384.0f);

	m_pos[8] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT - 125);
	m_wh [8] = D3DXVECTOR2(SCREEN_WIDTH / 2, 128.0f);



	m_blocktype = 0;
	
}

void STAGE_NOMAL4::Uninit(void)
{
	
}

void STAGE_NOMAL4::Draw(void)
{
	//ステージ描画
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	/*for (int i = 0; i < NUM_BLOCKNORMAL4; i++)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos[i].x,
			m_base->y + m_pos[i].y,
			m_wh[i].x, m_wh[i].y,
			0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
	}*/

	//-------------------------------------------------------------------
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE2,
		m_base->y + SCREEN_HEIGHT / 2 - 250,
		480.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < 3; i++)
	{
		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE2,
			m_base->y + SCREEN_HEIGHT / 2 - 250 + (216 * (i + 1)),
			480.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	//-------------------------------------------------------------------

	for (int i = 0; i < 10; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + 396.0f * 10,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		360.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE3 + 720.0f,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		480.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	//-------------------------------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE3 + 1440.0f + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
//------------------------------------------------------------------
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE3 + 1440.0f + 396.0f * 2,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		170.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	
	
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + SCREEN_WIDTH / 2,
		m_base->y + SCREEN_HEIGHT / 2,
		480.0f, 260.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH / 2 ,
		m_base->y + SCREEN_HEIGHT / 2 + 260.0f,
		480.0f, 280.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + SCREEN_WIDTH / 2 + 480,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		470.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	
	
}

D3DXVECTOR2 * STAGE_NOMAL4::GetStagePos(void)
{
	return m_pos;
}

D3DXVECTOR2 * STAGE_NOMAL4::GetStageWh(void)
{
	return m_wh;
}


