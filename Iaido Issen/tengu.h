#pragma once

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define DIVIDE_ENEMY_X 3     //�G�̉��̕�����
#define DIVIDE_ENEMY_Y 2     //�G�̏c�̕�����

#define PATTERN_ENEMY_WIDTH5 (1.0f / 5)         //�G��u�̉���
#define PATTERN_ENEMY_WIDTH4 (1.0f / 4)         //�G��u�̉���
#define PATTERN_ENEMY_WIDTH3 (1.0f / 3)         //�G��u�̉���
#define PATTERN_ENEMY_WIDTH2 (1.0f / 2)         //�G��u�̉���

#define PATTERN_ENEMY_HEIGHT (1.0f / DIVIDE_ENEMY_Y)        //�G��v�̍���

#define THUNDER_DOWN_FRAME (100)	// ���d��ԂɂȂ��Ă���t���[��
#define HIT_FRAME	(50)		// ��e�e�N�X�`����\������t���[����
#define DOWN_FRAME	(500)		// �_�E�����Ă���t���[����

#define GROUND_POS (780.0f)

#define THUNDER_FRAME (200.0f) //����������܂ł̃t���[����

#define FIRE_SPEED (4.0f)	// ���̃X�s�[�h

#define ANIMATION_COUNT (7)	// �A�j���[�V�������X�V����܂ł̃t���[����

#define THUNDER_HIT_SIZE (100.0f)	// ���Ƃ̓����蔻��̑傫��

#define GROUNDLINE 845





enum TENGU_STATE {
	TENGU_STATE_NONE,	      //�V�[���ݒ�Ȃ�
	TENGU_STATE_STAY,         //�ҋ@
	TENGU_STATE_THUNDER1,      //��
	TENGU_STATE_THUNDER2,      //��
	TENGU_STATE_THUNDER3,      //��
	TENGU_STATE_FIRE,	      //��
	TENGU_STATE_WIND,         //��
	TENGU_STATE_PARTURITION,  //���g

	TENGU_STATE_NUM,	      //�I�[�R�[�h
};


class TENGU
{
private:
	int	m_TextureTenguHp0;			// HP(��)�e�N�X�`�����ʎq
	int	m_TextureTenguHp1;			// HP�e�N�X�`�����ʎq
	int	m_TextureTenguNomal;		// �V��(�ҋ@)�e�N�X�`�����ʎq
	int	m_TextureTenguThunderAtk;	// �V��(��)�e�N�X�`�����ʎq
	int	m_TextureTenguThunder;		// �V��(��)�e�N�X�`�����ʎq
	int	m_TextureTenguFall;			// �V��(����)�e�N�X�`�����ʎq
	int m_TextureTenguDown;			// �V��(�_�E��)�e�N�X�`�����ʎq
	int	m_TextureTenguFire;			// �V��(���U��)�e�N�X�`�����ʎq
	int	m_TextureTenguWind;			// �V��(���U��)�e�N�X�`�����ʎq
	int m_TextureTenguHit;			// �V��(��e)�e�N�X�`�����ʎq
	int	m_TextureCloud;	            // �_�e�N�X�`�����ʎq
	int	m_TextureThunder;	        // ���e�N�X�`�����ʎq
	int	m_TextureFire;	            // �΃e�N�X�`�����ʎq
	int	m_TextureWind;	            // ���e�N�X�`�����ʎq
	int	m_TextureExp;	            // �����e�N�X�`�����ʎq

	bool m_TenguAtSoundFlag1;
	bool m_TenguAtSoundFlag2;
	bool m_TenguAtSoundFlag3;
	bool m_TenguAtSoundFlag4;
	bool m_TenguAtSoundFlag5;
	bool m_TenguAtSoundFlag6;
	bool m_TenguBGMSoundFlag;



	struct TENGU_KOUZOUTAI
	{
		D3DXVECTOR2		pos;          //�|�W�V����

		D3DXVECTOR2		dir;          //�ړ�����
		float			speed;        //�ړ��X�s�[�h
		float			vel;

		int				hp;

		int			    muki;         //����
		float			originalPosx; //���WX�̏����l


		bool			swingUpFlag;   //�U��グ��t���O
		bool			swingDownFlag; //�U�肨�낷�t���O

		bool			nomalFlag;		// �ҋ@���[�V�������Đ� (�e�N�X�`��)

		bool			thunderAtkFrag;		// ���U�������Ă��� (�e�N�X�`��)
		bool			thunderHitFlag;		// �������������t���O (�e�N�X�`��)
		int				thunderDownFrame;	// ���œ����Ȃ��Ȃ�t���[����

		bool			downFlag;			// �_�E�����Ă���t���O (�e�N�X�`��)
		int				downFrame;			// �_�E�����Ă���t���[����

		bool			fallFlag;			// ������t���O (�e�N�X�`��)

		bool			fireFlag;			// ���U���t���O (�e�N�X�`��)

		bool			windFlag;			// ���U���t���O (�e�N�X�`��)

		bool			atkFlag;			// �U�����󂯂邩
		bool			hitFlag;			// �U�����󂯂���
		bool			texHitFlag;			// �q�b�g�e�N�X�`����\�����邩 (�e�N�X�`��)
		int				hitFrame;			// �q�b�g�e�N�X�`����\������t���[����

		bool			ReturnNomalFlag;		// ���̈ʒu�֖߂�

		bool			move;			// ��e�Ȃǂœ����Ȃ�����false

		float				animePtn;      //�R�}��
		int				animeCounter;  //�R�}�`��܂ł̃J�E���g

