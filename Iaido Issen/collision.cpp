#include "collision.h"

void COLLISION::UpdateCollsion()
{
	switch (m_stage->GetStageNum())
	{
	case STAGETUTORIAL_1:
		Collision_Stage_Player(NUM_BLOCKTUTORIAL, m_stage->GetStageTutorial()->GetStagePos(), m_stage->GetStageTutorial()->GetStageWh(), *m_player->GetPlayerPos());

		break;
	case STAGENORMAL_1:
		Collision_Stage_Player(NUM_BLOCKNORMAL1,m_stage->GetStageNoraml1()->GetStagePos(), m_stage->GetStageNoraml1()->GetStageWh(), *m_player->GetPlayerPos());
		for (int i = 0; i < 6; i++)
		{
			if (*m_enemy->GetEnemy()[i].GetEnemyUse() == false)
				continue;

			Collsion_Enemy_Predict(*m_enemy->GetEnemy()[i].GetEnemyPos());
		}
		Collision_Stage_Predict(NUM_BLOCKNORMAL1, m_stage->GetStageNoraml1()->GetStagePos(), m_stage->GetStageNoraml1()->GetStageWh());

		Collision_Enemy_Slash(0, 6);
		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Enemy_Player(0, 6);
		}
		Collision_StageNoraml1();
		break;
	case STAGENORMAL_2:
		Collision_Stage_Player(NUM_BLOCKNORMAL2, m_stage->GetStageNoraml2()->GetStagePos(), m_stage->GetStageNoraml2()->GetStageWh(), *m_player->GetPlayerPos());
		Collision_Stage_Predict(NUM_BLOCKNORMAL2, m_stage->GetStageNoraml2()->GetStagePos(), m_stage->GetStageNoraml2()->GetStageWh());
		for (int i = 6; i < 8; i++)
		{
			if (*m_enemy->GetEnemy()[i].GetEnemyUse() == false)
				continue;

			Collsion_Enemy_Predict(*m_enemy->GetEnemy()[i].GetEnemyPos());
		}

		Collision_Enemy_Slash(6, 8);
		Collision_EnemyBird_Slash(0, 4);

		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Enemy_Player(6, 8);
			Collision_EnemyBirdFire_Player(0, 4);
			Collision_EnemyBirdWind_Player(0, 4);
			Collision_EnemyBirdThunder_Player(0, 4);
		}
		Collision_StageNoraml2();
		break;
	case STAGENORMAL_3:
		Collision_Stage_Player(NUM_BLOCKNORMAL3, m_stage->GetStageNoraml3()->GetStagePos(), m_stage->GetStageNoraml3()->GetStageWh(), *m_player->GetPlayerPos());
		for (int i = 8; i < 10; i++)
		{
			if (*m_enemy->GetEnemy()[i].GetEnemyUse() == false)
				continue;

			Collsion_Enemy_Predict(*m_enemy->GetEnemy()[i].GetEnemyPos());
		}
		Collision_Stage_Predict(NUM_BLOCKNORMAL3, m_stage->GetStageNoraml3()->GetStagePos(), m_stage->GetStageNoraml3()->GetStageWh());

		Collision_Enemy_Slash(8, 11);
		Collision_EnemyBird_Slash(4, 10);

		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Enemy_Player(8, 11);
			Collision_EnemyBirdFire_Player(4, 10);
			Collision_EnemyBirdWind_Player(4, 10);
			Collision_EnemyBirdThunder_Player(4, 10);
		}
		Collision_StageNoraml3();
		break;
	case STAGENORMAL_4:
		Collision_Stage_Player(NUM_BLOCKNORMAL4, m_stage->GetStageNoraml4()->GetStagePos(), m_stage->GetStageNoraml4()->GetStageWh(), *m_player->GetPlayerPos());
		for (int i = 10; i < 12; i++)
		{
			if (*m_enemy->GetEnemy()[i].GetEnemyUse() == false)
				continue;

			Collsion_Enemy_Predict(*m_enemy->GetEnemy()[i].GetEnemyPos());
		}
		Collision_Stage_Predict(NUM_BLOCKNORMAL4, m_stage->GetStageNoraml4()->GetStagePos(), m_stage->GetStageNoraml4()->GetStageWh());

		Collision_Enemy_Slash(11, 14);
		Collision_EnemyBird_Slash(10, 17);

		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Enemy_Player(11, 14);
			Collision_EnemyBirdFire_Player(10, 17);
			Collision_EnemyBirdWind_Player(10, 17);
			Collision_EnemyBirdThunder_Player(10, 17);
		}
		Collision_StageNoraml4();
		break;
	case STAGENORMAL_5:
		Collision_Stage_Player(NUM_BLOCKNORMAL5, m_stage->GetStageNoraml5()->GetStagePos(), m_stage->GetStageNoraml5()->GetStageWh(), *m_player->GetPlayerPos());
		for (int i = 12; i < 15; i++)
		{
			if (*m_enemy->GetEnemy()[i].GetEnemyUse() == false)
				continue;

			Collsion_Enemy_Predict(*m_enemy->GetEnemy()[i].GetEnemyPos());
		}
		Collision_Stage_Predict(NUM_BLOCKNORMAL5, m_stage->GetStageNoraml5()->GetStagePos(), m_stage->GetStageNoraml5()->GetStageWh());

		Collision_Enemy_Slash(14, 17);
		Collision_EnemyBird_Slash(17, 24);

		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Enemy_Player(14, 17);
			Collision_EnemyBirdFire_Player(17, 24);
			Collision_EnemyBirdWind_Player(17, 24);
			Collision_EnemyBirdThunder_Player(17, 24);
		}
		Collision_StageNoraml5();
		break;
	case STAGETENGUU_1:
		Collision_Stage_Player(NUM_BLOCKTENGU,m_stage->GetStageTengu()->GetStagePos(), m_stage->GetStageTengu()->GetStageWh(), *m_player->GetPlayerPos());
		Collision_Stage_Predict(NUM_BLOCKTENGU, m_stage->GetStageTengu()->GetStagePos(), m_stage->GetStageTengu()->GetStageWh());
		Collision_Thunder();
		Collision_ThunderPre();
		Collision_StageBoss();

		Collision_Tengu_Slash();
		Collision_Fire_Slash();
		Collision_FirePre_Slash();

		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Tengu_Player();
			Collision_Fire_Player();
			Collision_FirePre_Player();
			Collision_Wind_Player();
			Collision_WindPre_Player();
			Collision_Thunder_Player();
			Collision_ThunderPre_Player();
		}
		break;
	case STAGEKYUUBI_1:
		Collision_Stage_Player(NUM_BLOCKKYUUBI1, m_stage->GetStageKyuubi1()->GetStagePos(), m_stage->GetStageKyuubi1()->GetStageWh(), *m_player->GetOldPlayerPos());
		Collsion_Enemy_Predict(*m_enemy->GetKyuubi()->GetNineFoxPos());
		Collision_Stage_Predict(NUM_BLOCKKYUUBI1, m_stage->GetStageKyuubi1()->GetStagePos(), m_stage->GetStageKyuubi1()->GetStageWh());
		Collision_StageBoss();
		Collision_Kyuubi_Slash();
		if (*m_player->GetUnrivaled() == false)
		{	
			Collision_Kyuubi_Player();
			Collision_Tail_Player();
			Collision_Shake_Player();
		}
		break;
	case STAGEKYUUBI_2:
		Collision_Stage_Player(NUM_BLOCKKYUUBI2, m_stage->GetStageKyuubi2()->GetStagePos(), m_stage->GetStageKyuubi2()->GetStageWh(), *m_player->GetOldPlayerPos());
		Collsion_Enemy_Predict(*m_enemy->GetKyuubi()->GetNineFoxPos());
		Collision_Stage_Predict(NUM_BLOCKKYUUBI2, m_stage->GetStageKyuubi2()->GetStagePos(), m_stage->GetStageKyuubi2()->GetStageWh());
		Collision_StageBoss();
		Collision_Kyuubi_Slash();
		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Kyuubi_Player();
			Collision_Nagiharai_Player();
		}
		break;
	case STAGEKYUUBI_3:
		Collision_Stage_Player(NUM_BLOCKKYUUBI2, m_stage->GetStageKyuubi2()->GetStagePos(), m_stage->GetStageKyuubi2()->GetStageWh(), *m_player->GetOldPlayerPos());
		Collsion_Enemy_Predict(*m_enemy->GetKyuubi()->GetNineFoxPos());
		Collision_Stage_Predict(NUM_BLOCKKYUUBI2, m_stage->GetStageKyuubi2()->GetStagePos(), m_stage->GetStageKyuubi2()->GetStageWh());
		Collision_StageBoss();
		Collision_Kyuubi_Slash();
		if (*m_player->GetUnrivaled() == false)
		{
			Collision_Kyuubi_Player();
			Collision_Tail_Player();
			Collision_Shake_Player();
			Collision_Nagiharai_Player();
		}
		break;

	}
	
	

	if (m_space != 0.0f)
	{
		m_space--;
	}

}

