#pragma once
#include "main.h"

class OBSTACLE
{
private:
	int	m_texture = 0;

	D3DXVECTOR2 m_pos; //��Q���̈ʒu
	bool		m_collisionuse; //��Q���̃I���I�t
	float		m_size;//��Q���̑傫��

	int			m_animePtn;
	int			m_animeCounter;

	float m_animeTable[3] =			//�v���C���[��uv�l
	{
		0.0f,
		0.3333f,
		0.6666f,
	};

	D3DXVECTOR2 *m_base;							//�J�����̃x�[�X���Q�b�g����

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