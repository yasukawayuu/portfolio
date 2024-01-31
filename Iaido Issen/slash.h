#pragma once

#include "main.h"
#include"effect.h"

class SLASH
{
private:
	int m_TextureSHLeft = 0;//�X���b�V���p�e�N�X�`���̎��ʎq
	int m_TextureSHRight = 0;//�X���b�V���p�e�N�X�`���̎��ʎq

	D3DXVECTOR2 m_pos; //�X���b�V���̈ʒu
	bool m_use;		   //�X���b�V���̕\��
	float m_time;	   //�X���b�V���̕\������
	int m_muki;		   //�X���b�V���̌���

	float m_mukiTalbel[4] =
	{
		-80.0f,
		105.0f,
		-80.0f,
		105.0f,
	};

	D3DXVECTOR2 *m_base;							//�J�����̃x�[�X���Q�b�g����
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