bool COLLISION::HitCheckBox(D3DXVECTOR2 box1pos, float box1width, float box1height, D3DXVECTOR2 box2pos, float box2width, float box2height)
{
	float box1Xmin = box1pos.x - (box1width / 2);
	float box1Xmax = box1pos.x + (box1width / 2);
	float box1Ymin = box1pos.y - (box1height / 2);
	float box1Ymax = box1pos.y + (box1height / 2);

	float box2Xmin = box2pos.x - (box2width / 2);
	float box2Xmax = box2pos.x + (box2width / 2);
	float box2Ymin = box2pos.y - (box2height / 2);
	float box2Ymax = box2pos.y + (box2height / 2);

	if (box1Xmin < box2Xmax)
	{
		if (box1Xmax > box2Xmin)
		{
			if (box1Ymin < box2Ymax)
			{
				if (box1Ymax > box2Ymin)
				{
					return true;
				}
			}
		}
	}

	return false;
}


unsigned COLLISION::BoxHitDir(D3DXVECTOR2 base_pos, float base_wid, float base_hei, D3DXVECTOR2 hit_pos, float hit_wid, float hit_hei)
{
	unsigned result = 0;//結果(戻り値)
	//当たり判定
	D3DXVECTOR2 range((float)fabs(base_pos.x - hit_pos.x), (float)fabs(base_pos.y - hit_pos.y));
	if (range.x < (base_wid + hit_wid) / 2.0f) {
		if (range.y < (base_hei + hit_hei) / 2.0f) {

			//方向判定
			D3DXVECTOR2 v_corner(-base_wid / 2.0f, -base_hei / 2.0f);	//四角形の角のベクトル
			D3DXVec2Normalize(&v_corner, &v_corner);					//ノーマライズ
			D3DXVECTOR2 v_base_vertical(0.0f, -1.0f);					//上向きのベクトル
			float dot_corner = D3DXVec2Dot(&v_base_vertical, &v_corner);//角と上向きのベクトルの内積を取得
			D3DXVECTOR2 v_box(hit_pos - base_pos);						//四角同士のベクトルを取得
			D3DXVec2Normalize(&v_box, &v_box);							//ノーマライズ
			float dot_box = (float)fabs(D3DXVec2Dot(&v_base_vertical, &v_box));//上向きのベクトルと四角同士のベクトルの内積を取得

			if (dot_box > dot_corner) {//trueなら縦
				result |= HIT_VERTICAL;//縦
				if (D3DXVec2Dot(&v_base_vertical, &v_box) > 0) {
					result |= HIT_UP;//上
				}
				else {
					result |= HIT_DOWN;//下
				}
			}
			else if (dot_box < dot_corner) {//横
				result |= HIT_BESIDE;//横
				D3DXVECTOR2 v_base_beside(1.0f, 0.0f);//横向きのベクトルを取得
				if (D3DXVec2Dot(&v_base_beside, &v_box) > 0) {//trueなら右
					result |= HIT_RIGHT;//右
				}
				else {
					result |= HIT_LEFT;//左
				}
			}



		}
	}
	return result;
}

