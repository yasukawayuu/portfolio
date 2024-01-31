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

	D3DXVECTOR2 m_pos[NUM_BLOCKKYUUBI2];		    //�|�W�V����
	D3DXVECTOR2 m_wh[NUM_BLOCKKYUUBI2];			//�傫��
	D3DXVECTOR2 m_block;		//�u���b�N��

	D3DXVECTOR2 m_posdata;        //�|�W�V����
	bool        m_usedata;        //�����t���O

	bool m_bguse;

	bool    m_KyuubiBGMSoundFlag2;

	int			m_blocktype;	//�X�e�[�W�̎��7

	D3DXVECTOR2 m_blockType[2] = {
	{0.0f, 0.0f},	//�n��(0)
	{0.125f, 0.07f},//�����n��(1)
	};

	D3DXVECTOR2 *m_base;							//�J�����̃x�[�X���Q�b�g����
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