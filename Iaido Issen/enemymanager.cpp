#include "enemymanager.h"

void ENEMYMANAGER::Init(void)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_enemy[i].Init();
	}

	for (int i = 0; i < ENEMY_BIRD_NUM; i++)
	{
		m_enemybird[i].Init();
	}

	m_kyuubi.Init(10);
	m_tengu.Init();
;
	SetStage2NormalEnemyBird();
	SetStage3NormalEnemyBird();
	SetStage4NormalEnemyBird();
	SetStage5NormalEnemyBird();

	SetStage1NormalEnemy();
	SetStage2NormalEnemy();
	SetStage3NormalEnemy();
	SetStage4NormalEnemy();
	SetStage5NormalEnemy();
}

void ENEMYMANAGER::Uninit(void)
{
	for (int i = 0; i < ENEMY_BIRD_NUM; i++)
	{
		m_enemybird[i].Uninit();
	}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_enemy[i].Uninit();
	}
	m_kyuubi.Uninit();	
	m_tengu.Uninit();
}

void ENEMYMANAGER::Update(void)
{
	if (m_playerpos->x > 0 && m_playerpos->x < SCREEN_WIDTH)
	{
		switch (m_stage->GetStageNum())
		{
		case STAGENORMAL_1:
			m_enemy[0].Update();
			break;
		case STAGENORMAL_2:
			m_enemybird[0].Update();
			break;
		case STAGENORMAL_3:
			m_enemy[8].Update();

			m_enemybird[4].Update();
			break;
		case STAGENORMAL_4:
			m_enemy[11].Update();

			m_enemybird[10].Update();
			m_enemybird[11].Update();
			break;
		case STAGENORMAL_5:
			m_enemy[14].Update();
			m_enemy[15].Update();

			m_enemybird[17].Update();
			break;
		case STAGETENGUU_1:
			m_tengu.Update();
			break;
		case STAGEKYUUBI_1:
			m_kyuubi.Update();
			m_kyuubi.NineFoxPattenrn1();
			break;
		case STAGEKYUUBI_2:
			m_kyuubi.Update();
			m_kyuubi.NineFoxPattenrn2();
			break;
		case STAGEKYUUBI_3:
			m_kyuubi.Update();
			m_kyuubi.NineFoxPattenrn3();
			m_kyuubi.NineFoxAvatar();
			break;
		}
	}

	if (m_playerpos->x > SCREEN_WIDTH && m_playerpos->x < SCREEN_WIDTH * 2)
	{
		switch (m_stage->GetStageNum())
		{
		case STAGENORMAL_1:
			m_enemy[1].Update();
			m_enemy[2].Update();
			break;
		case STAGENORMAL_2:
			m_enemy[6].Update();

			m_enemybird[1].Update();
			break;
		case STAGENORMAL_3:
			m_enemy[9].Update();

			m_enemybird[5].Update();
			break;
		case STAGENORMAL_4:
			m_enemybird[12].Update();
			break;
		case STAGENORMAL_5:
			m_enemy[16].Update();

			m_enemybird[18].Update();
			m_enemybird[19].Update();
			m_enemybird[20].Update();
			break;
		}
	}

	if (m_playerpos->x > SCREEN_WIDTH * 2 && m_playerpos->x < SCREEN_WIDTH * 3)
	{
		switch (m_stage->GetStageNum())
		{
		case STAGENORMAL_1:
			m_enemy[3].Update();
			m_enemy[4].Update();
			break;
		case STAGENORMAL_2:
			m_enemybird[2].Update();
			break;
		case STAGENORMAL_3:
			m_enemybird[6].Update();
			m_enemybird[7].Update();
			break;
		case STAGENORMAL_4:
			m_enemy[12].Update();

			m_enemybird[13].Update();
			m_enemybird[14].Update();
			break;
		case STAGENORMAL_5:
			break;
		}
	}

	if (m_playerpos->x > SCREEN_WIDTH * 3 && m_playerpos->x < SCREEN_WIDTH * 4)
	{
		switch (m_stage->GetStageNum())
		{
		case STAGENORMAL_1:
			m_enemy[5].Update();
			break;
		case STAGENORMAL_2:
			m_enemy[7].Update();

			m_enemybird[3].Update();
			break;
		case STAGENORMAL_3:
			m_enemy[10].Update();

			m_enemybird[8].Update();
			m_enemybird[9].Update();
			break;
		case STAGENORMAL_4:
			m_enemy[13].Update();

			m_enemybird[15].Update();
			m_enemybird[16].Update();
			break;
		case STAGENORMAL_5:
			m_enemybird[21].Update();
			m_enemybird[22].Update();
			m_enemybird[23].Update();
			break;
		}
	}

		
}

