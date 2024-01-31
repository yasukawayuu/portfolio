#include "stage_kyuubi_2.h"
#include "sound1.h"


#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 8	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

static int   g_BGM_kyuubi2 = 0;		// BGM識別子


void STAGE_KYUUBI2::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagekyuubi/kyuubibg-1.png");
	m_Texturebg2 = LoadTexture((char*)"data/TEXTURE/stage/stagekyuubi/kyuubibg-2.png");
	m_Textureroof = LoadTexture((char*)"data/TEXTURE/stage/stagekyuubi/haikei_kyuubi.png");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagekyuubi/yane.png");


	g_BGM_kyuubi2 = LoadSound((char*)"data/BGM/vs九尾2.wav"); //タイトルBGM


	

	m_pos[0] = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	m_wh[0] = D3DXVECTOR2(1920.0f, 216.0f);

	m_pos[1] = D3DXVECTOR2(1770.0f, SCREEN_HEIGHT / 2 - 100.0f);
	m_wh[1] = D3DXVECTOR2(400.0f, 100.0f);

	m_pos[2] = D3DXVECTOR2(150.0f, SCREEN_HEIGHT / 2 - 100.0f);
	m_wh[2] = D3DXVECTOR2(400.0f, 100.0f);

	m_bguse = false;

	m_blocktype = 0;
}

void STAGE_KYUUBI2::Uninit(void)
{
	StopSound(g_BGM_kyuubi2);
	StopSoundAll();
}

void STAGE_KYUUBI2::Update(void)
{

	if (*m_kyuubi->GetNineFoxHp() < 8)
	{
		if (m_KyuubiBGMSoundFlag2 == false)
		{
			StopSoundAll();
			//255(-1)をループ指定すると無限ループ
			PlaySound(g_BGM_kyuubi2, -1);
			SetVolume(g_BGM_kyuubi2, 0.5);
			m_KyuubiBGMSoundFlag2 = true;
		}
	}
}

void STAGE_KYUUBI2::UpdateBG(void)
{
	if (*m_kyuubi->GetNineFoxHp() < 4)
	{
		m_bguse = true;

	}
}

void STAGE_KYUUBI2::Draw(void)
{
	//ステージ描画
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	if (m_bguse == true)
	{
		DrawSpriteLeftTop(m_Texturebg2,
			0.0f,
			0.0f,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	

	
	
	DrawSpriteLeftTop(m_Textureroof,
		m_base->x + 0.0f,
		m_base->y + 0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT + 30.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

/*for (int i = 0; i < 3; i++)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos[i].x,
			m_base->y + m_pos[i].y,
			m_wh[i].x, m_wh[i].y,
			0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
	}*/

	DrawSpriteLeftTop(m_Texturefooting,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	


}

D3DXVECTOR2 * STAGE_KYUUBI2::GetStagePos(void)
{
	return m_pos;
}

D3DXVECTOR2 * STAGE_KYUUBI2::GetStageWh(void)
{
	return m_wh;
}


