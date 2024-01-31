#include "stage_tengu.h"
#include "sound1.h"


#define DIVIDE_X 8	//‰¡‚Ì•ªŠ„”
#define DIVIDE_Y 8	//c‚Ì•ªŠ„”

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

void STAGE_TENGU::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagetengu1.jpg");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagenormal3footing.png");
	m_Texturerock = LoadTexture((char*)"data/TEXTURE/stage/stagenormal3rock.png");

	m_pos[0] = D3DXVECTOR2(SCREEN_WIDTH / 8, SCREEN_HEIGHT - 125);
	m_wh[0] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	m_pos[1] = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[1] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	m_pos[2] = D3DXVECTOR2(SCREEN_WIDTH * 0.875f, SCREEN_HEIGHT - 125);
	m_wh[2] = D3DXVECTOR2(SCREEN_WIDTH / 3, 128.0f);

	m_blocktype = 0;

	m_StopBGMSoundFlag=false;
	
}

void STAGE_TENGU::Uninit(void)
{
	
}

void STAGE_TENGU::Update(void)
{
	if (m_StopBGMSoundFlag == false)
	{
		StopSoundAll();
		m_StopBGMSoundFlag == true;
	}
}

void STAGE_TENGU::Draw(void)
{
	//ƒXƒe[ƒW•`‰æ
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		480.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + 720.0f,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		480.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + 1360.0f,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		550.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	/*for (int i = 0; i < NUM_BLOCKTENGU; i++)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos[i].x,
			m_base->y + m_pos[i].y,
			m_wh[i].x, m_wh[i].y,
			0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
	}*/
}

D3DXVECTOR2 * STAGE_TENGU::GetStagePos(void)
{
	return m_pos;
}

D3DXVECTOR2 * STAGE_TENGU::GetStageWh(void)
{
	return m_wh;
}


