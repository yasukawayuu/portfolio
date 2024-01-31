#pragma once

#include "main.h"
#include "stage_tutorial.h"
#include "stage_nomal1.h"
#include "stage_nomal2.h"
#include "stage_nomal3.h"
#include "stage_nomal4.h"
#include "stage_nomal5.h"
#include "stage_kyuubi_1.h"
#include "stage_kyuubi_2.h"
#include "stage_tengu.h"
#include "kyuubi.h"
#include "tengu.h"
#include "GameOver.h"

enum STAGE_NUM
{
	STAGETUTORIAL_1,
	STAGENORMAL_1,
	STAGENORMAL_2,
	STAGENORMAL_3,
	STAGENORMAL_4,
	STAGENORMAL_5,
	STAGETENGUU_1,
	STAGEKYUUBI_1,
	STAGEKYUUBI_2,
	STAGEKYUUBI_3,
};

class STAGEMANAGER
{
private:
	STAGE_TUTORIAL m_stagetutorial1;
	STAGE_NOMAL1 m_stagenormal1;
	STAGE_NOMAL2 m_stagenormal2;
	STAGE_NOMAL3 m_stagenormal3;
	STAGE_NOMAL4 m_stagenormal4;
	STAGE_NOMAL5 m_stagenormal5;
	STAGE_TENGU  m_stagetengu;
	STAGE_KYUUBI1 m_stagekyuubibi1;
	STAGE_KYUUBI2 m_stagekyuubibi2;
	STAGE_NUM m_stagenum;
	STAGE_NUM m_nowstage;

	D3DXVECTOR2 *m_playerpos;
	KYUUBI *m_kyuubi;
	TENGU  *m_tengu;
	
	int *m_playerhp;
	int *m_playerlive;
	bool *m_playerOnGround;
public:
	STAGEMANAGER(D3DXVECTOR2 *playerpos,D3DXVECTOR2 *base, KYUUBI *kyuubi,TENGU *tengu,int *playerhp,int *playerlive,bool *playerOnGround): m_playerpos(playerpos),
							m_stagetutorial1(playerpos,base),
							m_stagenormal1(playerpos,base),
							m_stagenormal2(playerpos,base),
							m_stagenormal3(playerpos,base),
							m_stagenormal4(playerpos,base),
							m_stagenormal5(playerpos,base),
							m_stagetengu(playerpos, base),
							m_stagekyuubibi1(playerpos,base),
							m_stagekyuubibi2(kyuubi,base),
							m_kyuubi(kyuubi),
							m_tengu(tengu),
							m_playerhp(playerhp),
							m_playerlive(playerlive),
							m_playerOnGround(playerOnGround){}
	~STAGEMANAGER(){}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	STAGE_TUTORIAL *GetStageTutorial(void) { return &m_stagetutorial1; }
	STAGE_NOMAL1 *GetStageNoraml1(void) { return &m_stagenormal1; }
	STAGE_NOMAL2 *GetStageNoraml2(void) { return &m_stagenormal2; }
	STAGE_NOMAL3 *GetStageNoraml3(void) { return &m_stagenormal3; }
	STAGE_NOMAL4 *GetStageNoraml4(void) { return &m_stagenormal4; }
	STAGE_NOMAL5 *GetStageNoraml5(void) { return &m_stagenormal5; }
	STAGE_TENGU  *GetStageTengu(void) { return &m_stagetengu; }
	STAGE_KYUUBI1 *GetStageKyuubi1(void) { return &m_stagekyuubibi1; }
	STAGE_KYUUBI2 *GetStageKyuubi2(void) { return &m_stagekyuubibi2; }
	STAGE_NUM GetStageNum(void) { return m_stagenum; }

	void SetStageNum(STAGE_NUM stagenum);
};