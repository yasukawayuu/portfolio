#include "stage_nomal1.h"
#include "sound1.h"

#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 8	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

static int   g_BGM_nomal = 0;		// BGM識別子


void STAGE_NOMAL1::Init(void)
{
	m_Texture = LoadTexture((char*)"data/TEXTURE/danjyon2.png");
	m_Texturebg = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1bg.jpg");
	m_Texturefooting = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1footing.png");
	m_Texturerock = LoadTexture((char*)"data/TEXTURE/stage/stagenormal1rock.png");
	m_TextureTutorial1 = LoadTexture((char*)"data/TEXTURE/tutorial/1.png");
	m_TextureTutorial2 = LoadTexture((char*)"data/TEXTURE/tutorial/2.png");

	m_nomalBGMSoundFlag = false;

	g_BGM_nomal = LoadSound((char*)"data/BGM/道中.wav"); //タイトルBGM

	PlaySound(g_BGM_nomal, -1);
	SetVolume(g_BGM_nomal, 0.5);


	// 1-1-1
	m_pos[0] = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[0] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	// 1-1-2
	m_pos[1] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT - 125);
	m_wh[1] = D3DXVECTOR2(SCREEN_WIDTH / 2, 128.0f);

	m_pos[2] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT - 253);
	m_wh[2] = D3DXVECTOR2(SCREEN_WIDTH / 5.0f, 256.0f);

	m_pos[3] = D3DXVECTOR2(STAGE2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 125);
	m_wh[3] = D3DXVECTOR2(SCREEN_WIDTH, 128.0f);

	// 1-1-3
	m_pos[4] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH / 8, SCREEN_HEIGHT - 125);
	m_wh[4] = D3DXVECTOR2(SCREEN_WIDTH / 4, 128.0f);

	m_pos[5] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH * 0.62f, SCREEN_HEIGHT - 189);
	m_wh[5] = D3DXVECTOR2(SCREEN_WIDTH / 4.0, 256.0f);

	m_pos[6] = D3DXVECTOR2(STAGE3 + SCREEN_WIDTH-(SCREEN_WIDTH/6), SCREEN_HEIGHT - 125);
	m_wh[6] = D3DXVECTOR2(SCREEN_WIDTH/3, 128.0f);
	// 1-1-4
	m_pos[7] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 16, SCREEN_HEIGHT - 125);
	m_wh[7] = D3DXVECTOR2(SCREEN_WIDTH / 8, 128.0f);

	m_pos[8] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - 253);
	m_wh[8] = D3DXVECTOR2(SCREEN_WIDTH / 4, 384.0f);

	m_pos[9] = D3DXVECTOR2(STAGE4 + SCREEN_WIDTH * 0.81, SCREEN_HEIGHT - 125);
	m_wh[9] = D3DXVECTOR2(SCREEN_WIDTH * 0.38, 128.0f);

	m_blocktype = 0;

}

void STAGE_NOMAL1::Uninit(void)
{

}

void STAGE_NOMAL1::Draw(void)
{
	//ステージ描画
	DrawSpriteLeftTop(m_Texturebg,
		0.0f,
		0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	

	for (int i = 0; i < 8; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i < 1; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE2 + SCREEN_WIDTH * 0.75f - 480.0f + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 412.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE2 + SCREEN_WIDTH * 0.75f - 480.0f + 396.0f * i,
			m_base->y + SCREEN_HEIGHT - 196.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE2 + SCREEN_WIDTH * 0.5f + 396.0f,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		396.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE2 + SCREEN_WIDTH * 0.5f + 396.0f*2,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		396.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	/*DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE2 + SCREEN_WIDTH * 0.75f - 480.0f + 396.0f * 2,
		m_base->y + SCREEN_HEIGHT - 196.0f,
		170.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);*/

		//--------------------------------------------------------------------
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE3,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		480.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < 1; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE3 + SCREEN_WIDTH / 2 + (470.0f * i),
			m_base->y + SCREEN_HEIGHT - 342.0f,
			470.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteLeftTop(m_Texturerock,
			m_base->x + STAGE3 + SCREEN_WIDTH / 2 + (470.0f * i),
			m_base->y + SCREEN_HEIGHT - 126.0f,
			470.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE3 + SCREEN_WIDTH * 0.5f + 470.0f,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		396.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE3 + 1800,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		396.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);
	//---------------------------------------------------------------------------------
	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4,
		m_base->y + SCREEN_HEIGHT - 216.0f,
		240.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);


	DrawSpriteLeftTop(m_Texturefooting,
		m_base->x + STAGE4 + SCREEN_WIDTH / 2 - 240,
		m_base->y + SCREEN_HEIGHT - 472.0f,
		470.0f, 216.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(m_Texturerock,
		m_base->x + STAGE4 + SCREEN_WIDTH / 2 - 240,
		m_base->y + SCREEN_HEIGHT - 256.0f,
		470.0f, 260.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < 2; i++)
	{
		DrawSpriteLeftTop(m_Texturefooting,
			m_base->x + STAGE4 + SCREEN_WIDTH / 2 + 230 + (396.0f * i),
			m_base->y + SCREEN_HEIGHT - 216.0f,
			396.0f, 216.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}

	/*for (int i = 0; i < NUM_BLOCKNORMAL1; i++)
	{
		DrawSprite(m_Texture,
			m_base->x + m_pos[i].x,
			m_base->y + m_pos[i].y,
			m_wh[i].x, m_wh[i].y,
			0.0f, 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
	}*/
	if (m_TutorialFrame >= 20)
	{
		m_TutorialPtn += 1.0f;
		m_TutorialFrame = 0;
	}
	m_TutorialFrame++;

	// コントローラーのチュートリアルを描画
	DrawSpriteLeftTop(m_TextureTutorial1,
		m_base->x + 30,
		m_base->y + (SCREEN_HEIGHT / 2) - 200,
		270.0f, 170.0f,
		m_TutorialPtn / 3, 0.0f, 1.0f / 3, 1.0f);

	DrawSpriteLeftTop(m_TextureTutorial2,
		m_base->x + STAGE2 + 30,
		m_base->y + (SCREEN_HEIGHT / 2) - 200,
		230.0f, 130.0f,
		m_TutorialPtn / 3, 0.0f, 1.0f / 3, 1.0f);

	DrawSpriteLeftTop(m_TextureTutorial1,
		m_base->x + (STAGE2 + 30) + 240,
		m_base->y + (SCREEN_HEIGHT / 2) - 200,
		230.0f, 130.0f,
		m_TutorialPtn / 3, 0.0f, 1.0f / 3, 1.0f);
}

D3DXVECTOR2 * STAGE_NOMAL1::GetStagePos(void)
{
	return m_pos;
}

D3DXVECTOR2 * STAGE_NOMAL1::GetStageWh(void)
{
	return m_wh;
}