void COLLISION::Collision_Stage_Player(int block_num,D3DXVECTOR2 stagepos[],D3DXVECTOR2 stagewh[],D3DXVECTOR2 playerpos)
{
	for (int i = 0; i < block_num; i++)
	{
		if (BoxHitDir(stagepos[i], stagewh[i].x, stagewh[i].y, playerpos, 98.0f, 256.0f) & HIT_UP)
		{
			*m_player->GetOnGround() = true;
		}
		else
		{
			*m_player->GetOnGround() = false;
		}

		if (*m_player->GetOnGround() == true)
		{
			break;
		}

	}

	for (int i = 0; i < block_num; i++)
	{
		if (BoxHitDir(stagepos[i], stagewh[i].x, stagewh[i].y, playerpos, 98.0f, 256.0f) & HIT_LEFT)
		{
			*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
		}

		if (BoxHitDir(stagepos[i], stagewh[i].x, stagewh[i].y, playerpos, 98.0f, 256.0f) & HIT_RIGHT)
		{
			*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
		}
		
	}
}



void COLLISION::Collision_Stage_Predict(int block_num, D3DXVECTOR2 stagepos[], D3DXVECTOR2 stagewh[])
{
	for (int i = 0; i < block_num; i++)
	{
		if (HitCheckBox(stagepos[i], stagewh[i].x, stagewh[i].y,
			*m_player->GetPlayerPos() + *m_player->GetPredictPos(), 98.0f, 230.0f))
		{
			*m_player->GetGoPredictPos() = false;
		}
		else
		{
			*m_player->GetGoPredictPos() = true;
		}

		if (*m_player->GetGoPredictPos() == false)
		{
			break;
		}
	}

}