void ENEMYMANAGER::Draw(void)
{
	switch (m_stage->GetStageNum())
	{
	case STAGENORMAL_1:
		for (int i = 0; i < 6; i++)
		{
			m_enemy[i].Draw();
		}
		break;
	case STAGENORMAL_2:
		for (int i = 6; i < 8; i++)
		{
			m_enemy[i].Draw();
		}

		for (int i = 0; i < 4; i++)
		{
			m_enemybird[i].Draw();
		}
		break;
	case STAGENORMAL_3:
		for (int i = 8; i < 11; i++)
		{
			m_enemy[i].Draw();
		}

		for (int i = 4; i < 10; i++)
		{
			m_enemybird[i].Draw();
		}
		break;
	case STAGENORMAL_4:
		for (int i = 11; i < 14; i++)
		{
			m_enemy[i].Draw();
		}

		for (int i = 10; i < 17; i++)
		{
			m_enemybird[i].Draw();
		}
		break;
	case STAGENORMAL_5:
		for (int i = 14; i < 17; i++)
		{
			m_enemy[i].Draw();
		}

		for (int i = 17; i < 24; i++)
		{
			m_enemybird[i].Draw();
		}
		break;
	case STAGETENGUU_1:
		m_tengu.Draw();
		break;
	case STAGEKYUUBI_1:
		m_kyuubi.Draw();
		break;
	case STAGEKYUUBI_2:
		m_kyuubi.Draw();
		break;
	case STAGEKYUUBI_3:
		m_kyuubi.Draw();
		m_kyuubi.NineFoxAvatarDraw();
		break;
	}

	
	
}

void ENEMYMANAGER::SetStage1NormalEnemy(void)
{
									//どこのブロックか　//表示するかどうか　//どの範囲　//中心点
	m_enemy[0].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml1()->GetStagePos()[0].x + m_stage->GetStageNoraml1()->GetStageWh()[0].x / 2, m_stage->GetStageNoraml1()->GetStagePos()[0].y - 180.0f), true,
		m_stage->GetStageNoraml1()->GetStageWh()[0].x, m_stage->GetStageNoraml1()->GetStagePos()[0].x, m_stage->GetStageNoraml1()->GetStagePos()[0].x);

	m_enemy[1].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml1()->GetStagePos()[1].x + m_stage->GetStageNoraml1()->GetStageWh()[1].x / 2, m_stage->GetStageNoraml1()->GetStagePos()[1].y - 180.0f), true,
		m_stage->GetStageNoraml1()->GetStageWh()[1].x, m_stage->GetStageNoraml1()->GetStagePos()[1].x, m_stage->GetStageNoraml1()->GetStagePos()[1].x);

	m_enemy[2].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml1()->GetStagePos()[2].x + m_stage->GetStageNoraml1()->GetStageWh()[2].x / 2, m_stage->GetStageNoraml1()->GetStagePos()[2].y - 240.0f), true,
		m_stage->GetStageNoraml1()->GetStageWh()[2].x, m_stage->GetStageNoraml1()->GetStagePos()[2].x, m_stage->GetStageNoraml1()->GetStagePos()[2].x);

	m_enemy[3].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml1()->GetStagePos()[4].x + m_stage->GetStageNoraml1()->GetStageWh()[4].x / 2, m_stage->GetStageNoraml1()->GetStagePos()[4].y - 180.0f), true,
		m_stage->GetStageNoraml1()->GetStageWh()[4].x, m_stage->GetStageNoraml1()->GetStagePos()[4].x, m_stage->GetStageNoraml1()->GetStagePos()[4].x);

	m_enemy[4].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml1()->GetStagePos()[5].x + m_stage->GetStageNoraml1()->GetStageWh()[5].x / 2, m_stage->GetStageNoraml1()->GetStagePos()[5].y - 240.0f), true,
		m_stage->GetStageNoraml1()->GetStageWh()[5].x, m_stage->GetStageNoraml1()->GetStagePos()[5].x, m_stage->GetStageNoraml1()->GetStagePos()[5].x);

	m_enemy[5].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml1()->GetStagePos()[8].x + m_stage->GetStageNoraml1()->GetStageWh()[8].x / 2, m_stage->GetStageNoraml1()->GetStagePos()[8].y - 300.0f), true,
		m_stage->GetStageNoraml1()->GetStageWh()[8].x, m_stage->GetStageNoraml1()->GetStagePos()[8].x, m_stage->GetStageNoraml1()->GetStagePos()[8].x);
}

