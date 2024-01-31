#pragma once

#include "main.h"
#include "player.h"


class ENEMY
{
private:
	D3DXVECTOR2 m_pos;
	float m_left = 0;
	float m_right;
	float m_speed;
	int m_Texture = 0;

	int m_animeCount;
	int m_animePtn;
	int m_LR = 0;

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

	D3DXVECTOR2* m_base;
	bool m_use;
public:
	ENEMY(D3DXVECTOR2* base):m_base(base){}
	~ENEMY() {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetEnemy(D3DXVECTOR2 pos,bool use,float range, float left, float right);
	D3DXVECTOR2 *GetEnemyPos(void) { return &m_pos; }
	bool *GetEnemyUse(void) { return &m_use; }
};

