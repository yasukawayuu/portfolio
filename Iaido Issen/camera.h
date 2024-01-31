#pragma once

#include "main.h"
#include "stagemanager.h"

#define PLAYER_DISP_X (SCREEN_WIDTH/2)	//プレイヤーの表示座標X
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)	//プレイヤーの表示座標Y


class CAMERA
{
private:
	D3DXVECTOR2 m_camera;
	D3DXVECTOR2 m_base;

	D3DXVECTOR2 *m_playerpos;
	STAGEMANAGER *m_stage;

public:
	CAMERA(D3DXVECTOR2 *pos) :m_playerpos(pos){}
	~CAMERA(){}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 * GetBase(void);

};