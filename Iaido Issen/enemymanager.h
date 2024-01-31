#pragma once
#include "main.h"
#include "enemy.h"
#include "enemybird.h"
#include "kyuubi.h"
#include "tengu.h"
#include "stagemanager.h"

#define ENEMY_NUM 17
#define ENEMY_BIRD_NUM 24

class ENEMYMANAGER
{
private:
	ENEMY m_enemy[ENEMY_NUM];
	ENEMYBIRD m_enemybird[ENEMY_BIRD_NUM];
	KYUUBI m_kyuubi;
	TENGU m_tengu;
	STAGEMANAGER *m_stage;
	D3DXVECTOR2 *m_playerpos;
public:
	ENEMYMANAGER(STAGEMANAGER *stage,D3DXVECTOR2 *playerpos, D3DXVECTOR2* base,EFFECT *effect,int *playerhp,bool *playerunrivaled) :m_stage(stage),m_enemy{ENEMY(base),ENEMY(base),ENEMY(base),
																										ENEMY(base),ENEMY(base),ENEMY(base),
																										ENEMY(base),ENEMY(base),ENEMY(base),
																										ENEMY(base),ENEMY(base),ENEMY(base),
																										ENEMY(base),ENEMY(base),ENEMY(base),
																										ENEMY(base),ENEMY(base)},
	                                                                                            m_enemybird{ ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base),
	                                                                                            			 ENEMYBIRD(playerpos,base),ENEMYBIRD(playerpos,base) },
																								m_kyuubi(playerpos, base,effect,playerhp,playerunrivaled),
																								m_playerpos(playerpos),
																								m_tengu(playerpos,base){}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetStage1NormalEnemy(void);
	void SetStage2NormalEnemy(void);
	void SetStage2NormalEnemyBird(void);
	void SetStage3NormalEnemy(void);
	void SetStage3NormalEnemyBird(void);
	void SetStage4NormalEnemy(void);
	void SetStage4NormalEnemyBird(void);
	void SetStage5NormalEnemy(void);

	void SetStage5NormalEnemyBird(void);

	KYUUBI *GetKyuubi(void) { return &m_kyuubi; }
	ENEMY *GetEnemy(void) { return m_enemy; }
	ENEMYBIRD *GetEnemyBird(void) { return m_enemybird; }
	TENGU *GetTengu(void) { return &m_tengu; }
};