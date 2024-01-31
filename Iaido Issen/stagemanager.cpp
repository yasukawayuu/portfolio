#include "stagemanager.h"
#include "GameOver.h"
#include "input.h"
#include "fade.h"


void STAGEMANAGER::Init(void)
{
	m_stagenum = STAGENORMAL_1;
	m_nowstage = m_stagenum;

	m_stagetutorial1.Init();
	m_stagenormal1.Init();
	m_stagenormal2.Init();
	m_stagenormal3.Init();
	m_stagenormal4.Init();
	m_stagenormal5.Init();
	m_stagetengu.Init();
	m_stagekyuubibi1.Init();
	m_stagekyuubibi2.Init();
}

void STAGEMANAGER::Uninit(void)
{
	m_stagetutorial1.Uninit();
	m_stagenormal1.Uninit();
	m_stagenormal2.Uninit();
	m_stagenormal3.Uninit();
	m_stagenormal4.Uninit();
	m_stagenormal5.Uninit();
	m_stagetengu.Uninit();
	m_stagekyuubibi1.Uninit();
	m_stagekyuubibi2.Uninit();
}

void STAGEMANAGER::Update(void)
{
	

	if (m_playerpos->x > SCREEN_WIDTH * 4)
	{
		switch (m_stagenum)
		{
		case STAGETUTORIAL_1:
			*m_playerpos = D3DXVECTOR2(100.0f, 0.0f);
			m_stagenum = STAGENORMAL_1;
			*m_playerlive = 2;
			*m_playerhp = 5;
			break;
		case STAGENORMAL_1:	
			*m_playerpos = D3DXVECTOR2(100.0f, 0.0f);
			m_stagenum = STAGENORMAL_2;
			*m_playerlive = 2;
			*m_playerhp = 5;
			break;
		case STAGENORMAL_2:
			*m_playerpos = D3DXVECTOR2(100.0f, 0.0f);
			m_stagenum = STAGENORMAL_3;
			*m_playerlive = 2;
			*m_playerhp = 5;
			break;
		case STAGENORMAL_3:
			*m_playerpos = D3DXVECTOR2(100.0f, 0.0f);
			m_stagenum = STAGENORMAL_4;
			*m_playerlive = 2;
			*m_playerhp = 5;
			break;
		case STAGENORMAL_4:
			*m_playerpos = D3DXVECTOR2(100.0f, 0.0f);
			m_stagenum = STAGENORMAL_5;
			*m_playerlive = 2;
			*m_playerhp = 5;
			break;
		case STAGENORMAL_5:
			*m_playerpos = D3DXVECTOR2(100.0f, 0.0f);
			m_stagenum = STAGETENGUU_1;
			*m_playerlive = 2;
			*m_playerhp = 5;
			break;
		}
	}
		

	if (m_tengu->GetTengu()->hp < 1 && m_stagenum == STAGETENGUU_1)
	{
		m_stagenum = STAGEKYUUBI_1;
		*m_playerlive = 2;
		*m_playerhp = 5;
		*m_playerpos = D3DXVECTOR2(100.0f, 0.0f);
	}
		

	if(*m_kyuubi->GetNineFoxHp() < 8)
		m_stagenum = STAGEKYUUBI_2;

	if(*m_kyuubi->GetNineFoxHp() < 4)
		m_stagenum = STAGEKYUUBI_3;
		
	if (*m_kyuubi->GetNineFoxHp() < 1)
		SceneTransition(SCENE_RESULT);

	switch (m_stagenum)
	{

	case STAGEKYUUBI_1:
		m_stagekyuubibi1.Update();
		break;
	case STAGEKYUUBI_2:
		m_stagekyuubibi2.Update();
		break;
	case STAGEKYUUBI_3:
		m_stagekyuubibi2.UpdateBG();
		break;
	}

}

void STAGEMANAGER::Draw(void)
{
	switch (m_stagenum)
	{
	case STAGETUTORIAL_1:
		m_stagetutorial1.Draw();
		break;
	case STAGENORMAL_1:
		m_stagenormal1.Draw();
		break;
	case STAGENORMAL_2:
		m_stagenormal2.Draw();
		break;
	case STAGENORMAL_3:
		m_stagenormal3.Draw();
		break;
	case STAGENORMAL_4:
		m_stagenormal4.Draw();
		break;
	case STAGENORMAL_5:
		m_stagenormal5.Draw();
		break;
	case STAGETENGUU_1:
		m_stagetengu.Draw();
		break;
	case STAGEKYUUBI_1:
		m_stagekyuubibi1.Draw();
		break;
	case STAGEKYUUBI_2:
		m_stagekyuubibi2.Draw();
		break;
	case STAGEKYUUBI_3:
		m_stagekyuubibi2.Draw();
		break;
	}
	
}

void STAGEMANAGER::SetStageNum(STAGE_NUM stagenum)
{
	m_stagenum = stagenum;
}
