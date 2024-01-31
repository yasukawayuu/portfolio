#pragma once

#include "main.h"

class EFFECT
{
private:
	int m_TextureKyuubiSand = 0;    //����̍U�����̍����p�e�N�X�`���̎��ʎq
	int m_TextureSlash = 0;         //�X���b�V���p�e�N�X�`���̎��ʎq
	int m_TextureBlood = 0;         //���t�e�N�X�`���̎��ʎq
	int m_TextureCharge = 0;        //�`���[�W�e�N�X�`���̎��ʎq
	int m_TextureDeath = 0;         //���S�����o�e�N�X�`���̎��ʎq
	int m_TextureHit = 0;           //�q�b�g�e�N�X�`���̎��ʎq
	int m_TextureOverheat = 0;      //�I�[�o�[�q�[�g�e�N�X�`���̎��ʎq
	int m_TextureRun = 0;           //�ʏ�ړ����e�N�X�`���̎��ʎq
	int m_TextureTeleportation = 0; //�u�Ԉړ����e�N�X�`���̎��ʎq
	int m_TextureKyuubiTele = 0;    //����̏u�Ԉړ����̃e�N�X�`�����ʎq
	int m_TextureKyuubiCharge;      //��������͂𗭂߂�Ƃ��̃e�N�X�`���̎��ʎq
	
	int m_Flag;


	
	D3DXVECTOR2 *m_base;			//�J����
	
	struct Effect
	{
		D3DXVECTOR2 pos;                     //�G�t�F�N�g�̃|�W�V����
		D3DXVECTOR2 wh;                      //�G�t�F�N�g�̑傫��
		bool        use;		             //�G�t�F�N�g�̕\��
		float       time;	                 //�G�t�F�N�g�̕\������
		int         muki;		             //�G�t�F�N�g�̌���
		int			animePtn;				 //�G�t�F�N�g�̓����̐؂�ւ�
		int			animeReservoirPtn;		 //�\������Ƃ��̃A�j���[�V����
		int			animeCounter;			 //�G�t�F�N�g�̓����̑����̃x�[�X���Q�b�g����
		D3DXVECTOR2 divide;                  //�G�t�F�N�g�̃A�j���[�V�����̕�����
		D3DXVECTOR2 patternWH;               //�G�t�F�N�g�̃p�^�[����
		int         patternMax;              //�G�t�F�N�g�̍ő�A�j���[�V������
		int         patternWait;             //�G�t�F�N�g�̃A�j���[�V�����E�F�C�g
	};

	float m_mukiTalbelSlash[4]
	{
		D3DX_PI / 2,
		0.0f,
		D3DX_PI / 2,
		0.0f,
	};

	float m_mukiTalbelTeleportation[4]
	{
		D3DX_PI,
		0.0f,
		D3DX_PI,
		0.0f,
	};

	Effect m_KyuubiSand;         //����̂����ۍU�����̍���
	Effect m_Slash;              //�a��
	Effect m_Blood;              //���t
	Effect m_Charge;              //�`���[�W
	Effect m_Death;              //���S�����o
	Effect m_Hit;                //�q�b�g
	Effect m_Overheat;           //�I�[�o�[�q�[�g
	Effect m_Run;                //�ʏ�ړ���
	Effect m_Teleportation;      //�u�Ԉړ�
	Effect m_KyuubiTele;         //����̏u�Ԉړ�
	Effect m_KyuubiCharge;       //����̖��͗���

public:
	EFFECT() {}
	EFFECT(D3DXVECTOR2 *base) : m_base(base) {}
	~EFFECT() {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetKyuubiSand(D3DXVECTOR2 pos);
	void SetSlashEffect(D3DXVECTOR2 pos,int muki);
	void SetBlood(D3DXVECTOR2 pos);
	void SetCharge(D3DXVECTOR2 pos);
	void SetDeath(D3DXVECTOR2 pos);
	void SetHit(D3DXVECTOR2 pos);
	void SetOverheat(D3DXVECTOR2 pos);
	void SetRun(D3DXVECTOR2 pos);
	void SetTeleportation(D3DXVECTOR2 pos);
	void SetKyuubiTele(D3DXVECTOR2 pos);
	void SetKyuubiCharge(D3DXVECTOR2 pos);



	void ResetKyuubiSand(void);
	void ResetSlash(void);
	void ResetBlood(void);
	void ResetCharge(void);
	void ResetDeath(void);
	void ResetHit(void);
	void ResetOverheat(void);
	void ResetRun(void);
	void ResetTeleportation(void);
	void ResetKyuubiTele(void);
	void ResetKyuubiCharge(void);
	

	Effect* GetKyuubiSand(void) { return &m_KyuubiSand; }
	Effect* GetSlash(void) { return &m_Slash; }
	Effect* GetBlood(void) { return &m_Blood; }
	Effect* GetCharge(void) { return &m_Charge; }
	Effect* GetDeath(void) { return &m_Death; }
	Effect* GetHit(void) { return &m_Hit; }
	Effect* GetOverheat(void) { return &m_Overheat; }
	Effect* GetRun(void) { return &m_Run; }
	Effect* GetTeleportation(void) { return &m_Teleportation; }

	void SetFlag(int flag);
};