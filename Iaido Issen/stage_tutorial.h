#pragma once
#pragma once
#include "main.h"

#define NUM_BLOCKTUTORIAL 8

#define STAGE2	(SCREEN_WIDTH)
#define STAGE3	(STAGE2 + SCREEN_WIDTH)
#define STAGE4	(STAGE3 + SCREEN_WIDTH)

class STAGE_TUTORIAL
{
private:
	int	m_Texture;
	int m_Texturebg;
	int m_Texturefooting;
	int m_Texturerock;


	D3DXVECTOR2 m_pos[NUM_BLOCKTUTORIAL];		    //ポジション
	D3DXVECTOR2 m_wh[NUM_BLOCKTUTORIAL];			//大きさ
	D3DXVECTOR2 m_block;		//ブロック数

	D3DXVECTOR2 m_posdata;        //ポジション
	bool        m_usedata;        //可視化フラグ

	int			m_blocktype;	//ステージの種類7

	D3DXVECTOR2 m_blockType[2] = {
	{0.0f, 0.0f},	//地面(0)
	{0.125f, 0.07f},//浮き地面(1)
	};

	D3DXVECTOR2 *m_base;							//カメラのベースをゲットした
	D3DXVECTOR2 *m_playerpos;

public:
	STAGE_TUTORIAL(D3DXVECTOR2* playerpos, D3DXVECTOR2 *base) :m_playerpos(playerpos), m_base(base) {}
	~STAGE_TUTORIAL() {}
	void Init(void);
	void Uninit(void);
	void Draw(void);

	D3DXVECTOR2* GetStagePos(void);
	D3DXVECTOR2* GetStageWh(void);
};