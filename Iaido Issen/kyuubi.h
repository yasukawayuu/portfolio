#pragma once
#include "main.h"
#include "effect.h"

#define ONIBI_NUM 5

enum NINEFOXMOVE
{
	NINEFOX_WAIT,
	NINEFOX_FIRE,
	NINEFOX_FIREMAP,
	NINEFOX_TAIL,
	NINEFOX_TAILSHAKE,
	NINEFOX_RETURN,
	NINEFOX_YOURYOKU,
	NINEFOX_NAGIHARAI,
	NINEFOX_RANDMMOVE,
	NINEFOX_AVATAR,

	NINEFOX_NONE
};


class KYUUBI
{
private:
	struct NINEFOX
	{
		D3DXVECTOR2 pos;		//����̈ʒu
		int		hp;				//HP
		bool    use;
		
		int		LR;

		int		nagiharaianimePtn = 0;	//�K����ガ�����A�j���p�^�[��
		bool	nagiharaiuse = false;		//�K���ガ�����̕\��

		int		shakeanimePtn = 0;	//�K�����h���Ă���A�j���p�^�[��
		bool	shakeuse = false;		//�K���U���̕\��

		bool    randomMoveUse = false;

		bool	onibianimeUse = false;	//�S�΂�ł��Ă��鎞�̕\��

		int		taikianimePtn = 0;	//�ҋ@��Ԃ̃A�j���[�V����
		int		animeCounter = 0;	 //�L�����N�^�[

		int		hitanimePtn;	//�U���������������̃A�j���[�V����
		bool	hitUse = false;			//�U���̂��������玞�̕\��	
		int		hitanimeCounter;

		int		guardanimePtn;	//�K�[�h����Ƃ��̃A�j���[�V����
		bool	guardUse = false;		//�K�[�h�̎��̕\��	
		int		guardanimeCounter;

		bool	retrunUse = false;
		int		retrunanimePtn;
		
		bool	youryokuUse = false;

		float	floating;		//���V
		float	floatspeed;		//���V����X�s�[�h

		bool	stage1taikiuse = true;			//�X�e�[�W1�ҋ@�\��
		bool	stage2taikiuse = false;			//�X�e�[�W2�ҋ@�\��



		D3DXVECTOR2	maprandmpos[5] = {};

		NINEFOXMOVE ninefoxmove;	//����̍s���p�^�[��
	};

	struct ONIBI
	{
		D3DXVECTOR2 pos;		//�ʒu
		D3DXVECTOR2 mappos;		//�}�b�v�̃����_���l��ۑ�����
		D3DXVECTOR2 dir;		//�����̋���

		
		float   radius;			//���a
		float	rotate;			//��]�X�s�[�h
		float   speed;			//����̋����܂ł̃X�s�[�h
		float	frame;

		bool	use;			//�\��
	};


	struct TAIL
	{
		D3DXVECTOR2 pos;		//�ʒu
		D3DXVECTOR2 dir;		//����̋���
		D3DXVECTOR2 playerOldpos;	//�v���C���[�̂�����ƑO�̈ʒu	
		bool		use;		//�\��

		int			tailanimePtn;
		float		upextend;
	};


	NINEFOX m_ninefox;
	ONIBI m_onibi[ONIBI_NUM];
	ONIBI m_avataronibi[3];
	TAIL  m_tail;

	float	m_frame;
	float	m_avatarframe;
	int     m_half;
	int     m_KyuubiFireFrame;
	bool    m_returnFlag;
	int     m_RandomMoveFlag;
	int     m_RandomMoveAnimCounter;


	D3DXVECTOR2 m_ninefoxavatarpos;
	bool m_ninefoxavataruse;

	int	 m_TextureNineFox;	//����̃e�N�X�`�����ʎq
	int  m_TextureOnibi;		//�S�΂̃e�N�X�`�����ʎq
	int  m_TextureTail;		//�K���̃e�N�X�`���̎��ʎq
	int  m_TextureTailNineFox;	
	int  m_TextureTailShake;
	int  m_TextureTailNagiharai;
	int  m_TextureOnibiNineFox;
	int  m_TextureHit;
	int  m_TextureGuard;
	int  m_TextrueShoumenNineFox;
	int  m_TextrueYouRyoKu;
	int	 m_TextureHp;
	int  m_TextureHpBlack;
	int  m_TextureHpHalf;
	int  m_TextureReturn;

