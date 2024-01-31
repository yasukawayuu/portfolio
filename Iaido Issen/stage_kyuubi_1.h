#pragma once
#include "main.h"

#define NUM_BLOCKKYUUBI1 1

class STAGE_KYUUBI1
{
private:
	int	m_Texture;
	int m_Texturefooting;
	int m_Texturebg;
	int m_Texturehusuma;

	D3DXVECTOR2 m_pos;		    //�|�W�V����
	D3DXVECTOR2 m_wh;			//�傫��
	D3DXVECTOR2 m_block;		//�u���b�N��

	D3DXVECTOR2 m_posdata;        //�|�W�V����
	bool        m_usedata;        //�����t���O

	bool    m_KyuubiBGMSoundFlag;



	int			m_blocktype;	//�X�e�[�W�̎��7

	D3DXVECTOR2 m_blockType[2] = {
	{0.0f, 0.0f},	//�n��(0)
	{0.125f, 0.07f},//�����n��(1)
	};

	D3DXVECTOR2 *m_base;							//�J�����̃x�[�X���Q�b�g����
	D3DXVECTOR2 *m_playerpos;

public:
	STAGE_KYUUBI1(D3DXVECTOR2* playerpos, D3DXVECTOR2 *base) :m_playerpos(playerpos), m_base(base) {}
	~STAGE_KYUUBI1() {}
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR2* GetStagePos(void);
	D3DXVECTOR2* GetStageWh(void);
};