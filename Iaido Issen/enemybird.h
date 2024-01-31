#pragma once

#include"main.h"

#define PATTERN_ENEMY_WIDTH5 (1.0f / 5)         //ìGÇÃuÇÃâ°ïù
#define PATTERN_ENEMY_WIDTH4 (1.0f / 4)         //ìGÇÃuÇÃâ°ïù
#define PATTERN_ENEMY_WIDTH2 (1.0f / 2)         //ìGÇÃuÇÃâ°ïù

enum ENEMYBIRD_PATTERN
{
	ENEMYBIRD_UP,
	ENEMYBIRD_THUNDERATTACK,
	EMEMYBIRD_TURNING,
	ENEMYBIRD_FIREATTACK,
	ENEMYBIRD_WINDATTACK,

	ENEMYIRD_NUM
};

class ENEMYBIRD
{
private:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_originpos;
	D3DXVECTOR2 m_enoriginpos;
	int m_animeCount;
	int	m_animePtn;
	int m_LR;
	float m_frame;
	float m_speed;

	int m_elementanimeCount;
	int m_elementanimePtn;

	bool m_upflag;

	float m_u[4]
	{
		0.0f,
		0.3333f,
		0.6666f,
		0.3333f
	};

	float m_v[2]
	{
		0.0f,
		0.5f
	};

	struct ELEMENT
	{
		D3DXVECTOR2 m_pos;
		D3DXVECTOR2 m_oldplayerpos;
		bool		use;
		int			m_Texture;
	};


	ELEMENT m_fire;
	ELEMENT m_wind;
	ELEMENT m_thundercould;
	ELEMENT m_thunder;

	D3DXVECTOR2 *m_playerpos;
	int m_Texturered = 0;
	int m_Textureyellow = 0;
	int m_Texturepurple = 0;

	D3DXVECTOR2* m_base;
	bool m_use;
	float m_rotate;
	ENEMYBIRD_PATTERN m_pattern;
public:
	ENEMYBIRD(D3DXVECTOR2 *pos, D3DXVECTOR2* base) :m_playerpos(pos), m_base(base){}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BirdWait(void);
	void BirdUp(void);
	void BirdThunderAttack(void);
	void BirdTurning(void);
	void BirdFireAttack(void);
	void BirdWindAttack(void);
	void BirdMove(void);
	void SetEnemy(D3DXVECTOR2 pos, bool use,ENEMYBIRD_PATTERN pattern);


	D3DXVECTOR2 *GetEnemyBirdPos(void) { return &m_pos; }
	bool *GetEnemyBirdUse(void) { return &m_use; }
	D3DXVECTOR2 *GetFirePos(void) { return &m_fire.m_pos; }
	bool *GetFireUse(void) { return &m_fire.use; }
	D3DXVECTOR2 *GetWindPos(void) { return &m_wind.m_pos; }
	bool *GetWindUse(void) { return &m_wind.use; }
	D3DXVECTOR2 *GetThunderPos(void) { return &m_thunder.m_pos; }
	bool *GetThunderUse(void) { return &m_thunder.use; }
};