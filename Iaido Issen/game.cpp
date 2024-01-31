#include "game.h"
#include "input.h"

GAME::~GAME()
{

}

void GAME::Init(void)
{
	m_gameover.InitGameOver();
	m_Player.Init();
	m_Stage.Init();
	m_Enemy.Init();
	m_Camera.Init();
	m_Slash.Init();
	m_Obstacle.Init();
	m_Effect.Init();
	ReChallenge();
}

void GAME::Uninit(void)
{
	m_gameover.UninitGameOver();
	m_Effect.Uninit();
	m_Player.Uninit();
	m_Stage.Uninit();
	m_Enemy.Uninit();
	m_Camera.Uninit();
	m_Slash.Uninit();
	m_Obstacle.Uninit();
}

void GAME::Update(void)
{

	if (GetKeyboardTrigger(DIK_1))
	{
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		m_Stage.SetStageNum(STAGENORMAL_1);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		m_Stage.SetStageNum(STAGENORMAL_2);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		m_Stage.SetStageNum(STAGENORMAL_3);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		m_Stage.SetStageNum(STAGENORMAL_4);
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		m_Stage.SetStageNum(STAGENORMAL_5);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		m_Enemy.GetTengu()->Init();
		m_Player.Init();
		m_Stage.SetStageNum(STAGETENGUU_1);
	}
	if (GetKeyboardTrigger(DIK_7))
	{
		m_Enemy.GetKyuubi()->Init(10);
		m_Player.Init();
		m_Stage.SetStageNum(STAGEKYUUBI_1);
	}
	if (GetKeyboardTrigger(DIK_8))
	{
		m_Enemy.GetKyuubi()->Init(7);
		*m_Enemy.GetKyuubi()->GetHalf() = 4;
		m_Player.Init();
		m_Stage.SetStageNum(STAGEKYUUBI_2);
	}
	if (GetKeyboardTrigger(DIK_9))
	{
		m_Enemy.GetKyuubi()->Init(3);
		*m_Enemy.GetKyuubi()->GetHalf() = 2;
		m_Player.Init();
		m_Stage.SetStageNum(STAGEKYUUBI_3);
	}


	if (*m_Player.GetPlayerUse() == false)
	{
		m_gameover.UpdateGameOver();
		if (*m_gameover.GetChallenge() == true)
		{
			*m_gameover.GetChallenge() = false;
			m_gameover.UninitGameOver();
			m_gameover.InitGameOver();
			ReChallenge();
		}
	}
	else
	{
		m_Collision.UpdateCollsion();
		m_Stage.Update();
		m_Player.Update();
		m_Enemy.Update();
		m_Camera.Update();
		m_Slash.Update();
		m_Obstacle.Update();
		m_Effect.Update();
	}
}

void GAME::Draw(void)
{
	if (*m_Player.GetPlayerUse() == false)
	{
		m_gameover.DrawGameOver();
	}
	else
	{
		m_Stage.Draw();
		m_Player.Draw();
		m_Enemy.Draw();
		m_Camera.Draw();
		m_Slash.Draw();
		m_Effect.Draw();
	}
	//m_Obstacle.Draw();
}

void GAME::ReChallenge(void)
{
	switch (m_Stage.GetStageNum())
	{
	case STAGETUTORIAL_1:
		m_Player.Init();
		break;
	case STAGENORMAL_1:
		m_Stage.GetStageNoraml1()->Init();
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		break;
	case STAGENORMAL_2:
		m_Stage.GetStageNoraml1()->Init();
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		break;
	case STAGENORMAL_3:
		m_Stage.GetStageNoraml1()->Init();
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		break;
	case STAGENORMAL_4:
		m_Stage.GetStageNoraml1()->Init();
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		break;
	case STAGENORMAL_5:
		m_Stage.GetStageNoraml1()->Init();
		m_Enemy.Init();
		m_Player.Init();
		m_Camera.Init();
		break;
	case STAGETENGUU_1:
		m_Enemy.GetTengu()->Init();
		m_Player.Init();
		break;
	case STAGEKYUUBI_1:
		m_Stage.GetStageKyuubi1()->Init();
		m_Enemy.GetKyuubi()->Init(10);
		m_Player.Init();
		break;
	case STAGEKYUUBI_2:
		m_Stage.GetStageKyuubi2()->Init();
		m_Enemy.GetKyuubi()->Init(7);
		*m_Enemy.GetKyuubi()->GetHalf() = 4;
		m_Player.Init();
		break;
	case STAGEKYUUBI_3:
		m_Stage.GetStageKyuubi2()->Init();
		m_Enemy.GetKyuubi()->Init(3);
		*m_Enemy.GetKyuubi()->GetHalf() = 2;
		m_Player.Init();
		break;
	}
}