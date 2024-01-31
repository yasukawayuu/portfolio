#pragma once
#include "main.h"
#include "kyuubi.h"

#define NUM_BLOCKKYUUBI2 3

class STAGE_KYUUBI2
{
private:
	int	m_Texture;
	int m_Texturebg;
	int m_Texturebg2;
	int m_Textureroof;
	int m_Texturefooting;

	D3DXVECTOR2 m_pos[NUM_BLOCKKYUUBI2];		    //ポジション
	D3DXVECTOR2 m_wh[NUM_BLOCKKYUUBI2];			//大きさ
	D3DXVECTOR2 m_block;		//ブロック数

	D3DXVECTOR2 m_posdata;        //ポジション
	bool        m_usedata;        //可視化フラグ

	bool m_bguse;

	bool    m_KyuubiBGMSoundFlag2;

	int			m_blocktype;	//ステージの種類7

	D3DXVECTOR2 m_blockType[2] = {
	{0.0f, 0.0f},	//地面(0)
	{0.125f, 0.07f},//浮き地面(1)
	};

	D3DXVECTOR2 *m_base;							//カメラのベースをゲットした
	KYUUBI *m_kyuubi;
public:
	STAGE_KYUUBI2(KYUUBI *kyuubi, D3DXVECTOR2 *base) :m_kyuubi(kyuubi), m_base(base) {}
	~STAGE_KYUUBI2() {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateBG(void);
	void Draw(void);

	D3DXVECTOR2* GetStagePos(void);
	D3DXVECTOR2* GetStageWh(void);
};