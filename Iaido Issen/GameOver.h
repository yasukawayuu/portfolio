/*****************************************************************************
*
*    GameOver.h
*    作成者　　五十嵐郁哉
******************************************************************************/
#pragma once

#include "main.h"
#include "stagemanager.h"

/*****************************************************************************
* マクロ定義
******************************************************************************/
enum SELECT
{
	SELECT_NONE,		// シーン設定なし
	SELECT_FOR_TITLE,	//　タイトル
	SELECT_FOR_RETRY,		// ゲーム本編

	SELECT_NUM,		// 終端コード
};



/*****************************************************************************
* プロトタイプ宣言
******************************************************************************/
class GAMEOVER
{
private:
	bool m_challenge;
public:
	void InitGameOver(void);
	void UninitGameOver(void);
	void UpdateGameOver(void);
	void DrawGameOver(void);

	bool*GetChallenge(void) { return &m_challenge; }
	bool GAMEOVERSoundFlag;
	bool GAMEOVERSoundFlag2;
};


