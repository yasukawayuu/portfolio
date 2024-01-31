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
		D3DXVECTOR2 pos;		//九尾の位置
		int		hp;				//HP
		bool    use;
		
		int		LR;

		int		nagiharaianimePtn = 0;	//尻尾を薙ぎ払いアニメパターン
		bool	nagiharaiuse = false;		//尻尾薙ぎ払いの表示

		int		shakeanimePtn = 0;	//尻尾を刺してくるアニメパターン
		bool	shakeuse = false;		//尻尾攻撃の表示

		bool    randomMoveUse = false;

		bool	onibianimeUse = false;	//鬼火を打ってくる時の表示

		int		taikianimePtn = 0;	//待機状態のアニメーション
		int		animeCounter = 0;	 //キャラクター

		int		hitanimePtn;	//攻撃が当たった時のアニメーション
		bool	hitUse = false;			//攻撃のがあったら時の表示	
		int		hitanimeCounter;

		int		guardanimePtn;	//ガードするときのアニメーション
		bool	guardUse = false;		//ガードの時の表示	
		int		guardanimeCounter;

		bool	retrunUse = false;
		int		retrunanimePtn;
		
		bool	youryokuUse = false;

		float	floating;		//浮遊
		float	floatspeed;		//浮遊するスピード

		bool	stage1taikiuse = true;			//ステージ1待機表示
		bool	stage2taikiuse = false;			//ステージ2待機表示



		D3DXVECTOR2	maprandmpos[5] = {};

		NINEFOXMOVE ninefoxmove;	//九尾の行動パターン
	};

	struct ONIBI
	{
		D3DXVECTOR2 pos;		//位置
		D3DXVECTOR2 mappos;		//マップのランダム値を保存する
		D3DXVECTOR2 dir;		//何かの距離

		
		float   radius;			//半径
		float	rotate;			//回転スピード
		float   speed;			//何らの距離までのスピード
		float	frame;

		bool	use;			//表示
	};


	struct TAIL
	{
		D3DXVECTOR2 pos;		//位置
		D3DXVECTOR2 dir;		//何らの距離
		D3DXVECTOR2 playerOldpos;	//プレイヤーのちょっと前の位置	
		bool		use;		//表示

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

	int	 m_TextureNineFox;	//九尾のテクスチャ識別子
	int  m_TextureOnibi;		//鬼火のテクスチャ識別子
	int  m_TextureTail;		//尻尾のテクスチャの識別子
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


	void NineFoxPattenrn1(void);	//九尾の行動パターン更新
	void NineFoxPattenrn2(void);
	void NineFoxPattenrn3(void);

	void NineFoxWait1(void);
	void NineFoxWait2(void);		//九尾と攻撃の更新
	void NineFoxWait3(void);

	void NineFoxTail(NINEFOXMOVE nextmove);		//九尾の尻尾を地面に刺してプレイヤーの足元に出す
	void NineFoxTailShake(NINEFOXMOVE nextmove);//九尾がプレイヤーの目の前に瞬間移動して突き刺しをする
	
	void NineFoxAvatar(void);	//九尾が分身する

	void NineFoxFireMap(NINEFOXMOVE nextmove);	//鬼火がマップにランダムに配置する
	void NineFoxFire(NINEFOXMOVE nextmove);		//九尾の周りに鬼火が出てプレイヤーに追跡する
	void NineFoxReturn(void);  //九尾が手前に戻ってくる
	void NineFoxNoyouyroku(NINEFOXMOVE nextmove); //九尾の妖力なくなった
	void NineFoxNagiharai(NINEFOXMOVE nextmove); //九尾がプレイヤーの目の前に瞬間移動して薙ぎ払いをする

	void NineFoxRandmMove(void); //九尾がマップ上でランダム瞬間移動をする

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
	bool    m_KyuubiSoundFlag5;//チャージ
	bool    m_KyuubiSoundFlag6;

};