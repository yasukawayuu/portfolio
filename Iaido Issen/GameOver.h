/*****************************************************************************
*
*    GameOver.h
*    �쐬�ҁ@�@�܏\�����
******************************************************************************/
#pragma once

#include "main.h"
#include "stagemanager.h"

/*****************************************************************************
* �}�N����`
******************************************************************************/
enum SELECT
{
	SELECT_NONE,		// �V�[���ݒ�Ȃ�
	SELECT_FOR_TITLE,	//�@�^�C�g��
	SELECT_FOR_RETRY,		// �Q�[���{��

	SELECT_NUM,		// �I�[�R�[�h
};



/*****************************************************************************
* �v���g�^�C�v�錾
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