void ENEMYMANAGER::SetStage2NormalEnemy(void)
{
	m_enemy[6].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml2()->GetStagePos()[1].x + m_stage->GetStageNoraml2()->GetStageWh()[1].x / 2, m_stage->GetStageNoraml2()->GetStagePos()[1].y - 180.0f), true,
		m_stage->GetStageNoraml2()->GetStageWh()[1].x, m_stage->GetStageNoraml2()->GetStagePos()[1].x, m_stage->GetStageNoraml2()->GetStagePos()[1].x);

	m_enemy[7].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml2()->GetStagePos()[6].x + m_stage->GetStageNoraml2()->GetStageWh()[6].x / 2, m_stage->GetStageNoraml2()->GetStagePos()[6].y - 180.0f), true,
		m_stage->GetStageNoraml2()->GetStageWh()[6].x, m_stage->GetStageNoraml2()->GetStagePos()[6].x, m_stage->GetStageNoraml2()->GetStagePos()[6].x);
}

void ENEMYMANAGER::SetStage2NormalEnemyBird(void)
{
	m_enemybird[0].SetEnemy(D3DXVECTOR2(1700.0f, 400.0f), true, ENEMYBIRD_THUNDERATTACK);

	m_enemybird[1].SetEnemy(D3DXVECTOR2(3400.0f, 800.0f), true, ENEMYBIRD_UP);

	m_enemybird[2].SetEnemy(D3DXVECTOR2(4800.0f, 300.0f), true, EMEMYBIRD_TURNING);

	m_enemybird[3].SetEnemy(D3DXVECTOR2(6800.0f, 300.0f), true, EMEMYBIRD_TURNING);
}

void ENEMYMANAGER::SetStage3NormalEnemy(void)
{
	m_enemy[8].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml3()->GetStagePos()[0].x + m_stage->GetStageNoraml3()->GetStageWh()[0].x / 2, m_stage->GetStageNoraml3()->GetStagePos()[0].y - 180.0f), true,
		m_stage->GetStageNoraml3()->GetStageWh()[0].x, m_stage->GetStageNoraml3()->GetStagePos()[0].x, m_stage->GetStageNoraml3()->GetStagePos()[0].x);

	m_enemy[9].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml3()->GetStagePos()[1].x + m_stage->GetStageNoraml3()->GetStageWh()[1].x / 2, m_stage->GetStageNoraml3()->GetStagePos()[1].y - 180.0f), true,
		m_stage->GetStageNoraml3()->GetStageWh()[1].x, m_stage->GetStageNoraml3()->GetStagePos()[1].x, m_stage->GetStageNoraml3()->GetStagePos()[1].x);

	m_enemy[10].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml3()->GetStagePos()[6].x + m_stage->GetStageNoraml3()->GetStageWh()[6].x / 2, m_stage->GetStageNoraml3()->GetStagePos()[6].y - 300.0f), true,
		m_stage->GetStageNoraml3()->GetStageWh()[6].x, m_stage->GetStageNoraml3()->GetStagePos()[6].x, m_stage->GetStageNoraml3()->GetStagePos()[6].x);
}

void ENEMYMANAGER::SetStage3NormalEnemyBird(void)
{
	m_enemybird[4].SetEnemy(D3DXVECTOR2(1700.0f, 400.0f), true, ENEMYBIRD_WINDATTACK);


	m_enemybird[6].SetEnemy(D3DXVECTOR2(4500.0f, 400.0f), true, ENEMYBIRD_WINDATTACK);

	m_enemybird[7].SetEnemy(D3DXVECTOR2(5300.0f, 800.0f), true, ENEMYBIRD_UP);

	m_enemybird[8].SetEnemy(D3DXVECTOR2(6300.0f, 400.0f), true, ENEMYBIRD_WINDATTACK);

	m_enemybird[9].SetEnemy(D3DXVECTOR2(7000.0f, 400.0f), true, ENEMYBIRD_THUNDERATTACK);
}

