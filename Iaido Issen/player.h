#pragma once

#include "main.h"
#include "slash.h"
#include "effect.h"


#define PLAYER_DISP_X (SCREEN_WIDTH/2)			//�v���C���[�̕\�����WX
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)			//�v���C���[�̕\�����WY

//*****************************************************************************
// �}�N����`
//*****************************************************************************


class PLAYER
{
private:
	D3DXVECTOR2 m_pos;							//�v���C���[�̈ʒu
	D3DXVECTOR2	m_vel;							//���x�x�N�g��
	D3DXVECTOR2 m_oldpos;

	float		m_height = 0.0f;						//�v���C���[�̍���
	float		m_size = 0.0f;							//�v���C���[�̃T�C�Y
	float       m_gravity = 0.0f;						//�v���C���[�̏d��
	float		m_crouchingtime = 0.0f;				//���Ⴊ�ݎ���
	bool		m_crouching = false;					//���Ⴊ��ł邩�ǂ���
	bool        m_onGround = false;						//�n�ʂɂ��邩
	bool		m_skychage = false;

	float		m_overheatframe = 0.0f;
	float		m_penaltyframe = 0.0f;
	bool		m_overheatflag = false;

	float		m_movetime = 0.0f; 						//������܂ł̎���
	int			m_muki = 0;							//�v���C���[�̌���
	int			m_mukiOld = 0;						//�O�t���[���Ńv���C���[�������Ă�������
	int			m_animePtn = 0;						//�v���C���[�̓����̐؂�ւ�
	int			m_animeReservoirPtn = 0;			//�\������Ƃ��̃A�j���[�V����
	int			m_animeCounter = 0;					//�v���C���[�̓����̑���

	int         m_slashFlag = false;

	int			m_continuity = 0;					//�A��
	float		m_nextcontinuitytime = 0.0f;			//���̓�A���łĂ鎞��
	float		m_continuitytime = 0.0f;				//��A�������ԂȂ����ǂ���
	bool        m_diagonalSlash = false;				//�΂߂ɐ؂�����
	bool		m_predict = false;						//�\���e
	bool		m_gopredictpos = false;					//�\����ɍs���邩�ǂ���
	float		m_shadowspeedY = 0.0f;					//�e��Y�����ړ�����X�s�[�h
	float		m_playerY = 0.0f;						// �e�������\��̏ꏊ

	bool		m_unrivaled;
	int			m_unrivaledtime;

	D3DXVECTOR2	m_predictpos;					//�\���ꏊ
	int			m_hp = 0;							//�v���C���[�̗̑�
	int			m_live = 0;
	float		m_a = 0.0f;							//�����x
	

	bool		m_use;							//�v���C���[�̕\��

	int			m_Textureplayer = 0;					//�v���C���[�̃e�N�X�`���̎��ʎq
	int			m_Texturereservoir = 0;				//�v���C���[�̗��߃e�N�X�`���̎��ʎq
	int			m_Texturehp = 0;					    //�v���C���[��HP�e�N�X�`���̎��ʎq
	int			m_Texturecrouching = 0;				//�v���C���[�̂��Ⴊ�݃e�N�X�`���̎��ʎq 
	int			m_Texturelive = 0;
	int			m_Texturehpunder = 0;
	

	bool		m_overheatinit = true;
	bool		m_useRightStick = false;
	bool        m_walkSoundFlag;
	bool        m_landingSoundFlag;
	bool        m_AtSoundFlag;


	float m_AnimeTable[8] =						//�v���C���[�̃e�N�X�`��u�l
	{
		0.0f,
		0.125f,
		0.25f,
		0.375f,
		0.5f,
		0.625f,
		0.75,
		0.875,
	};

	float m_AnimeReservoirTable[5] =			//�v���C���[�̗��߃e�N�X�`��u�l
	{
		0.0f,
		0.2f,
		0.4f,
		0.6f,
		0.8f,
	};

    float m_MukiTable[4] =						//�v���C���[�̌�����v�l
	{
		0.5f,	//������
		0.0f,	//�E����
		0.5f,
		0.0f,
	};

    D3DXVECTOR2 *m_base;							//�J�����̃x�[�X���Q�b�g����

	SLASH *m_slash;
	EFFECT* m_Effect;

public:
	PLAYER(D3DXVECTOR2 *base, SLASH *slash, EFFECT* Effect) : m_base(base), m_slash(slash),m_Effect(Effect){}	//�R���X�g���N�^(�J�����̃x�[�X���󂯎���Ă���)
	~PLAYER();									//�f�X�g���N�^
	void Init(void);							//�v���C���[�̏���������
	void Uninit(void);							//�v���C���[�̏I������
	void Update(void);							//�v���C���[�̃A�b�v�f�[�g����
	void Draw(void);							//�v���C���[�̕`�揈��
	D3DXVECTOR2* GetPlayerPos(void);			//�v���C���[�̈ʒu��Ԃ�
	D3DXVECTOR2 * GetOldPlayerPos(void);
	D3DXVECTOR2* GetPredictPos(void) { return &m_predictpos; }
	int *GetPlayerHp(void) { return &m_hp; }
	bool* GetOnGround(void);					//�n�ʂɂ��邩�ǂ���
	bool* GetGoPredictPos(void);
	bool* GetPlayerUse(void) { return &m_use; }
	int *GetPlayerLive(void) { return &m_live; }
	bool *GetUnrivaled(void) { return &m_unrivaled; }
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

