#pragma once

#include "main.h"
#include "player.h"
#include "stagemanager.h"
#include "enemymanager.h"
#include "slash.h"

#define HIT_VERTICAL (0x00000001)
#define HIT_BESIDE	(0x00000002)

#define HIT_UP (0x00000010)
#define HIT_DOWN (0x00000020)
#define HIT_LEFT (0x00000040)
#define HIT_RIGHT (0x00000080)

class COLLISION
{
private:
	STAGEMANAGER *m_stage;
	ENEMYMANAGER *m_enemy;
	PLAYER *m_player;
	SLASH *m_slash;

	float m_space;
public:
	COLLISION(){}

	COLLISION(STAGEMANAGER *stage,PLAYER *player,ENEMYMANAGER *enemy,SLASH *slash):m_stage(stage),m_player(player),m_enemy(enemy),m_slash(slash){}

	void UpdateCollsion();
	
	bool HitCheckBox(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);

	unsigned BoxHitDir(D3DXVECTOR2 base_pos, float base_wid, float base_hei, D3DXVECTOR2 hit_pos, float hit_wid, float hit_hei);

								//ブロックの数		//ブロックの場所	//ブロックの大きさ		//プレイヤーの位置
	void Collision_Stage_Player(int block_num, D3DXVECTOR2 stagepos[], D3DXVECTOR2 stagewh[], D3DXVECTOR2 playerpos);
	void Collision_Stage_Predict(int block_num, D3DXVECTOR2 stagepos[], D3DXVECTOR2 stagewh[]);
	void Collsion_Enemy_Predict(D3DXVECTOR2 enemypos);
	void Collision_Kyuubi_Slash(void);
	void Collision_Onibi_Player(void);
	void Collision_Kyuubi_Player(void);
	void Collision_Tail_Player(void);
	void Collision_Shake_Player(void);
	void Collision_Nagiharai_Player(void);
	void Collision_Enemy_Slash(int num_1, int num_2);
	void Collision_Enemy_Player(int num_1, int num_2);
	void Collision_EnemyBirdFire_Player(int num_1, int num_2);
	void Collision_EnemyBirdWind_Player(int num_1, int num_2);
	void Collision_EnemyBirdThunder_Player(int num_1, int num_2);
	void Collision_EnemyBird_Slash(int num_1, int num_2);
	void Collision_Tengu_Slash(void);
	void Collision_Thunder(void);
	void Collision_ThunderPre(void);
	void Collision_Fire_Slash(void);
	void Collision_FirePre_Slash(void);
	void Collision_Tengu_Player(void);
	void Collision_Fire_Player(void);
	void Collision_FirePre_Player(void);
	void Collision_Wind_Player(void);
	void Collision_WindPre_Player(void);
	void Collision_Thunder_Player(void);
	void Collision_ThunderPre_Player(void);
	void Collision_StageNoraml1(void);
	void Collision_StageNoraml2(void);
	void Collision_StageNoraml3(void);
	void Collision_StageNoraml4(void);
	void Collision_StageNoraml5(void);
	void Collision_StageBoss(void);
};