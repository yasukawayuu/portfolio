#include "kyuubi.h"
#include "input.h"
#include "sound1.h"

static int g_Sound_Kb_move = 0;
static int g_Sound_Kb_G = 0;
static int g_Sound_Kb_hit = 0;
static int g_Sound_Kb_tame = 0;
static int g_Sound_Kb_at1 = 0;
static int g_Sound_Kb_at6 = 0;
static int g_Sound_Kb_at7 = 0;
static int g_Sound_Kb_at8 = 0;


void KYUUBI::Init(int hp)
{
	m_TextureOnibiNineFox = LoadTexture((char*)"data/TEXTURE/kyuubi/shoumenOnibi.png");
	m_TextureNineFox = LoadTexture((char*)"data/TEXTURE/kyuubi/taiki.png");
	m_TextureOnibi = LoadTexture((char*)"data/TEXTURE/onibi.png");
	m_TextureTail = LoadTexture((char*)"data/TEXTURE/kyuubi/tail.png");
	m_TextureTailNineFox = LoadTexture((char*)"data/TEXTURE/kyuubi/underAttack_1.png");
	m_TextureTailShake = LoadTexture((char*)"data/TEXTURE/kyuubi/ShakeAttack.png");
	m_TextureTailNagiharai = LoadTexture((char*)"data/TEXTURE/kyuubi/nagiharai.png");
	m_TextureHit = LoadTexture((char*)"data/TEXTURE/kyuubi/hidan.png");
	m_TextureGuard = LoadTexture((char*)"data/TEXTURE/kyuubi/gured.png");
	m_TextrueShoumenNineFox = LoadTexture((char*)"data/TEXTURE/kyuubi/shoumenTaiki.png");
	m_TextrueYouRyoKu = LoadTexture((char*)"data/TEXTURE/kyuubi/charge.png");
	m_TextureHpBlack = LoadTexture((char*)"data/TEXTURE/kyuubi/kuro_kyuubi.png");
	m_TextureHp = LoadTexture((char*)"data/TEXTURE/kyuubi/HP_kyuubi.png");
	m_TextureHpHalf = LoadTexture((char*)"data/TEXTURE/kyuubi/hanbun_kyuubi.png");
	m_TextureReturn = LoadTexture((char*)"data/TEXTURE/kyuubi/return.png");

	g_Sound_Kb_move = LoadSound((char*)"data/SE/KB_move.wav");
	g_Sound_Kb_G = LoadSound((char*)"data/SE/KB_G.wav");
	g_Sound_Kb_hit = LoadSound((char*)"data/SE/KB_hit.wav");
	g_Sound_Kb_tame = LoadSound((char*)"data/SE/KB_tya-zi.wav");
	g_Sound_Kb_at1 = LoadSound((char*)"data/SE/KB_At_01_2.wav");
	g_Sound_Kb_at6 = LoadSound((char*)"data/SE/ó≥ä™.wav");
	g_Sound_Kb_at7 = LoadSound((char*)"data/SE/óãÉSÉçÉSÉç2.wav");
	g_Sound_Kb_at8 = LoadSound((char*)"data/SE/óãÉhÅ[Éì.wav");

	m_ninefox.use = true;

	m_ninefox.hp = hp;
	m_ninefox.pos = D3DXVECTOR2(1400.0f, 700.0f);
	m_ninefox.stage1taikiuse = true;
	m_ninefox.stage2taikiuse = false;
	m_ninefox.guardUse = false;
	m_ninefox.hitUse = false;
	m_ninefox.randomMoveUse = false;
	m_ninefox.nagiharaiuse = false;
	m_ninefox.nagiharaianimePtn = 0;
	m_ninefox.shakeuse = false;
	m_ninefox.shakeanimePtn = 0;
	m_tail.use = false;
	m_ninefox.retrunanimePtn = 0;
	m_ninefox.floating = 0.0;
	m_ninefox.floatspeed = 0.15f;
	m_frame = 0.0f;
	m_ninefox.ninefoxmove = NINEFOX_WAIT;
	

	m_ninefoxavatarpos = D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f);
	m_ninefoxavataruse = true;

	for (int i = 0; i < ONIBI_NUM; i++)
	{
		m_onibi[i].use = false;
		m_onibi[i].pos = m_ninefox.pos;
		m_onibi[i].speed = 4.0f;
	}


	for (int i = 0; i < 3; i++)
	{
		m_avataronibi[i].use = true;
		m_avataronibi[i].pos = m_ninefoxavatarpos;
		m_avataronibi[i].speed = 4.0f;
	}

	m_tail.use = false;
	m_tail.pos = D3DXVECTOR2(m_ninefox.pos.x, m_ninefox.pos.y + 500.0f);

	m_half = 5;
	m_KyuubiFireFrame = 0;
	m_returnFlag = false;
	m_RandomMoveFlag = 0;
	m_RandomMoveAnimCounter = false;
}

void KYUUBI::Uninit(void)
{
	
}