void ENEMYMANAGER::SetStage4NormalEnemy(void)
{
	m_enemy[11].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml4()->GetStagePos()[0].x + m_stage->GetStageNoraml4()->GetStageWh()[0].x / 2, m_stage->GetStageNoraml4()->GetStagePos()[0].y - 180.0f), true,
		m_stage->GetStageNoraml4()->GetStageWh()[0].x, m_stage->GetStageNoraml4()->GetStagePos()[0].x, m_stage->GetStageNoraml4()->GetStagePos()[0].x);

	m_enemy[12].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml4()->GetStagePos()[5].x + m_stage->GetStageNoraml4()->GetStageWh()[5].x / 2, m_stage->GetStageNoraml4()->GetStagePos()[5].y - 180.0f), true,
		m_stage->GetStageNoraml4()->GetStageWh()[5].x, m_stage->GetStageNoraml4()->GetStagePos()[5].x, m_stage->GetStageNoraml4()->GetStagePos()[5].x);

	m_enemy[13].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml4()->GetStagePos()[7].x + m_stage->GetStageNoraml4()->GetStageWh()[7].x / 2, m_stage->GetStageNoraml4()->GetStagePos()[7].y - 300.0f), true,
		m_stage->GetStageNoraml4()->GetStageWh()[7].x, m_stage->GetStageNoraml4()->GetStagePos()[7].x, m_stage->GetStageNoraml4()->GetStagePos()[7].x);
}

void ENEMYMANAGER::SetStage4NormalEnemyBird(void)
{
	m_enemybird[10].SetEnemy(D3DXVECTOR2(1000.0f, 400.0f), true, ENEMYBIRD_FIREATTACK);

	m_enemybird[11].SetEnemy(D3DXVECTOR2(1800.0f, 300.0f), true, ENEMYBIRD_THUNDERATTACK);

	m_enemybird[12].SetEnemy(D3DXVECTOR2(2800.0f, 400.0f), true, ENEMYBIRD_FIREATTACK);

	m_enemybird[13].SetEnemy(D3DXVECTOR2(5000.0f, 200.0f), true, ENEMYBIRD_THUNDERATTACK);

	m_enemybird[14].SetEnemy(D3DXVECTOR2(5500.0f, 400.0f), true, ENEMYBIRD_FIREATTACK);

	m_enemybird[15].SetEnemy(D3DXVECTOR2(6500.0f, 400.0f), true, ENEMYBIRD_FIREATTACK);

	m_enemybird[16].SetEnemy(D3DXVECTOR2(7300.0f, 200.0f), true, ENEMYBIRD_THUNDERATTACK);
}

void ENEMYMANAGER::SetStage5NormalEnemy(void)
{
	m_enemy[14].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml5()->GetStagePos()[0].x + m_stage->GetStageNoraml5()->GetStageWh()[0].x / 4, m_stage->GetStageNoraml5()->GetStagePos()[0].y - 180.0f), true,
		m_stage->GetStageNoraml5()->GetStageWh()[0].x, m_stage->GetStageNoraml5()->GetStagePos()[0].x, m_stage->GetStageNoraml5()->GetStagePos()[0].x);

	m_enemy[15].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml5()->GetStagePos()[0].x + m_stage->GetStageNoraml5()->GetStageWh()[0].x / 2, m_stage->GetStageNoraml5()->GetStagePos()[0].y - 180.0f), true,
		m_stage->GetStageNoraml5()->GetStageWh()[0].x, m_stage->GetStageNoraml5()->GetStagePos()[0].x, m_stage->GetStageNoraml5()->GetStagePos()[0].x);

	m_enemy[16].SetEnemy(D3DXVECTOR2(m_stage->GetStageNoraml5()->GetStagePos()[2].x + m_stage->GetStageNoraml5()->GetStageWh()[2].x / 2, m_stage->GetStageNoraml5()->GetStagePos()[2].y - 360.0f), true,
		m_stage->GetStageNoraml5()->GetStageWh()[2].x, m_stage->GetStageNoraml5()->GetStagePos()[2].x, m_stage->GetStageNoraml5()->GetStagePos()[2].x);
}

void ENEMYMANAGER::SetStage5NormalEnemyBird(void)
{
	m_enemybird[17].SetEnemy(D3DXVECTOR2(1200.0f, 200.0f), true, ENEMYBIRD_FIREATTACK);

	m_enemybird[18].SetEnemy(D3DXVECTOR2(2100.0f, 200.0f), true, ENEMYBIRD_WINDATTACK);

	m_enemybird[19].SetEnemy(D3DXVECTOR2(3000.0f, 200.0f), true, EMEMYBIRD_TURNING);

	m_enemybird[20].SetEnemy(D3DXVECTOR2(3700.0f, 200.0f), true, ENEMYBIRD_WINDATTACK);

	m_enemybird[21].SetEnemy(D3DXVECTOR2(6500.0f, 400.0f), true, ENEMYBIRD_FIREATTACK);

	m_enemybird[22].SetEnemy(D3DXVECTOR2(6800.0f, 400.0f), true, ENEMYBIRD_THUNDERATTACK);

	m_enemybird[23].SetEnemy(D3DXVECTOR2(7100.0f, 400.0f), true, ENEMYBIRD_WINDATTACK);

}