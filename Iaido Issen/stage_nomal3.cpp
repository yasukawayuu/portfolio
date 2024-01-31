#include "stage_nomal3.h"


#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 8	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

void STAGE_NOMAL3::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagenormal3bg.jpg");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagenormal3footing.png");
	m_Texturerock = LoadTexture((char*)"data/TEXTURE/stage/stagenormal3rock.png");

	// 1-3-1
	m_pos[0] = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[0] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	// 1-3-2
	m_pos[1] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[1] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);


	// 1-3-3
	m_pos[2] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH / 4 - 22.5f, SCREEN_HEIGHT - 125);
	m_wh [2] = D3DXVECTOR2(SCREEN_WIDTH / 2 - 45.0f, 128.0f);

	m_pos[3] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH * 0.875f, SCREEN_HEIGHT - 125);
	m_wh [3] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);


	// 1-3-4
	m_pos[4] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 6, SCREEN_HEIGHT - 125);
	m_wh [4] = D3DXVECTOR2(SCREEN_WIDTH / 3, 128.0f);

	m_pos[5] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 3, SCREEN_HEIGHT - 250);
	m_wh [5] = D3DXVECTOR2(SCREEN_WIDTH / 16, 384.0f);

	m_pos[6] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH * 0.625f, SCREEN_HEIGHT - 317);
	m_wh[6] = D3DXVECTOR2(SCREEN_WIDTH / 4, 384.0f);

	m_pos[7] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT - 125);
	m_wh [7] = D3DXVECTOR2(SCREEN_WIDTH / 2, 128.0f);

	

	m_blocktype = 0;

}

void STAGE_NOMAL3::Uninit(void)
{
	
}

void STAGE_NOMAL3::Draw(void)
{
	//ステージ描画
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);


	for (int i = 0; i < 12; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i < 3; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE3 + SCREEN_WIDTH * 0.875f - 245.0f + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE4 + SCREEN_WIDTH * 0.75f - 245.0f + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	
	//----------------------------------------------------------
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + SCREEN_WIDTH / 3 - 61.5f,
		m_base->y + SCREEN_HEIGHT - 470.0f,
		123.75f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	
	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH / 3 - 61.5f,
		m_base->y + SCREEN_HEIGHT - 254.0f,
		123.75f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH / 3 - 61.5f,
		m_base->y + SCREEN_HEIGHT - 38.0f,
		123.75f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	//----------------------------------------------------------



	//----------------------------------------------------------
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + SCREEN_WIDTH * 0.625f - 245.0f,
		m_base->y + SCREEN_HEIGHT - 530.0f,
		247.5f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);


	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH * 0.625f - 245.0f,
		m_base->y + SCREEN_HEIGHT - 314.0f,
		247.5f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH * 0.625f - 245.0f,
		m_base->y + SCREEN_HEIGHT - 98.0f,
		247.5f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);


	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + SCREEN_WIDTH * 0.625f ,
		m_base->y + SCREEN_HEIGHT - 530.0f,
		247.5f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH * 0.625f,
		m_base->y + SCREEN_HEIGHT - 314.0f,
		247.5f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH * 0.625f,
		m_base->y + SCREEN_HEIGHT - 98.0f,
		247.5f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	//------------------------------------------------------


	/*for (int i = 0; i < NUM_BLOCKNORMAL3; i++)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos[i].x,
			m_base->y + m_pos[i].y,
			m_wh[i].x, m_wh[i].y,
			0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
	}*/


	
}

D3DXVECTOR2 * STAGE_NOMAL3::GetStagePos(void)
{
	return m_pos;
}

D3DXVECTOR2 * STAGE_NOMAL3::GetStageWh(void)
{
	return m_wh;
}


