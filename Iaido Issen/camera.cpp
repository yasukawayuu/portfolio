#include "camera.h"
#include "input.h"

void CAMERA::Init(void)
{
	m_camera = D3DXVECTOR2(0.0f, 0.0f);
	m_base = D3DXVECTOR2(0.0f, 0.0f);
}

void CAMERA::Uninit(void) 
{
}

void CAMERA::Update(void)
{


	if (m_playerpos->x > SCREEN_WIDTH * 4)
	{
		m_camera = D3DXVECTOR2(0.0f, 0.0f);
	}
	else if (m_playerpos->x > SCREEN_WIDTH * 3)
	{
		m_camera.x = SCREEN_WIDTH * 3;
	}
	else if (m_playerpos->x > SCREEN_WIDTH * 2)
	{
		m_camera.x = SCREEN_WIDTH * 2;
	}
	else if (m_playerpos->x > SCREEN_WIDTH)
	{
		m_camera.x = SCREEN_WIDTH;
	}

	if(m_playerpos->x < SCREEN_WIDTH)
		m_camera = D3DXVECTOR2(0.0f, 0.0f);

	
	



	//if(GetKeyboardTrigger(DIK_Q))
	//	m_camera.x -= SCREEN_WIDTH;

	//if (GetKeyboardTrigger(DIK_E))
	//	m_camera.x += SCREEN_WIDTH;

	if (m_camera.x < 0)
		m_camera.x = 0;
	/*if (m_camera.x > 960)
		m_camera.x = 960;
	if (m_camera.y < 0)
		m_camera.y = 0;
	if (m_camera.y > 480)
		m_camera.y = 480;*/
	//カメラの座標を反転したものがベース座標になる
	m_base = (m_camera * -1);
}

void CAMERA::Draw(void)
{
}

D3DXVECTOR2 * CAMERA::GetBase(void)
{
	return &m_base;
}