void COLLISION::Collsion_Enemy_Predict(D3DXVECTOR2 enemypos)
{
	if (HitCheckBox(enemypos,98.0f,224.0f, *m_player->GetPlayerPos() + *m_player->GetPredictPos(),98.0f,224.0f))
	{
		*m_player->GetGoPredictPos() = false;
	}
	else
	{
		*m_player->GetGoPredictPos() = true;
	}
}

void COLLISION::Collision_Kyuubi_Slash(void)
{
	if (m_space == 0.0f)
	{
		if (HitCheckBox(*m_enemy->GetKyuubi()->GetNineFoxPos(), 224.0f, 224.0f, *m_slash->GetSlashPos(), 256.0f, 256.0f) && 
			*m_slash->GetSlashUse() == true && *m_enemy->GetKyuubi()->GetNineFoxOnibiUse() == false && *m_enemy->GetKyuubi()->GetNineFoxReturnUse() == false)
		{
			*m_enemy->GetKyuubi()->GetNineFoxHitUse() = true;
			m_space = 60.0f;
		}
	}
	else
	{
		m_space--;
	}
}


void COLLISION::Collision_Kyuubi_Player(void)
{
	if (HitCheckBox(*m_enemy->GetKyuubi()->GetNineFoxPos(), 96.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f) && m_enemy->GetKyuubi()->GetNineFoxOnibiUse() == false)
	{
		*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
	}
}