	float m_u[4]
	{
		0.0f,
		0.3333f,
		0.6666f,
		0.3333f
	};

	float m_u2[2]
	{
		0.0f,
		0.5f
	};

	float m_u6[6]
	{
		0.0000f,
		0.1666f,
		0.3333f,
		0.4999f,
		0.6666f,
		0.8333f,
	};

	float m_v[2]
	{
		0.0f,
		0.5f
	};

	int *m_playerhp;
	bool *m_playerunrivaled;
	D3DXVECTOR2 *m_playerpos;
	D3DXVECTOR2	*m_base;
	EFFECT* m_effect;
public:
	KYUUBI(D3DXVECTOR2 *pos, D3DXVECTOR2* base, EFFECT* effect,int *playerhp,bool *playerunrivaled) :m_playerpos(pos), m_base(base),m_effect(effect),m_playerhp(playerhp),m_playerunrivaled(playerunrivaled){}
	void Init(int hp);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void NineFoxAvatarDraw(void);


	void NineFoxPattenrn1(void);	//����̍s���p�^�[���X�V
	void NineFoxPattenrn2(void);
	void NineFoxPattenrn3(void);

	void NineFoxWait1(void);
	void NineFoxWait2(void);		//����ƍU���̍X�V
	void NineFoxWait3(void);

	void NineFoxTail(NINEFOXMOVE nextmove);		//����̐K����n�ʂɎh���ăv���C���[�̑����ɏo��
	void NineFoxTailShake(NINEFOXMOVE nextmove);//������v���C���[�̖ڂ̑O�ɏu�Ԉړ����ē˂��h��������
	
	void NineFoxAvatar(void);	//��������g����

	void NineFoxFireMap(NINEFOXMOVE nextmove);	//�S�΂��}�b�v�Ƀ����_���ɔz�u����
	void NineFoxFire(NINEFOXMOVE nextmove);		//����̎���ɋS�΂��o�ăv���C���[�ɒǐՂ���
	void NineFoxReturn(void);  //�������O�ɖ߂��Ă���
	void NineFoxNoyouyroku(NINEFOXMOVE nextmove); //����̗d�͂Ȃ��Ȃ���
	void NineFoxNagiharai(NINEFOXMOVE nextmove); //������v���C���[�̖ڂ̑O�ɏu�Ԉړ����ēガ����������

	void NineFoxRandmMove(void); //������}�b�v��Ń����_���u�Ԉړ�������

	bool *GetNineFoxHitUse(void) { return &m_ninefox.hitUse; }
	bool *GetNineFoxOnibiUse(void) { return &m_ninefox.onibianimeUse; }
	bool *GetNineFoxReturnUse(void) { return &m_ninefox.retrunUse; }
	D3DXVECTOR2 *GetNineFoxPos(void) { return &m_ninefox.pos; }
	int *GetNineFoxHp(void) { return &m_ninefox.hp; }
	D3DXVECTOR2 *GetNineFoxTail(void) { return &m_tail.pos; }
	bool *GetNineFoxTailUse(void) { return &m_tail.use; }
	int *GetNineFoxSkakePtn(void) { return &m_ninefox.shakeanimePtn; }
	int *GetNineFoxNagiharaiPtn(void) {	return &m_ninefox.nagiharaianimePtn; }
	D3DXVECTOR2 *GetOnibiPos(void) { return &m_onibi->pos; }
	int *GetHalf(void) { return &m_half; }

	bool    m_KyuubiSoundFlag1;
	bool    m_KyuubiSoundFlag2;//g
	bool    m_KyuubiSoundFlag3;//hit
	bool    m_KyuubiSoundFlag4;//at1
	bool    m_KyuubiSoundFlag5;//�`���[�W
	bool    m_KyuubiSoundFlag6;

};