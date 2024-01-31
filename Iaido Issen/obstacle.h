#pragma once
#include "main.h"

class OBSTACLE
{
private:
	int	m_texture = 0;

	D3DXVECTOR2 m_pos; //障害物の位置
	bool		m_collisionuse; //障害物のオンオフ
	float		m_size;//障害物の大きさ

	int			m_animePtn;
	int			m_animeCounter;

	float m_animeTable[3] =			//プレイヤーのuv値
	{
		0.0f,
		0.3333f,
		0.6666f,
	};

	D3DXVECTOR2 *m_base;							//カメラのベースをゲットした

public:
	OBSTACLE(D3DXVECTOR2 *base):m_base(base){}
	~OBSTACLE(){}

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	D3DXVECTOR2* GetObstaclePos(void);
	bool* GetCollisionPos(void);
	float* GetObstacleSize(void);
};