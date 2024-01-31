#pragma once
#include "main.h"

#define NUM_BLOCKKYUUBI1 1

class STAGE_KYUUBI1
{
private:
	int	m_Texture;
	int m_Texturefooting;
	int m_Texturebg;
	int m_Texturehusuma;

	D3DXVECTOR2 m_pos;		    //ポジション
	D3DXVECTOR2 m_wh;			//大きさ
	D3DXVECTOR2 m_block;		//ブロック数

	D3DXVECTOR2 m_posdata;        //ポジション
	bool        m_usedata;        //可視化フラグ

	bool    m_KyuubiBGMSoundFlag;



	int			m_blocktype;	//ステージの種類7

	D3DXVECTOR2 m_blockType[2] = {
	{0.0f, 0.0f},	//地面(0)
	{0.125f, 0.07f},//浮き地面(1)
	};

	D3DXVECTOR2 *m_base;							//カメラのベースをゲットした
	D3DXVECTOR2 *m_playerpos;

public:
	STAGE_KYUUBI1(D3DXVECTOR2* playerpos, D3DXVECTOR2 *base) :m_playerpos(playerpos), m_base(base) {}
	~STAGE_KYUUBI1() {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR2* GetStagePos(void);
	D3DXVECTOR2* GetStageWh(void);
};