void KYUUBI::Update(void)
{
	if (GetKeyboardTrigger(DIK_J))
	{
		m_ninefox.hp--;
	}

	if (m_ninefox.hitUse == true && m_ninefox.guardUse == false)
	{
		if (m_KyuubiSoundFlag3 == false)//hitéûâπÇ™ñ¬ÇÈ
		{
			PlaySound(g_Sound_Kb_hit, 0);
			m_KyuubiSoundFlag3 = true;
		}
	}
	else
	{
		m_KyuubiSoundFlag3 = false;
	}

	if (m_ninefox.hitUse == true && (m_ninefox.shakeuse == false && m_tail.use == false && m_ninefox.nagiharaiuse == false && m_ninefox.onibianimeUse == false && m_ninefox.youryokuUse == false))
	{
		m_ninefox.guardUse = true;

	     if (m_KyuubiSoundFlag2 == false)//ÉKÅ[ÉhéûâπÇ™ñ¬ÇÈ
		 {
				PlaySound(g_Sound_Kb_G, 0);
				m_KyuubiSoundFlag2 = true;
		 }
	}
	else
	{
		m_ninefox.guardUse = false;
		m_KyuubiSoundFlag2 = false;
	}

	if (m_ninefox.pos.x > m_playerpos->x)
	{
		m_ninefox.LR = 0;
	}
	else
	{
		m_ninefox.LR = 1;
	}

	if (m_ninefox.hitanimeCounter > 20)
	{
		if (m_ninefox.hitUse == true && m_ninefox.guardUse == false)
			m_ninefox.hitanimePtn++;

		if (m_ninefox.hitanimePtn >= 2)
		{
			m_ninefox.hitanimePtn = 0;
			m_ninefox.hitUse = false;
			m_ninefox.hp -= 1;
		}

	
		m_ninefox.hitanimeCounter = 0;
	}

	m_ninefox.hitanimeCounter++;

	if (m_ninefox.guardanimeCounter > 10)
	{
		if (m_ninefox.guardUse == true)
			m_ninefox.guardanimePtn++;

		if (m_ninefox.guardanimePtn >= 3)
		{
			m_ninefox.guardanimePtn = 0;
			m_ninefox.hitUse = false;
			m_ninefox.guardUse = false;
		}

		m_ninefox.guardanimeCounter = 0;
	}

	m_ninefox.guardanimeCounter++;


	

	if (m_ninefox.animeCounter > 100)
	{
		//ÉAÉjÉÅÅ[ÉVÉáÉìÉpÉ^Å[ÉìÇêÿÇËë÷Ç¶ÇÈ
		m_ninefox.taikianimePtn++;

		//ç≈å„ÇÃÉAÉjÉÅÅ[ÉVÉáÉìÉpÉ^Å[ÉìÇï\é¶ÇµÇΩÇÁÉäÉZÉbÉgÇ∑ÇÈ
		if (m_ninefox.taikianimePtn >= 4)
			m_ninefox.taikianimePtn = 0;

		m_ninefox.animeCounter = 0;
	}

	m_ninefox.animeCounter++;

	


	if (m_tail.use == false)
	{
		m_ninefox.floating += m_ninefox.floatspeed;	//ã„îˆÇ™è„â∫ïÇÇ≠èàóù

		if (m_ninefox.floating > 5.0f)				//5.0fÇí¥Ç¶ÇΩÇÁÅ~-1Ç≈îΩëŒÇ…
			m_ninefox.floatspeed *= -1;

		if (m_ninefox.floating < -5.0f)
			m_ninefox.floatspeed *= -1;
	}


	if (m_ninefox.hp < 1)
	{
		m_ninefox.use = false;
	}

	if (m_ninefox.shakeuse == true)//èuä‘à⁄ìÆÇÃâπ
	{
		if (m_KyuubiSoundFlag1 == false)
		{
			PlaySound(g_Sound_Kb_move , 0);
			SetVolume(g_Sound_Kb_move, 0.1);
			m_KyuubiSoundFlag1 = true;
		}
	}
	else
	{
		m_ninefox.shakeuse == false;
		m_KyuubiSoundFlag1 = false;
	}
	
	/*if (m_tail.use == false)
	{
		if(m_KyuubiSoundFlag4== false)
		PlaySound(g_Sound_Kb_at1, 0);
		m_KyuubiSoundFlag4 = true;
	}
	else
	{
		m_KyuubiSoundFlag4 = false;
	}*/

	if (m_ninefox.youryokuUse == true)
	{
		if(m_KyuubiSoundFlag5 == false)
		PlaySound(g_Sound_Kb_tame, -1);
		m_ninefox.youryokuUse = false;
		m_KyuubiSoundFlag5 = true;
	}
	else
	{
		StopSound(g_Sound_Kb_tame);
		m_ninefox.youryokuUse = false;
		m_KyuubiSoundFlag5 = false;
	}
	
}

