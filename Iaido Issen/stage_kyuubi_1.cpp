#include "stage_kyuubi_1.h"
#include "sound1.h"


#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 8	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

static int   g_BGM_kyuubi1 = 0;		// BGM識別子


void STAGE_KYUUBI1::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagekyuubi/asiba.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagekyuubi/kyuubibg-1.png");
	m_Texturehusuma = LoadTexture((char*)"data/TEXTURE/stage/stagekyuubi/husuma.png");

	g_BGM_kyuubi1= LoadSound((char*)"data/BGM/vs九尾1.wav"); //タイトルBGM

	m_KyuubiBGMSoundFlag = false;
	
	m_pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	m_wh = D3DXVECTOR2(1920.0f, 216.0f);
	m_blocktype = 0;
	
}

void STAGE_KYUUBI1::Uninit(void)
{
	m_KyuubiBGMSoundFlag = false;
	StopSound(g_BGM_kyuubi1);
}

void STAGE_KYUUBI1::Update(void)
{
	if (m_KyuubiBGMSoundFlag == false)
	{
		StopSoundAll();
		//255(-1)をループ指定すると無限ループ
		PlaySound(g_BGM_kyuubi1, -1);
		m_KyuubiBGMSoundFlag = true;
	}

}

void STAGE_KYUUBI1::Draw(void)
{
	//ステージ描画
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturehusuma,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(m_Texture,
		m_base->x + m_pos.x,
		m_base->y + m_pos.y,
		m_wh.x, m_wh.y,
		0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);



	for (int i = 0; i < 7; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + 297.0f * i,
			m_base->y + SCREEN_HEIGHT - 250.0f,
			396.0f, 250.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

}

D3DXVECTOR2 * STAGE_KYUUBI1::GetStagePos(void)
{
	return &m_pos;
}

D3DXVECTOR2 * STAGE_KYUUBI1::GetStageWh(void)
{
	return &m_wh;
}