void COLLISION::Collision_Onibi_Player(void)
{
	if (m_space == 0.0f)
	{
		for (int i = 0; i < 5; i++)
		{
			if (HitCheckBox(m_enemy->GetKyuubi()->GetOnibiPos()[i], 64.0f, 64.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
			{
				*m_player->GetPlayerHp() -= 1;
				m_space = 60.0f;
			}
		}
		
	}
}


void COLLISION::Collision_Tail_Player(void)
{
	if (m_space == 0.0f && *m_enemy->GetKyuubi()->GetNineFoxTailUse() == true)
	{
		if (HitCheckBox(*m_enemy->GetKyuubi()->GetNineFoxTail(), 96.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
		{
			*m_player->GetPlayerHp() -= 1;
			m_space = 120.0f;
			*m_player->GetUnrivaled() = true;
		}
	}
}

void COLLISION::Collision_Shake_Player(void)
{
	if (m_space == 0.0f)
	{
		if (*m_enemy->GetKyuubi()->GetNineFoxSkakePtn() == 2)
		{
			if (HitCheckBox(D3DXVECTOR2(m_enemy->GetKyuubi()->GetNineFoxPos()->x - 50.0f, m_enemy->GetKyuubi()->GetNineFoxPos()->y), 98.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
			{
				*m_player->GetPlayerHp() -= 1;
				m_space = 60.0f;
				*m_player->GetUnrivaled() = true;
			}
		}
	}
}

void COLLISION::Collision_Nagiharai_Player(void)
{
	if (m_space == 0.0f)
	{
		if (*m_enemy->GetKyuubi()->GetNineFoxNagiharaiPtn() == 2)
		{
			if (HitCheckBox(D3DXVECTOR2(m_enemy->GetKyuubi()->GetNineFoxPos()->x - 50.0f, m_enemy->GetKyuubi()->GetNineFoxPos()->y), 98.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
			{
				*m_player->GetPlayerHp() -= 1;
				m_space = 60.0f;
				*m_player->GetUnrivaled() = true;
			}
		}
	}
}


void COLLISION::Collision_Enemy_Slash(int num_1,int num_2)
{
	for (int i = num_1; i < num_2; i++)
	{
		if (*m_enemy->GetEnemy()[i].GetEnemyUse() == false)
			continue;

		if (HitCheckBox(*m_enemy->GetEnemy()[i].GetEnemyPos(), 192.0f, 256.0f, *m_slash->GetSlashPos(), 128.0f, 256.0f) && *m_slash->GetSlashUse() == true)
		{
			*m_enemy->GetEnemy()[i].GetEnemyUse() = false;
		}
	}
	
}

void COLLISION::Collision_Enemy_Player(int num_1, int num_2)
{
	if (m_space == 0.0f)
	{
		for (int i = num_1; i < num_2; i++)
		{
			if (*m_enemy->GetEnemy()[i].GetEnemyUse() == false)
				continue;

			if (HitCheckBox(*m_enemy->GetEnemy()[i].GetEnemyPos(), 96.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
				*m_player->GetPlayerHp() -= 1;
				m_space = 60.0f;
				*m_player->GetUnrivaled() = true;
			}
		}
	}
	
}

void COLLISION::Collision_EnemyBirdFire_Player(int num_1, int num_2)
{
	if (m_space == 0.0f)
	{
		for (int i = num_1; i < num_2; i++)
		{
			if (*m_enemy->GetEnemyBird()[i].GetEnemyBirdUse() == false)
				continue;

			if (HitCheckBox(*m_enemy->GetEnemyBird()[i].GetFirePos(), 128.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
				*m_player->GetPlayerHp() -= 1;
				m_space = 60.0f;
				*m_player->GetUnrivaled() = true;
			}
		}
	}
}

void COLLISION::Collision_EnemyBirdWind_Player(int num_1, int num_2)
{
	if (m_space == 0.0f)
	{
		for (int i = num_1; i < num_2; i++)
		{
			if (*m_enemy->GetEnemyBird()[i].GetEnemyBirdUse()== false)
				continue;

			if (HitCheckBox(*m_enemy->GetEnemyBird()[i].GetWindPos(), 128.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
				*m_player->GetPlayerHp() -= 1;
				m_space = 60.0f;
				*m_player->GetUnrivaled() = true;
			}
		}
	}
}

void COLLISION::Collision_EnemyBirdThunder_Player(int num_1, int num_2)
{
	if (m_space == 0.0f)
	{
		for (int i = num_1; i < num_2; i++)
		{
			if (*m_enemy->GetEnemyBird()[i].GetEnemyBirdUse() == false)
				continue;

			if (HitCheckBox(*m_enemy->GetEnemyBird()[i].GetThunderPos(), 98.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
				*m_player->GetPlayerHp() -= 1;
				m_space = 60.0f;
				*m_player->GetUnrivaled() = true;
			}
		}
	}
}



void COLLISION::Collision_EnemyBird_Slash(int num_1, int num_2)
{
	for (int i = num_1; i < num_2; i++)
	{
		if (*m_enemy->GetEnemyBird()[i].GetEnemyBirdUse() == false)
			continue;

		if (HitCheckBox(*m_enemy->GetEnemyBird()[i].GetEnemyBirdPos(), 192.0f, 256.0f, *m_slash->GetSlashPos(), 192.0f, 256.0f) && *m_slash->GetSlashUse() == true)
		{
			*m_enemy->GetEnemyBird()[i].GetEnemyBirdUse() = false;
		}
	}

}

void COLLISION::Collision_Tengu_Slash(void)
{
	if (m_enemy->GetTengu()->GetTengu()->downFlag == true)
	{
		if (HitCheckBox(m_enemy->GetTengu()->GetTengu()->pos, 192.0f, 256.0f, *m_slash->GetSlashPos(), 128.0f, 256.0f) && *m_slash->GetSlashUse() == true)
		{

			m_enemy->GetTengu()->GetTengu()->hp -= 1;
			m_enemy->GetTengu()->GetTengu()->hitFlag = true;
			m_enemy->GetTengu()->GetTengu()->downFlag = false;

		}
	}
}

void COLLISION::Collision_Thunder(void)
{
	if (m_enemy->GetTengu()->GetTenguThunder()->use == true)
	{
		if ((((m_enemy->GetTengu()->GetTenguCloud()->pos.x - m_enemy->GetTengu()->GetTengu()->pos.x) <= THUNDER_HIT_SIZE) &&
			(m_enemy->GetTengu()->GetTenguCloud()->pos.x - m_enemy->GetTengu()->GetTengu()->pos.x) >= -THUNDER_HIT_SIZE))
		{
			if (m_enemy->GetTengu()->GetTengu()->move == true)
			{
				m_enemy->GetTengu()->GetTenguThunder()->frame = 0.0f;
				m_enemy->GetTengu()->GetTenguCloud()->use = false;
				m_enemy->GetTengu()->GetTenguCloud()->frame = 0;

				m_enemy->GetTengu()->GetTenguThunder()->pos = D3DXVECTOR2(-100.0f, -100.0f);
				m_enemy->GetTengu()->GetTengu()->stateteng = TENGU_STATE_STAY;
				m_enemy->GetTengu()->TextureFlagManager(&m_enemy->GetTengu()->GetTengu()->thunderHitFlag);


				m_enemy->GetTengu()->GetTenguFire()->speed = 3.0f;
				m_enemy->GetTengu()->GetTenguFire()->onGround = false;
				m_enemy->GetTengu()->GetTenguFire()->use = false;

				m_enemy->GetTengu()->GetTenguWind()->use = false;
				m_enemy->GetTengu()->GetTenguWind()->speed.x = frand() * 10.0 - 5.0f;
				m_enemy->GetTengu()->GetTenguWind()->speed.y = -1.0f;

				m_enemy->GetTengu()->GetTenguThunder()->use = false;
				m_enemy->GetTengu()->GetTengu()->move = false;
			}
		}

		if ((((m_enemy->GetTengu()->GetTenguCloud()->pos.x - m_enemy->GetTengu()->GetTenguPre()->pos.x) <= THUNDER_HIT_SIZE) &&
			(m_enemy->GetTengu()->GetTenguCloud()->pos.x - m_enemy->GetTengu()->GetTenguPre()->pos.x) >= -THUNDER_HIT_SIZE))
		{
			m_enemy->GetTengu()->GetTenguThunder()->use = false;
			m_enemy->GetTengu()->GetTenguThunder()->pos = D3DXVECTOR2(-100.0f, -100.0f);
			m_enemy->GetTengu()->GetTenguThunder()->frame = 0.0f;
			m_enemy->GetTengu()->GetTenguCloud()->use = false;
			m_enemy->GetTengu()->GetTenguCloud()->frame = 0;
			m_enemy->GetTengu()->GetTengu()->stateteng = TENGU_STATE_STAY;
			m_enemy->GetTengu()->GetTenguPre()->stateteng = TENGU_STATE_STAY;
			m_enemy->GetTengu()->TextureFlagManagerPre(&m_enemy->GetTengu()->GetTenguPre()->thunderHitFlag);
			m_enemy->GetTengu()->GetTenguPre()->move = false;

		}
	}
}

void COLLISION::Collision_ThunderPre(void)
{
	if (m_enemy->GetTengu()->GetTenguThunderPre()->use == true)
	{
		if ((((m_enemy->GetTengu()->GetTenguCloudPre()->pos.x - m_enemy->GetTengu()->GetTengu()->pos.x) <= THUNDER_HIT_SIZE) &&
			(m_enemy->GetTengu()->GetTenguCloudPre()->pos.x - m_enemy->GetTengu()->GetTengu()->pos.x) >= -THUNDER_HIT_SIZE))
		{
			if (m_enemy->GetTengu()->GetTengu()->move == true)
			{


				m_enemy->GetTengu()->GetTenguThunderPre()->use = false;
				m_enemy->GetTengu()->GetTenguThunderPre()->pos = D3DXVECTOR2(-100.0f, -100.0f);
				m_enemy->GetTengu()->GetTenguThunderPre()->frame = 0.0f;
				m_enemy->GetTengu()->GetTenguCloudPre()->use = false;
				m_enemy->GetTengu()->GetTenguCloudPre()->frame = 0;
				m_enemy->GetTengu()->GetTenguPre()->stateteng = TENGU_STATE_STAY;
				m_enemy->GetTengu()->GetTengu()->stateteng = TENGU_STATE_STAY;
				m_enemy->GetTengu()->TextureFlagManager(&m_enemy->GetTengu()->GetTengu()->thunderHitFlag);


				m_enemy->GetTengu()->GetTenguFire()->speed = 3.0f;
				m_enemy->GetTengu()->GetTenguFire()->onGround = false;
				m_enemy->GetTengu()->GetTenguFire()->use = false;

				m_enemy->GetTengu()->GetTenguWind()->use = false;
				m_enemy->GetTengu()->GetTenguWind()->speed.x = frand() * 10.0 - 5.0f;
				m_enemy->GetTengu()->GetTenguWind()->speed.y = -1.0f;

				m_enemy->GetTengu()->GetTengu()->move = false;
			}
		}

		if ((((m_enemy->GetTengu()->GetTenguCloudPre()->pos.x - m_enemy->GetTengu()->GetTenguPre()->pos.x) <= THUNDER_HIT_SIZE) &&
			(m_enemy->GetTengu()->GetTenguCloudPre()->pos.x - m_enemy->GetTengu()->GetTenguPre()->pos.x) >= -THUNDER_HIT_SIZE))
		{
			m_enemy->GetTengu()->GetTenguThunderPre()->frame = 0.0f;
			m_enemy->GetTengu()->GetTenguCloudPre()->use = false;
			m_enemy->GetTengu()->GetTenguCloudPre()->frame = 0;
			m_enemy->GetTengu()->GetTenguThunderPre()->use = false;
			m_enemy->GetTengu()->GetTenguThunderPre()->pos = D3DXVECTOR2(-100.0f, -100.0f);
			m_enemy->GetTengu()->GetTenguPre()->stateteng = TENGU_STATE_STAY;
			m_enemy->GetTengu()->TextureFlagManagerPre(&m_enemy->GetTengu()->GetTenguPre()->thunderHitFlag);
			m_enemy->GetTengu()->GetTenguPre()->move = false;

		}
	}
}

void COLLISION::Collision_Fire_Slash(void)
{
	if (HitCheckBox(*m_slash->GetSlashPos(), 128.0f, 256.0f, m_enemy->GetTengu()->GetTenguFire()->pos, 180.0f, 280.0f))
	{
		m_enemy->GetTengu()->GetTenguFire()->onGround = false;
		m_enemy->GetTengu()->GetTenguFire()->use = false;
	}
}

void COLLISION::Collision_FirePre_Slash(void)
{
	if (HitCheckBox(*m_slash->GetSlashPos(), 128.0f, 256.0f, m_enemy->GetTengu()->GetTenguFirePre()->pos, 180.0f, 280.0f))
	{
		m_enemy->GetTengu()->GetTenguFirePre()->onGround = false;
		m_enemy->GetTengu()->GetTenguFirePre()->use = false;
	}
}

void COLLISION::Collision_Tengu_Player(void)
{

	if (HitCheckBox(m_enemy->GetTengu()->GetTengu()->pos, 96.0f, 256.0f, *m_player->GetPlayerPos(), 98.0f, 256.0f))
	{
		*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
		*m_player->GetUnrivaled() = true;
	}
}

void COLLISION::Collision_Fire_Player(void)
{
	if (m_enemy->GetTengu()->GetTenguFire()->use == true)
	{
		if (HitCheckBox(m_enemy->GetTengu()->GetTenguFire()->pos, 150.0f, 280.0f, *m_player->GetPlayerPos(), 128.0f, 256.0f))
		{
			*m_player->GetPlayerHp() -= 1;
			m_enemy->GetTengu()->GetTenguFire()->onGround = false;
			m_enemy->GetTengu()->GetTenguFire()->use = false;
			*m_player->GetUnrivaled() = true;
		}
	}
}
void COLLISION::Collision_FirePre_Player(void)
{
	if (m_enemy->GetTengu()->GetTenguFirePre()->use == true)
	{
		if (HitCheckBox(m_enemy->GetTengu()->GetTenguFirePre()->pos, 150.0f, 280.0f, *m_player->GetPlayerPos(), 128.0f, 256.0f))
		{
			*m_player->GetPlayerHp() -= 1;
			m_enemy->GetTengu()->GetTenguFirePre()->onGround = false;
			m_enemy->GetTengu()->GetTenguFirePre()->use = false;
			*m_player->GetUnrivaled() = true;
		}
	}
}

void COLLISION::Collision_Wind_Player(void)
{
	if (m_enemy->GetTengu()->GetTenguWind()->use == true)
	{
		if (HitCheckBox(m_enemy->GetTengu()->GetTenguWind()->pos, 200.0f, 310.0f, *m_player->GetPlayerPos(), 128.0f, 256.0f))
		{
			*m_player->GetPlayerHp() -= 1;
			*m_player->GetUnrivaled() = true;
			//m_enemy->GetTengu()->GetTenguWind()->use = false;
		}
	}
}

void COLLISION::Collision_WindPre_Player(void)
{
	if (m_enemy->GetTengu()->GetTenguWindPre()->use == true)
	{
		if (HitCheckBox(m_enemy->GetTengu()->GetTenguWindPre()->pos, 200.0f, 310.0f, *m_player->GetPlayerPos(), 128.0f, 256.0f))
		{
			*m_player->GetPlayerHp() -= 1;
			*m_player->GetUnrivaled() = true;
			//m_enemy->GetTengu()->GetTenguWindPre()->use = false;
		}
	}
}

void COLLISION::Collision_Thunder_Player(void)
{
	if (m_enemy->GetTengu()->GetTenguThunder()->use == true)
	{
		if (HitCheckBox(m_enemy->GetTengu()->GetTenguThunder()->pos, 80.0f, SCREEN_HEIGHT * 2, *m_player->GetPlayerPos(), 128.0f, 256.0f))
		{
			*m_player->GetPlayerHp() -= 1;
			*m_player->GetUnrivaled() = true;
			//m_enemy->GetTengu()->GetTenguWind()->use = false;
		}
	}
}
void COLLISION::Collision_ThunderPre_Player(void)
{
	if (m_enemy->GetTengu()->GetTenguThunderPre()->use == true)
	{
		if (HitCheckBox(m_enemy->GetTengu()->GetTenguThunderPre()->pos, 80.0f, SCREEN_HEIGHT * 2, *m_player->GetPlayerPos(), 128.0f, 256.0f))
		{
			*m_player->GetPlayerHp() -= 1;
			*m_player->GetUnrivaled() = true;
			//m_enemy->GetTengu()->GetTenguWind()->use = false;
		}
	}
}

void COLLISION::Collision_StageNoraml1(void)
{
	if (m_player->GetPlayerPos()->x > 0 && m_player->GetPlayerPos()->x < SCREEN_WIDTH)
	{
		if (*m_enemy->GetEnemy()[0].GetEnemyUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 2)
	{
		if (*m_enemy->GetEnemy()[1].GetEnemyUse() == true || *m_enemy->GetEnemy()[2].GetEnemyUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();

			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}

	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 3)
	{
		if (*m_enemy->GetEnemy()[3].GetEnemyUse() == true || *m_enemy->GetEnemy()[4].GetEnemyUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 4)
	{
		if (*m_enemy->GetEnemy()[5].GetEnemyUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}
}

void COLLISION::Collision_StageNoraml2(void)
{
	if (m_player->GetPlayerPos()->x > 0 && m_player->GetPlayerPos()->x < SCREEN_WIDTH)
	{
		if (*m_enemy->GetEnemyBird()[0].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 2)
	{
		if (*m_enemy->GetEnemy()[6].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[1].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();

			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 3)
	{
		if (*m_enemy->GetEnemyBird()[2].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 4)
	{
		if (*m_enemy->GetEnemy()[7].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[3].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}
}

void COLLISION::Collision_StageNoraml3(void)
{
	if (m_player->GetPlayerPos()->x > 0 && m_player->GetPlayerPos()->x < SCREEN_WIDTH)
	{
		if (*m_enemy->GetEnemy()[8].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[4].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 2)
	{
		if (*m_enemy->GetEnemy()[9].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[5].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();

			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 3)
	{
		if (*m_enemy->GetEnemyBird()[6].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[7].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 4)
	{
		if (*m_enemy->GetEnemy()[10].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[8].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[9].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}
}

void COLLISION::Collision_StageNoraml4(void)
{
	if (m_player->GetPlayerPos()->x > 0 && m_player->GetPlayerPos()->x < SCREEN_WIDTH)
	{
		if (*m_enemy->GetEnemy()[11].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[10].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[11].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 2)
	{
		if (*m_enemy->GetEnemyBird()[12].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();

			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 3)
	{
		if (*m_enemy->GetEnemy()[12].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[13].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[14].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 3 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 4)
	{
		if (*m_enemy->GetEnemy()[13].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[15].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[16].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH  * 4 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}
}

void COLLISION::Collision_StageNoraml5(void)
{
	if (m_player->GetPlayerPos()->x > 0 && m_player->GetPlayerPos()->x < SCREEN_WIDTH)
	{
		if (*m_enemy->GetEnemy()[14].GetEnemyUse() == true || *m_enemy->GetEnemy()[15].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[17].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}

	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 2)
	{
		if (*m_enemy->GetEnemy()[16].GetEnemyUse() == true || *m_enemy->GetEnemyBird()[18].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[19].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[20].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();

			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 2 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}


	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 3 && m_player->GetPlayerPos()->x < SCREEN_WIDTH * 4)
	{
		if (*m_enemy->GetEnemyBird()[21].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[22].GetEnemyBirdUse() == true || *m_enemy->GetEnemyBird()[23].GetEnemyBirdUse() == true)
		{
			if (m_player->GetPlayerPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
			}

			if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH * 4 - 48.0f)
			{
				*m_player->GetGoPredictPos() = false;
			}
		}
	}
}

void COLLISION::Collision_StageBoss(void)
{
	if (m_player->GetPlayerPos()->x > SCREEN_WIDTH - 48.0f)
	{
		*m_player->GetPlayerPos() = *m_player->GetOldPlayerPos();
	}

	if (m_player->GetPlayerPos()->x + m_player->GetPredictPos()->x > SCREEN_WIDTH - 48.0f)
	{
		*m_player->GetGoPredictPos() = false;
	}
}