void KYUUBI::Draw(void)
{
	if (m_ninefox.use == true)
	{

		for (int i = 0; i < ONIBI_NUM; i++)
		{
			if (m_onibi[i].use != true)
				continue;


			DrawSpriteColorRotate(m_TextureOnibi, m_base->x + m_onibi[i].pos.x, m_base->y + m_onibi[i].pos.y, 256.0f,
				120.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		}


		if (m_ninefox.guardUse == true)
		{
			DrawSprite(m_TextureGuard, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
				224.0f, m_u[m_ninefox.guardanimePtn], m_v[m_ninefox.LR], 0.3333f, 0.5f);
		}
		else
		{

			if (m_ninefox.stage1taikiuse == true && m_ninefox.shakeuse == false && m_tail.use == false && m_ninefox.randomMoveUse == false)
			{
				DrawSprite(m_TextureNineFox, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
					224.0f, m_u[m_ninefox.taikianimePtn], m_v[m_ninefox.LR], 0.3333f, 0.5f);
			}

			if (m_ninefox.stage2taikiuse == true && m_ninefox.nagiharaiuse == false && m_ninefox.onibianimeUse == false && m_ninefox.youryokuUse == false && m_ninefox.retrunUse == false
				&& m_ninefox.shakeuse == false && m_tail.use == false && m_ninefox.randomMoveUse == false)
			{
				DrawSprite(m_TextrueShoumenNineFox, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
					224.0f, m_u[m_ninefox.taikianimePtn], 0.0f, 0.3333f, 1.0f);
			}
		}

		if (m_ninefox.hitUse == true && m_ninefox.guardUse == false)
		{
			DrawSprite(m_TextureHit, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y, 224.0f,
				224.0f, m_u2[m_ninefox.hitanimePtn], m_v[m_ninefox.LR], 0.5f, 0.5f);
		}
		else
		{
			if (m_tail.use == true)
			{
				DrawSprite(m_TextureTailNineFox, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
					224.0f, m_u[m_tail.tailanimePtn], m_v[m_ninefox.LR], 0.3333f, 0.5f);

				DrawSprite(m_TextureTail, m_base->x + m_tail.pos.x, m_base->y + m_tail.pos.y, 120.0f,
					256.0f, 0.0f, 0.0f, 1.0f, 1.0f);

			}

			if (m_ninefox.shakeuse == true)
			{
				DrawSprite(m_TextureTailShake, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
					224.0f, m_u[m_ninefox.shakeanimePtn], m_v[m_ninefox.LR], 0.3333f, 0.5f);
			}

			if (m_ninefox.nagiharaiuse == true)
			{
				DrawSprite(m_TextureTailNagiharai, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
					224.0f, m_u[m_ninefox.nagiharaianimePtn], m_v[m_ninefox.LR], 0.3333f, 0.5f);
			}


			if (m_ninefox.youryokuUse == true)
			{
				DrawSprite(m_TextrueYouRyoKu, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
					224.0f, m_u[m_ninefox.taikianimePtn], m_v[m_ninefox.LR], 0.3333f, 0.5f);
			}
		}

		if (m_ninefox.onibianimeUse == true)
		{
			DrawSpriteColor(m_TextureOnibiNineFox, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 150.0f,
				150.0f, m_u[m_ninefox.taikianimePtn], 0.0f, 0.3333f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		}

		if (m_ninefox.retrunUse == true)
		{
			if (m_returnFlag == false)
			{
				DrawSpriteColor(m_TextureReturn, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 150.0f,
					150.0f, m_u6[m_ninefox.retrunanimePtn], 0.0f, 0.16666f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			else
			{
				DrawSprite(m_TextureReturn, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
					224.0f, m_u6[m_ninefox.retrunanimePtn], 0.0f, 0.16666f, 1.0f);
			}
			
		}

		if (m_ninefox.randomMoveUse == true)
		{
			DrawSprite(m_TextureReturn, m_base->x + m_ninefox.pos.x, m_base->y + m_ninefox.pos.y + m_ninefox.floating, 224.0f,
			        224.0f, m_u6[m_ninefox.retrunanimePtn], 0.0f, 0.16666f, 1.0f);
		}

		//îÌíeå„HPÇÃï`âÊ
		for (int i = 5; i >= 1; i--)
		{
			DrawSprite(m_TextureHpBlack, SCREEN_WIDTH - (100.0f*i), 50.0f, 100.0f, 100.0f,
				0.0f, 0.0f, 1.0f, 1.0f);
		}
		//îÌíeëOHPHalfÇÃï`âÊ
	    if (m_ninefox.hp == 8)
			m_half = 4;
		else if (m_ninefox.hp == 6)
			m_half = 3;
		else if (m_ninefox.hp == 4)
			m_half = 2;
		else if (m_ninefox.hp == 2)
			m_half = 1;
		else if (m_ninefox.hp == 0)
			m_half = 0;
		for (int i = m_half; i >= 1; i--)
		{
			DrawSprite(m_TextureHpHalf, SCREEN_WIDTH - (100.0f*i), 50.0f, 100.0f, 100.0f,
				0.0f, 0.0f, 1.0f, 1.0f);
		}
		//îÌíeëOHPMAXÇÃï`âÊ
		for (int i = m_ninefox.hp / 2 ; i >= 1; i--)
		{
			DrawSprite(m_TextureHp, SCREEN_WIDTH - (100.0f*i), 50.0f, 100.0f, 100.0f,
				0.0f, 0.0f, 1.0f, 1.0f);
		}
	}
}

void KYUUBI::NineFoxAvatarDraw(void)
{
	if (m_ninefox.use == true)
	{
		if (m_ninefoxavataruse == true)
		{
			DrawSpriteColor(m_TextureOnibiNineFox, m_base->x + m_ninefoxavatarpos.x, m_base->y + m_ninefoxavatarpos.y + m_ninefox.floating, 150.0f,
				150.0f, m_u[m_ninefox.taikianimePtn], 0.0f, 0.3333f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		}

		for (int i = 0; i < 3; i++)
		{
			if (m_avataronibi[i].use != true)
				continue;

			DrawSpriteColorRotate(m_TextureOnibi, m_base->x + m_avataronibi[i].pos.x, m_base->y + m_avataronibi[i].pos.y, 256.0f,
				120.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		}
	}	
}

void KYUUBI::NineFoxPattenrn3(void)
{
	switch (m_ninefox.ninefoxmove)
	{
		//ìGÇÃèÛë‘Ç…ÇÊÇ¡ÇƒìÆçÏÇêÿÇËë÷Ç¶ÇÈ
	case NINEFOX_WAIT:
		NineFoxWait3();
		break;
	case NINEFOX_TAIL:
		NineFoxTail(NINEFOX_TAILSHAKE);
		break;
	case NINEFOX_TAILSHAKE:
		NineFoxTailShake(NINEFOX_NAGIHARAI);
		break;
	case NINEFOX_NAGIHARAI:
		NineFoxNagiharai(NINEFOX_RANDMMOVE);
		break;	
	case NINEFOX_RANDMMOVE:
		NineFoxRandmMove();
		break;
	default:
		m_ninefox.nagiharaiuse = false; 
		m_ninefox.onibianimeUse = false;
		m_ninefox.youryokuUse = false;  
		m_ninefox.retrunUse = false;
		m_RandomMoveFlag = false;
		m_ninefox.shakeuse = false;  
		m_tail.use == false;
		m_ninefox.ninefoxmove = NINEFOX_WAIT;
		break;
	}

}


void KYUUBI::NineFoxPattenrn1(void)
{

	switch (m_ninefox.ninefoxmove)
	{
		//ìGÇÃèÛë‘Ç…ÇÊÇ¡ÇƒìÆçÏÇêÿÇËë÷Ç¶ÇÈ
	case NINEFOX_WAIT:
		NineFoxWait1();
		break;
	case NINEFOX_TAIL:
		NineFoxTail(NINEFOX_TAILSHAKE);
		break;
	case NINEFOX_TAILSHAKE:
		NineFoxTailShake(NINEFOX_RANDMMOVE);
		break;
	case NINEFOX_RANDMMOVE:
		NineFoxRandmMove();
		break;
	}


}

void KYUUBI::NineFoxPattenrn2(void)
{

	switch (m_ninefox.ninefoxmove)
	{
		//ìGÇÃèÛë‘Ç…ÇÊÇ¡ÇƒìÆçÏÇêÿÇËë÷Ç¶ÇÈ
	case NINEFOX_WAIT:
		NineFoxWait2();
		break;
	case NINEFOX_FIRE:
		NineFoxFire(NINEFOX_RETURN);
		break;
	case NINEFOX_FIREMAP:
		NineFoxFireMap(NINEFOX_FIRE);
		break;
	case NINEFOX_RETURN:
		NineFoxReturn();
		break;
	case NINEFOX_YOURYOKU:
		NineFoxNoyouyroku(NINEFOX_WAIT);
		break;
	case NINEFOX_NAGIHARAI:
		NineFoxNagiharai(NINEFOX_FIREMAP);
		break;
	default:
		m_ninefox.shakeuse = false;
		m_tail.use = false;
		m_RandomMoveFlag = false;
		m_ninefox.stage1taikiuse = false;
		m_effect->ResetKyuubiSand();
		m_ninefox.ninefoxmove = NINEFOX_WAIT;
		break;
	}


}

void KYUUBI::NineFoxWait1(void)
{
	
	m_frame = 0.0f;
	m_tail.tailanimePtn = 0;
	m_tail.upextend = 0.0f;
	m_frame = 0.0f;
	m_tail.pos = D3DXVECTOR2(m_ninefox.pos.x, m_ninefox.pos.y + 500.0f);
	m_tail.playerOldpos = D3DXVECTOR2(0.0f, 0.0f);
	m_ninefox.stage1taikiuse = true;
	m_ninefox.ninefoxmove = NINEFOX_TAIL;

	for (int i = 0; i < 5; i++)
	{
		m_ninefox.maprandmpos[i] = D3DXVECTOR2(frand() * 1700.0f + 100.0f, frand() * 490.0f + 100.0f);
	}
}

void KYUUBI::NineFoxWait2(void)
{
	m_ninefox.shakeuse = false;
	m_tail.use = false;
	m_ninefox.stage1taikiuse = false;
	m_ninefox.stage2taikiuse = true;
	m_frame = 0.0f;
	m_tail.playerOldpos = D3DXVECTOR2(0.0f, 0.0f);
	m_ninefox.pos = D3DXVECTOR2(frand() * 1700.0f + 100.0f, frand() * 490.0f + 100.0f);
	for (int i = 0; i < ONIBI_NUM; i++)
	{
		m_onibi[i].pos = m_ninefox.pos;
		m_onibi[i].use = true;
		m_onibi[i].frame = 0.0f;
		m_onibi[i].rotate = 0.0f;

		m_onibi[i].mappos.x = frand() * 1000.0f + 500.0f;
		m_onibi[i].mappos.y = frand() * 800.0f;
	}
	m_ninefox.ninefoxmove = NINEFOX_NAGIHARAI;
}

void KYUUBI::NineFoxWait3(void)
{
	m_ninefox.stage1taikiuse = false;
	m_ninefox.stage2taikiuse = true;
	m_ninefox.pos = D3DXVECTOR2(1400.0f, 850.0f);
	m_frame = 0.0f;
	m_tail.tailanimePtn = 0;
	m_tail.upextend = 0.0f;
	m_frame = 0.0f;
	m_tail.pos = D3DXVECTOR2(m_ninefox.pos.x, m_ninefox.pos.y + 500.0f);
	m_tail.playerOldpos = D3DXVECTOR2(0.0f, 0.0f);
	for (int i = 0; i < 5; i++)
	{
		m_ninefox.maprandmpos[i] = D3DXVECTOR2(frand() * 1700.0f + 100.0f, frand() * 490.0f + 100.0f);
	}
	m_ninefox.ninefoxmove = NINEFOX_TAIL;
}

void KYUUBI::NineFoxTail(NINEFOXMOVE nextmove)
{

	m_frame++;

	m_tail.use = true;

	m_tail.tailanimePtn = 0;

	if (m_frame > 60.0f)
	{
		
		if (m_tail.playerOldpos == D3DXVECTOR2(0.0f, 0.0f))			//ëOÇÃÉvÉåÉCÉÑÅ[ÇÃà íuÇ™âΩÇ‡Ç»Ç©Ç¡ÇΩÇÁ
		{
			m_tail.playerOldpos = *m_playerpos;
		}

		m_effect->SetKyuubiSand(D3DXVECTOR2(m_tail.playerOldpos.x, SCREEN_HEIGHT - 64));
		m_tail.tailanimePtn = 1;
	}


	if (m_frame > 120.0f)
	{
		m_tail.tailanimePtn = 2;

		if(m_tail.upextend <= 350.0f)
		m_tail.upextend += 10.0f;

		

		m_tail.pos = D3DXVECTOR2(m_tail.playerOldpos.x, 1200.0f - m_tail.upextend); //ÉvÉåÉCÉÑÅ[ÇÃë´å≥Ç≈èôÅXÇ…è„Ç…êLÇ—ÇƒÇ¢Ç≠
	}

	if (m_frame > 150.0f)
	{
		m_effect->ResetKyuubiSand();
	}

	if (m_frame > 180.0f)
	{
		m_frame = 0;
		m_tail.playerOldpos = D3DXVECTOR2(0.0f, 0.0f);
		m_tail.use = false;
		m_tail.tailanimePtn = 0;
		m_ninefox.ninefoxmove = nextmove;

	}
}

void KYUUBI::NineFoxTailShake(NINEFOXMOVE nextmove)
{

	m_frame++;

	if (m_frame > 120.0f)									//2ïbëOÇÃÉvÉåÉCÉÑÅ[ÇÃà íuÇÇ∆Ç¡ÇƒÇÈ
	{
		if (m_tail.playerOldpos == D3DXVECTOR2(0.0f, 0.0f))
		{
			m_tail.playerOldpos = *m_playerpos;
		}

		if(m_ninefox.shakeuse == false)
		m_effect->SetKyuubiTele(D3DXVECTOR2(m_ninefox.pos.x,m_ninefox.pos.y + 80));

		m_ninefox.pos.x = m_tail.playerOldpos.x + 128.0f;			//ÉvÉåÉCÉÑÅ[ÇÃâEë§Ç…
		m_ninefox.pos.y = m_tail.playerOldpos.y;

		m_ninefox.shakeuse = true;

		m_ninefox.shakeanimePtn = 0;
	}

	if (m_frame > 150.0f)
		m_ninefox.shakeanimePtn = 1;

	if(m_frame > 180.0f)
		m_ninefox.shakeanimePtn = 2;

	if (m_frame > 200.0f)									//5ïbåoÇ¡ÇΩÇÁñﬂÇÈ
	{
		m_tail.playerOldpos = D3DXVECTOR2(0.0f, 0.0f);
		m_ninefox.shakeuse = false;
		m_ninefox.shakeanimePtn = 0;
		m_frame = 0;
		m_ninefox.ninefoxmove = nextmove;
	}
}

void KYUUBI::NineFoxAvatar(void)
{
	m_avatarframe++;

	for (int i = 0; i < 3; i++)
	{
		if (m_avataronibi[i].use != true)
			continue;

		m_avataronibi[i].frame++;
		m_avataronibi[i].rotate += 0.01f;

		if (m_avataronibi[i].radius < 150.0f)
			m_avataronibi[i].radius += 10.0f;

		if (m_avataronibi[i].frame <= 30.0f * i)										//ÇPïbä‘äuÇäJÇØÇƒ
		{
			m_avataronibi[i].pos = m_ninefoxavatarpos;									//ã„îˆÇÃà íuÇíÜêSÇ∆ÇµÇƒ
			m_avataronibi[i].pos.x += cos(2 * D3DX_PI / 3 * i + m_avataronibi[i].rotate) * m_avataronibi[i].radius;	//150ÇÃîºåaÇ≈âÒì]Ç∑ÇÈ
			m_avataronibi[i].pos.y += sin(2 * D3DX_PI / 3 * i + m_avataronibi[i].rotate) * m_avataronibi[i].radius;
		}


		if (m_avataronibi[i].use == true && m_avataronibi[i].frame >= 90.0f * i)		    //1ïbä‘äuÇäJÇØÇƒí«ê’
		{
			m_avataronibi[i].dir = *m_playerpos - m_avataronibi[i].pos;

			D3DXVec2Normalize(&m_avataronibi[i].dir, &m_avataronibi[i].dir);

			m_avataronibi[i].pos += (m_avataronibi[i].dir * m_avataronibi[i].speed);
		}

		D3DXVECTOR2 dist = m_avataronibi[i].pos - *m_playerpos;

		float len = D3DXVec2Length(&dist);

		if (len < 20 && m_avataronibi[i].use == true)
		{
			if (*m_playerunrivaled == false)
			*m_playerhp -= 1;
			m_avataronibi[i].use = false;
		}

		if (m_avataronibi[i].frame > 240.0f + 30.0f * i&& m_avataronibi[i].use == true)								//1ïbå„Ç…èoî≠ÇµÇΩÇ‚Ç¬ÇÕëOÇÃÇ‚Ç¬ÇÊÇËÇPïbíxÇ≠Ç…è¡Ç¶ÇÈ
		{
			m_avataronibi[i].use = false;
		}

	}

	if (m_avatarframe > 1000.0f)
	{
		for (int i = 0; i < 3; i++)
		{
			m_avataronibi[i].pos = m_ninefoxavatarpos;
			m_avataronibi[i].radius = 0;
			m_avataronibi[i].rotate = 0;
			m_avataronibi[i].use = true;
			m_avataronibi[i].frame = 0.0f;
			m_avatarframe = 0.0f;
		}
	}
}

void KYUUBI::NineFoxFireMap(NINEFOXMOVE nextmove)
{

	m_ninefox.onibianimeUse = true;
	m_ninefox.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f);

	if (m_KyuubiFireFrame > 60.0f)
	{
		m_ninefox.ninefoxmove = nextmove;
		m_KyuubiFireFrame = 0.0f;
	}
	m_KyuubiFireFrame++;
	//for (int i = 0; i < (ONIBI_NUM / 2); i++)						//ãSâŒÇÃîºï™ÇÃêîÇÉãÅ[ÉvÇ≥ÇπÇƒÇÈ
	//{
	//	
	//  m_onibi[i].frame++;
	//	if (m_onibi[i].use == true)
	//	{
	//		m_onibi[i].dir = m_onibi[i].mappos - m_onibi[i].pos;	//éwíËÇµÇΩèÍèäÇ∆ãSâŒÇ∆ÇÃãóó£

	//		D3DXVec2Normalize(&m_onibi[i].dir, &m_onibi[i].dir);
	//	}

	//	D3DXVECTOR2 dist = m_onibi[i].pos - m_onibi[i].mappos;

	//	float len = D3DXVec2Length(&dist);

	//	if (len > 20 && m_onibi[i].use == true)
	//	{
	//		m_onibi[i].pos += (m_onibi[i].dir * m_onibi[i].speed);	//ãóó£Ç™20à»ì‡Ç…Ç»ÇÈÇ‹Ç≈ãﬂÇ√Ç≠

	//	}
	//	if (m_onibi[i].frame > 60.0f)
	//	{
	//		m_onibi[i].frame = 0.0f;
	//		
	//	}

	//}
}

void KYUUBI::NineFoxFire(NINEFOXMOVE nextmove)
{

	for (int i = 0; i < ONIBI_NUM; i++)
	{

		if (m_onibi[i].use != true)
			continue;

		m_onibi[i].frame++;
		m_onibi[i].rotate += 0.01f;

		if (m_onibi[i].radius < 150.0f)
			m_onibi[i].radius += 10.0f;

		if (m_onibi[i].frame <= 30.0f * (i + 1))										//ÇPïbä‘äuÇäJÇØÇƒ
		{
			m_onibi[i].pos = m_ninefox.pos;										//ã„îˆÇÃà íuÇíÜêSÇ∆ÇµÇƒ
			m_onibi[i].pos.x += cos(2 * D3DX_PI / ONIBI_NUM * (i - ONIBI_NUM) + m_onibi[i].rotate) * m_onibi[i].radius;	//150ÇÃîºåaÇ≈âÒì]Ç∑ÇÈ
			m_onibi[i].pos.y += sin(2 * D3DX_PI / ONIBI_NUM * (i - ONIBI_NUM) + m_onibi[i].rotate) * m_onibi[i].radius;
		}


		if (m_onibi[i].use == true && m_onibi[i].frame >= 30.0f * (i + 1))		    //1ïbä‘äuÇäJÇØÇƒí«ê’
		{
			m_onibi[i].dir = *m_playerpos - m_onibi[i].pos;

			D3DXVec2Normalize(&m_onibi[i].dir, &m_onibi[i].dir);

			m_onibi[i].pos += (m_onibi[i].dir * m_onibi[i].speed);
		}

		D3DXVECTOR2 dist = m_onibi[i].pos - *m_playerpos;

		float len = D3DXVec2Length(&dist);

		if (len < 20 && m_onibi[i].use == true)
		{
			if (*m_playerunrivaled == false)
			*m_playerhp -= 1;
			m_onibi[i].use = false;
		}

		if (m_onibi[i].frame > 240.0f + 30.0f * i&& m_onibi[i].use == true)								//1ïbå„Ç…èoî≠ÇµÇΩÇ‚Ç¬ÇÕëOÇÃÇ‚Ç¬ÇÊÇËÇPïbíxÇ≠Ç…è¡Ç¶ÇÈ
		{
			m_onibi[i].use = false;
		}

	}

	if (m_onibi[0].use == false && m_onibi[1].use == false && m_onibi[2].use == false && m_onibi[3].use == false && m_onibi[4].use == false)
	{
		for (int i = 0; i < ONIBI_NUM; i++)
		{
			m_onibi[i].radius = 0;
			m_onibi[i].rotate = 0;
		}
		
		m_ninefox.ninefoxmove = nextmove;
	}



}

void KYUUBI::NineFoxReturn(void)
{
	m_frame++;

	m_ninefox.onibianimeUse = false;
	m_ninefox.retrunUse = true;

	if (m_frame > 10.0f)
	{
		if (m_returnFlag == false)
		{
			m_ninefox.retrunanimePtn++;
		}
		else
		{
			m_ninefox.retrunanimePtn--;
		}
		if (m_ninefox.retrunanimePtn > 5)
		{
			m_ninefox.retrunanimePtn = 5;
			m_ninefox.pos = D3DXVECTOR2(1400.0f, 850.0f);
			m_returnFlag = true;
			
		}
		if (m_returnFlag == true && m_ninefox.retrunanimePtn <= 0)
		{
			m_returnFlag = false;
			m_ninefox.retrunanimePtn = 0;
			m_ninefox.stage2taikiuse = false;
			m_ninefox.retrunUse = false;
			m_frame = 0.0f;
			m_ninefox.ninefoxmove = NINEFOX_YOURYOKU;
		}
		
		m_frame = 0.0f;
	}


}

void KYUUBI::NineFoxNoyouyroku(NINEFOXMOVE nextmove)
{
	for (int i = 0; i < ONIBI_NUM; i++)
	{
		m_onibi[i].use = false;
	}
	m_frame++;
	
	m_ninefox.youryokuUse = true;

	m_effect->SetKyuubiCharge(m_ninefox.pos);

	if (m_frame > 240.0f)
	{
		m_ninefox.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f);
		m_ninefox.youryokuUse = false;
		m_ninefox.ninefoxmove = nextmove;
		m_effect->ResetKyuubiCharge();
	}
}

void KYUUBI::NineFoxNagiharai(NINEFOXMOVE nextmove)
{

	m_frame++;

	for (int i = 0; i < ONIBI_NUM; i++)
	{
		m_onibi[i].pos = m_ninefox.pos;
	}

	if (m_frame > 120.0f)									//2ïbëOÇÃÉvÉåÉCÉÑÅ[ÇÃà íuÇÇ∆Ç¡ÇƒÇÈ
	{
		if (m_tail.playerOldpos == D3DXVECTOR2(0.0f, 0.0f))
		{
			m_tail.playerOldpos = *m_playerpos;
		}

		m_ninefox.pos.x = m_tail.playerOldpos.x + 128.0f;			//ÉvÉåÉCÉÑÅ[ÇÃâEë§Ç…
		m_ninefox.pos.y = m_tail.playerOldpos.y;

		m_ninefox.nagiharaiuse = true;

		m_ninefox.nagiharaianimePtn = 0;
	}

	if (m_frame > 150.0f)
		m_ninefox.nagiharaianimePtn = 1;

	if (m_frame > 180.0f)
		m_ninefox.nagiharaianimePtn = 2;

	if (m_frame > 200.0f)									//5ïbåoÇ¡ÇΩÇÁñﬂÇÈ
	{
		m_ninefox.nagiharaianimePtn = 0;

		m_ninefox.nagiharaiuse = false;

		m_frame = 0.0f;

		for (int i = 0; i < ONIBI_NUM; i++)
		{
			m_onibi[i].pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f);
		}

		m_ninefox.ninefoxmove = nextmove;
	}
}


void KYUUBI::NineFoxRandmMove(void)
{
	m_frame++;
	m_ninefox.randomMoveUse = true;

	if (m_frame > 60)
	{
		switch (m_RandomMoveFlag)
		{
		case 0:
			if (m_RandomMoveAnimCounter > 10.0f)
			{
				if (m_returnFlag == false)
				{
					m_ninefox.retrunanimePtn++;
				}
				else
				{
					m_ninefox.retrunanimePtn--;
				}

				if (m_ninefox.retrunanimePtn > 5)
				{
					m_ninefox.retrunanimePtn = 5;
					m_ninefox.pos = m_ninefox.maprandmpos[0];
					m_returnFlag = true;
				}
				if (m_returnFlag == true && m_ninefox.retrunanimePtn <= 0)
				{
					m_returnFlag = false;
					m_ninefox.retrunanimePtn = 0;
					m_RandomMoveFlag = 1;
					
				}
				m_RandomMoveAnimCounter = 0.0f;
			}
			m_RandomMoveAnimCounter++;
			break;
		case 1:
			if (m_RandomMoveAnimCounter > 10.0f)
			{
				if (m_returnFlag == false)
				{
					m_ninefox.retrunanimePtn++;
				}
				else
				{
					m_ninefox.retrunanimePtn--;
				}

				if (m_ninefox.retrunanimePtn > 5)
				{
					m_ninefox.retrunanimePtn = 5;
					m_ninefox.pos = m_ninefox.maprandmpos[1];
					m_returnFlag = true;
				}
				if (m_returnFlag == true && m_ninefox.retrunanimePtn <= 0)
				{
					m_returnFlag = false;
					m_ninefox.retrunanimePtn = 0;
					m_RandomMoveFlag = 2;

				}
				m_RandomMoveAnimCounter = 0.0f;
			}
			m_RandomMoveAnimCounter++;
			break;
		case 2:
			if (m_RandomMoveAnimCounter > 10.0f)
			{
				if (m_returnFlag == false)
				{
					m_ninefox.retrunanimePtn++;
				}
				else
				{
					m_ninefox.retrunanimePtn--;
				}

				if (m_ninefox.retrunanimePtn > 5)
				{
					m_ninefox.retrunanimePtn = 5;
					m_ninefox.pos = m_ninefox.maprandmpos[2];
					m_returnFlag = true;
				}
				if (m_returnFlag == true && m_ninefox.retrunanimePtn <= 0)
				{
					m_returnFlag = false;
					m_ninefox.retrunanimePtn = 0;
					m_RandomMoveFlag = 3;

				}
				m_RandomMoveAnimCounter = 0.0f;
			}
			m_RandomMoveAnimCounter++;
			break;
		case 3:
			if (m_RandomMoveAnimCounter > 10.0f)
			{
				if (m_returnFlag == false)
				{
					m_ninefox.retrunanimePtn++;
				}
				else
				{
					m_ninefox.retrunanimePtn--;
				}

				if (m_ninefox.retrunanimePtn > 5)
				{
					m_ninefox.retrunanimePtn = 5;
					m_ninefox.pos = m_ninefox.maprandmpos[3];
					m_returnFlag = true;
				}
				if (m_returnFlag == true && m_ninefox.retrunanimePtn <= 0)
				{
					m_returnFlag = false;
					m_ninefox.retrunanimePtn = 0;
					m_RandomMoveFlag = 4;

				}
				m_RandomMoveAnimCounter = 0.0f;
			}
			m_RandomMoveAnimCounter++;
			break;
		case 4:
			if (m_RandomMoveAnimCounter > 10.0f)
			{
				if (m_returnFlag == false)
				{
					m_ninefox.retrunanimePtn++;
				}
				else
				{
					m_ninefox.retrunanimePtn--;
				}

				if (m_ninefox.retrunanimePtn > 5)
				{
					m_ninefox.retrunanimePtn = 5;
					m_ninefox.pos = m_ninefox.maprandmpos[4];
					m_returnFlag = true;
				}
				if (m_returnFlag == true && m_ninefox.retrunanimePtn <= 0)
				{
					m_returnFlag = false;
					m_ninefox.retrunanimePtn = 0;
					m_RandomMoveFlag = 5;

				}
				m_RandomMoveAnimCounter = 0.0f;
			}
			m_RandomMoveAnimCounter++;
			break;
		case 5:
			if (m_RandomMoveAnimCounter > 10.0f)
			{
				if (m_returnFlag == false)
				{
					m_ninefox.retrunanimePtn++;
				}
				else
				{
					m_ninefox.retrunanimePtn--;
				}

				if (m_ninefox.retrunanimePtn > 5)
				{
					m_ninefox.retrunanimePtn = 5;
					m_ninefox.pos = D3DXVECTOR2(1400.0f, 850.0f);
					m_returnFlag = true;
				}
				if (m_returnFlag == true && m_ninefox.retrunanimePtn <= 0)
				{
					m_returnFlag = false;
					m_ninefox.randomMoveUse = false;
					m_ninefox.retrunanimePtn = 0;
					m_RandomMoveFlag = 0;
					m_frame = 0;
					m_ninefox.ninefoxmove = NINEFOX_WAIT;
				}
				m_RandomMoveAnimCounter = 0.0f;
			}
			m_RandomMoveAnimCounter++;
			break;
		}
	}
	
}