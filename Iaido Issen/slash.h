#pragma once

#include "main.h"
#include"effect.h"

class SLASH
{
private:
	int m_TextureSHLeft = 0;//スラッシュ用テクスチャの識別子
	int m_TextureSHRight = 0;//スラッシュ用テクスチャの識別子

	D3DXVECTOR2 m_pos; //スラッシュの位置
	bool m_use;		   //スラッシュの表示
	float m_time;	   //スラッシュの表示時間
	int m_muki;		   //スラッシュの向き

	float m_mukiTalbel[4] =
	{
		-80.0f,
		105.0f,
		-80.0f,
		105.0f,
	};

	D3DXVECTOR2 *m_base;							//カメラのベースをゲットした
	EFFECT* m_Effect;

public:
	SLASH(){}
	SLASH(D3DXVECTOR2 *base, EFFECT* Effect) : m_base(base),m_Effect(Effect){}
	~SLASH(){}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetSlash(D3DXVECTOR2 pos, int muki);
	D3DXVECTOR2* GetSlashPos(void);
	bool* GetSlashUse(void);
};