		bool 			use;           //���t���O
		float			frame;         //�i�񂾃t���[����

		int             stateteng;     //�V��̏��

		
	};
	
    int m_rand[3];
    int m_randPre[3];
   
    int r;
    int rPre;
   
   
    float  m_bulletCount = 0.0f;          //�|�����˂����܂ł��J�E���g
    float  m_shildCount = 0.0f;           //�����ːi����܂ł��J�E���g

	float m_AnimeTable[4] =			//�G��uv�l
	{
		0.0f,
		0.3333f,
		0.6666f,
		0.3333f,
	};

	float m_MukiTable[2] =
	{
		0.5f,	//������
		0.0f,	//�E����
	};
	

	struct CLOUD
	{
		D3DXVECTOR2		pos;          //�|�W�V����

		float			frame;        //�i�񂾃t���[����
		float			anmPtn;
		int				anmFrame;

		bool 			use;          //���t���O

	};
	struct THUNDER
	{
		D3DXVECTOR2		pos;          //�|�W�V����

		float			frame;        //�i�񂾃t���[����

		bool 			use;          //���t���O

	};
	struct FIRE
	{
		D3DXVECTOR2		pos;          //�|�W�V����
		D3DXVECTOR2		prepos;       //�\���|�W�V����
		D3DXVECTOR2     dir;          //�����x�N�g��
		D3DXVECTOR2     vDist;        //2�_�Ԃ̋���(�v�Z)

		float			frame;        //�i�񂾃t���[����
		float           speed;        //�΂̑���
		float           len;          //2�_�Ԃ̋���

		bool 			use;          //���t���O
		bool            onGround;     //�΂��n�ʂɂ������̃t���O
	};

	struct WIND
	{
		D3DXVECTOR2		pos;          //�|�W�V����
		D3DXVECTOR2		speed;        //����


		float			frame;        //�i�񂾃t���[����

		bool 			use;          //���t���O

	};

	struct EXP
	{
		D3DXVECTOR2		pos;          //�|�W�V����

		float	anmPtn;
		int		anmFrame;

		bool 			use;          //���t���O

	};

	TENGU_KOUZOUTAI m_Tengu;				      //�V��o�b�t�@
	CLOUD m_Cloud;                     //�_�o�b�t�@
	THUNDER m_Thunder;                 //���o�b�t�@
	FIRE  m_Fire[3];                   //�΃o�b�t�@
	WIND  m_Wind[2];                   //���o�b�t�@


	TENGU_KOUZOUTAI m_TenguPre;				  //�V�番�g�o�b�t�@
	CLOUD m_CloudPre;                  //�_���g�o�b�t�@
	THUNDER m_ThunderPre;              //�����g�o�b�t�@
	FIRE  m_FirePre[3];                //�Ε��g�o�b�t�@
	WIND  m_WindPre[2];                //�����g�o�b�t�@

	EXP  m_Exp;

	D3DXVECTOR2 *m_playerpos;
	D3DXVECTOR2	*m_base;

public:
	TENGU(D3DXVECTOR2 *pos, D3DXVECTOR2* base) :m_playerpos(pos), m_base(base) {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	void TenguPattenrn(void);           //�V��̏�ԑJ��
	void TenguState_Stay(void);         //�V��ҋ@���
	void TenguState_Thunder(void);      //�V�痋�U�����
	void TenguState_Fire(void);         //�V��̉΍U�����
	void TenguState_Wind(void);         //�V��̕��U�����
	void TenguState_Parturition(void);  //�V��̕��g���

	void TenguPrePattenrn(void);           //�V��(���g)�̏�ԑJ��
	void TenguPreState_Stay(void);         //�V��(���g)�ҋ@���
	void TenguPreState_Thunder(void);      //�V��(���g)���U�����
	void TenguPreState_Fire(void);         //�V��(���g)�̉΍U�����
	void TenguPreState_Wind(void);         //�V��(���g)�̕��U�����

	void DeletePre(void);					//���g������

	void TenguExp(void);					//�{�̂𔚔�������

	void TextureFlagManager(bool* Tflag);	// �n�����e�N�X�`���t���O��true�ɂ��āA����ȊO�̃e�N�X�`���t���O��false�ɂ��� (�{��)
	void TextureFlagManagerPre(bool* Tflag);	// �n�����e�N�X�`���t���O��true�ɂ��āA����ȊO�̃e�N�X�`���t���O��false�ɂ��� (���g)


	int *GetTenguHp(void) { return &m_Tengu.hp; }

	bool *GetTenguThunderHitFlag(void){ return &m_Tengu.thunderHitFlag; }
	//bool *GetTenguThunderHitFlag(void) { return &m_Tengu.ReturnNomalFlag; }
	D3DXVECTOR2 *GetTenguPos(void) { return &m_Tengu.pos; }

	TENGU_KOUZOUTAI *GetTengu(void) { return &m_Tengu; }
	CLOUD *GetTenguCloud(void) { return &m_Cloud; }
	THUNDER *GetTenguThunder(void) { return &m_Thunder; }
	FIRE *GetTenguFire(void) { return m_Fire; }
	WIND *GetTenguWind(void) { return m_Wind; }

	TENGU_KOUZOUTAI *GetTenguPre(void) { return &m_TenguPre; }
	CLOUD *GetTenguCloudPre(void) { return &m_CloudPre; }
	THUNDER *GetTenguThunderPre(void) { return &m_ThunderPre; }
	FIRE *GetTenguFirePre(void) { return m_FirePre; }
	WIND *GetTenguWindPre(void) { return m_WindPre; }

};