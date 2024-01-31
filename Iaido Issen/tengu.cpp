#include "tengu.h"
#include "sound1.h"
#include "stagemanager.h"

static int	g_BGM_tengu = 0;		// BGM���ʎq

static int g_Sound_t_at1 = 0;
static int g_Sound_t_at2 = 0;
static int g_Sound_t_at3 = 0;
static int g_Sound_t_at4 = 0;
static int g_Sound_t_at5 = 0;
static int g_Sound_t_at6 = 0;
static int g_Sound_t_at7 = 0;
static int g_Sound_t_at8 = 0;


void TENGU::Init(void)
{
	//�^�C�g����ʗp�e�N�X�`���̓ǂݍ���
	m_TextureTenguHp0 = LoadTexture((char*)"data/TEXTURE/tengu/kuro.png");
	m_TextureTenguHp1 = LoadTexture((char*)"data/TEXTURE/tengu/tengutairyoku.png");
	m_TextureTenguNomal = LoadTexture((char*)"data/TEXTURE/tengu/taiki.png");				//�V��(�ҋ@)
	m_TextureTenguThunderAtk = LoadTexture((char*)"data/TEXTURE/tengu/thunder_atk.png");	//�V��(���U��)
	m_TextureTenguThunder = LoadTexture((char*)"data/TEXTURE/tengu/biribiri.png");			//�V��(����e)
	m_TextureTenguFall = LoadTexture((char*)"data/TEXTURE/tengu/rakka.png");				//�V��(����)
	m_TextureTenguDown = LoadTexture((char*)"data/TEXTURE/tengu/dawn.png");					//�V��(�_�E��)
	m_TextureTenguFire = LoadTexture((char*)"data/TEXTURE/tengu/fire_atk.png");				//�V��(���U��)
	m_TextureTenguWind = LoadTexture((char*)"data/TEXTURE/tengu/wind_atk.png");				//�V��(���U��)
	m_TextureTenguHit = LoadTexture((char*)"data/TEXTURE/tengu/hidan.png");					//�V��(��e)
	m_TextureCloud = LoadTexture((char*)"data/TEXTURE/tengu/cloud1.png");					//�_
	m_TextureThunder = LoadTexture((char*)"data/TEXTURE/tengu/kaminari1.png");				//��
	m_TextureFire = LoadTexture((char*)"data/TEXTURE/tengu/fire1.png");						//��
	m_TextureWind = LoadTexture((char*)"data/TEXTURE/tengu/strom1.png");					//��
	m_TextureExp = LoadTexture((char*)"data/TEXTURE/tengu/Explosion1.png");					//����

	g_Sound_t_at1 = LoadSound((char*)"data/SE/�_�X�����_�y��̉�.wav");
	g_Sound_t_at2 = LoadSound((char*)"data/SE/���{�b.wav");
	g_Sound_t_at3 = LoadSound((char*)"data/SE/����������.wav");
	g_Sound_t_at4 = LoadSound((char*)"data/SE/���S���S��.wav");
	g_Sound_t_at5 = LoadSound((char*)"data/SE/���h�[��.wav");
	g_Sound_t_at6 = LoadSound((char*)"data/SE/����.wav");
	g_Sound_t_at7 = LoadSound((char*)"data/SE/���S���S��2.wav");
	g_Sound_t_at8 = LoadSound((char*)"data/SE/���h�[��.wav");
	

	g_BGM_tengu = LoadSound((char*)"data/BGM/vs�V��.wav");

	
	
	//�V��̐ݒ�
	m_Tengu.pos = D3DXVECTOR2(400, 200);
	m_Tengu.use = true;
	m_Tengu.hp = 3;
	m_Tengu.stateteng = TENGU_STATE_STAY;
	m_Tengu.move = true;
	m_Tengu.nomalFlag = true;
	m_Tengu.thunderAtkFrag = false;
	m_Tengu.thunderHitFlag = false;
	m_Tengu.thunderDownFrame = 0;
	m_Tengu.fallFlag = false;
	m_Tengu.downFlag = false;
	m_Tengu.atkFlag = false;
	m_Tengu.hitFlag = false;
	m_Tengu.texHitFlag = false;
	m_Tengu.fireFlag = false;
	m_Tengu.hitFrame = 0;
	m_Tengu.ReturnNomalFlag = false;
	m_Tengu.windFlag = false;
	m_Tengu.animeCounter = 0;
	m_Tengu.animePtn = 0.0f;

	m_TenguBGMSoundFlag = false;

	//�_�̐ݒ�
	m_Cloud.use = false;
	m_Cloud.anmPtn = 0;
	m_Cloud.anmFrame = 0;

	//���̐ݒ�
	m_Thunder.use = false;

	//�΂̐ݒ�
	for (int i = 0; i < 1; i++)
	{
		m_Fire[i].use = false;
		m_Fire[i].speed = FIRE_SPEED;
		m_Fire[i].onGround = false;
	}

	//���̐ݒ�
	for (int i = 0; i < 1; i++)
	{
		m_Wind[i].use = false;
		m_Wind[i].speed.x = frand() * 10.0 - 5.0f;
		m_Wind[i].speed.y = -3.0f;
	}

	

	//�V��̕��g�̐ݒ�
	m_TenguPre.pos = D3DXVECTOR2(1000, 200);
	m_TenguPre.use = false;
	m_Tengu.vel = 5.0f;
	m_TenguPre.stateteng = TENGU_STATE_NONE;
	m_TenguPre.nomalFlag = true;
	m_Tengu.thunderAtkFrag = false;
	m_TenguPre.fireFlag = false;
	m_TenguPre.windFlag = false;
	m_TenguPre.animeCounter = 0;
	m_TenguPre.animePtn = 0.0f;

	//�_���g�̐ݒ�
	m_CloudPre.use = false;

	//�����g�̐ݒ�
	m_ThunderPre.use = false;

	//�Ε��g�̐ݒ�
	for (int i = 0; i < 1; i++)
	{
		m_FirePre[i].use = false;
		m_FirePre[i].speed = FIRE_SPEED;
		m_FirePre[i].onGround = false;
	}

	//�����g�̐ݒ�
	for (int i = 0; i < 1; i++)
	{
		m_WindPre[i].use = false;
		m_WindPre[i].speed.x = frand() * 10.0 - 5.0f;
		m_WindPre[i].speed.y = -3.0f;
	}

	m_Exp.use = false;
	m_Exp.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_Exp.anmFrame = 0;
	m_Exp.anmPtn = 0.0f;

}

void TENGU::Uninit(void)
{
	m_TenguBGMSoundFlag = false;
	StopSound(g_BGM_tengu);
}

void TENGU::Update(void)
{
	//�V��̏�ԑJ��
	TenguPattenrn();

	TenguPrePattenrn();

	if (m_TenguBGMSoundFlag == false)
	{   
		StopSoundAll();
		//255(-1)�����[�v�w�肷��Ɩ������[�v
		PlaySound(g_BGM_tengu, -1);
		SetVolume(g_BGM_tengu, 0.5);
		m_TenguBGMSoundFlag = true;
	}

	if (m_Wind[0].use == true)//����������Ƃ�������
	{
		if (m_TenguAtSoundFlag1 == false)
		{
			PlaySound(g_Sound_t_at6, -1);
			m_TenguAtSoundFlag1 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag1 = false;
		StopSound(g_Sound_t_at6);
	}


	if (m_Fire[0].use == true)//�΂�����Ƃ�������
	{
		if (m_TenguAtSoundFlag2 == false)
		{
			PlaySound(g_Sound_t_at3, -1);
			m_TenguAtSoundFlag2 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag2 = false;
		StopSound(g_Sound_t_at3);
	}

	if (m_Cloud.use == true )//�_������Ƃ�������
	{
		if (m_TenguAtSoundFlag3 == false)
		{
			PlaySound(g_Sound_t_at4, -1);
			m_TenguAtSoundFlag3 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag3 = false;
		StopSound(g_Sound_t_at4);
	}

	if (m_Thunder.use == true)//��������Ƃ�������
	{
		if (m_TenguAtSoundFlag4 == false)
		{
			PlaySound(g_Sound_t_at5, 0);
			m_TenguAtSoundFlag4 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag4 = false;

	}

	if (m_CloudPre.use == true)//���g�_������Ƃ�������
	{
		if (m_TenguAtSoundFlag5 == false)
		{
			PlaySound(g_Sound_t_at7, -1);
			m_TenguAtSoundFlag5 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag5 = false;
		StopSound(g_Sound_t_at7);
	}

	if (m_ThunderPre.use == true)//���g��������Ƃ�������
	{
		if (m_TenguAtSoundFlag6 == false)
		{
			PlaySound(g_Sound_t_at5, 0);
			m_TenguAtSoundFlag6 = true;
		}
	}
	else
	{
		m_TenguAtSoundFlag6 = false;

	}

	// �A�j���[�V�����̍X�V
	if (m_Tengu.animeCounter > ANIMATION_COUNT)
	{
		m_Tengu.animePtn++;

		if (m_Tengu.animePtn >= 25)
			m_Tengu.animePtn = 0;

		m_Tengu.animeCounter = 0;
	}
	m_Tengu.animeCounter++;

	if (m_Tengu.hp <= 0)
	{
		TenguExp();
		m_Tengu.use = false;
		m_TenguPre.use = false;
	}
}

void TENGU::Draw(void)
{
	
	//�V��̕`�揈��
	if (m_Tengu.use == true)
	{
		// �ҋ@
		if (m_Tengu.nomalFlag == true)
		{
			DrawSprite(m_TextureTenguNomal,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// ���U��
		else if (m_Tengu.thunderAtkFrag == true)
		{
			
			DrawSprite(m_TextureTenguThunderAtk,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// ���d��
		else if (m_Tengu.thunderHitFlag == true)
		{
			DrawSprite(m_TextureTenguThunder,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// ������
		else if (m_Tengu.fallFlag == true)
		{
			DrawSprite(m_TextureTenguFall,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
		}
		// �_�E��
		else if (m_Tengu.downFlag == true)
		{
			DrawSprite(m_TextureTenguDown,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
		}
		// ���U��
		else if (m_Tengu.fireFlag == true)
		{
			DrawSprite(m_TextureTenguFire,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 3, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f);
		}
		// ���U��
		else if (m_Tengu.windFlag == true)
		{
			DrawSprite(m_TextureTenguWind,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				m_Tengu.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f);
		}
		// ��e
		else if (m_Tengu.texHitFlag == true)
		{
			DrawSprite(m_TextureTenguHit,
				m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y,
				192.0f, 256.0f,
				1.0f / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
		}


		//���U���̕`��
		if (m_Cloud.use == true)
		{
			if (m_Thunder.use == true)
			{
				//���̕`��
				DrawSprite(m_TextureThunder, m_base->x + m_Thunder.pos.x, m_base->y + (m_Thunder.pos.y + 512), 600.0f, 1024.0f,
					m_Tengu.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f);
			}

			//�_�̕`��
			DrawSprite(m_TextureCloud, m_base->x + m_Cloud.pos.x, m_base->y + m_Cloud.pos.y, 192.0f, 256.0f,
				m_Cloud.anmPtn / 2.0f, 0.0f, 1.0f / 2.0f, 1.0f);
		}
		//�΍U���̕`��
		for (int i = 0; i < 1; i++)
		{
			if (m_Fire[i].use == true)
			{
				//�΂̕`��
				DrawSprite(m_TextureFire, m_base->x + m_Fire[i].pos.x, m_base->y + m_Fire[i].pos.y, 400.0f, 256.0f,
					m_Tengu.animePtn / 5, ((int)m_Tengu.animePtn) % 5 / 5.0f, PATTERN_ENEMY_WIDTH5, 1.0f / 5.0f);
			}
		}

		//���̍U���̕`��
		for (int i = 0; i < 1; i++)
		{
			if (m_Wind[i].use == true)
			{
				//���̕`��
				DrawSprite(m_TextureWind, m_base->x + m_Wind[i].pos.x, m_base->y + m_Wind[i].pos.y, 250.0f, 310.0f,
					m_Tengu.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f);
				
			}
			
		}
	}

	//���g�V��̕`��
	if (m_TenguPre.use == true)
	{
		// �ҋ@
		if (m_TenguPre.nomalFlag == true)
		{
			DrawSpriteColor(m_TextureTenguNomal,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// ���U��
		else if (m_TenguPre.thunderAtkFrag == true)
		{
			DrawSpriteColor(m_TextureTenguThunderAtk,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// ���d��
		else if (m_TenguPre.thunderHitFlag == true)
		{
			DrawSpriteColor(m_TextureTenguThunder,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / DIVIDE_ENEMY_X, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// ���U��
		else if (m_TenguPre.fireFlag == true)
		{
			DrawSpriteColor(m_TextureTenguFire,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				192.0f, 256.0f,
				m_TenguPre.animePtn / 3, 0.0f, PATTERN_ENEMY_WIDTH3, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		// ���U��
		else if (m_TenguPre.windFlag == true)
		{
			DrawSpriteColor(m_TextureTenguWind,
				m_base->x + m_TenguPre.pos.x, m_base->y + m_TenguPre.pos.y,
				250.0f, 310.0f,
				m_TenguPre.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}




		//���U���̕`��
		if (m_CloudPre.use == true)
		{
			if (m_ThunderPre.use == true)
			{
				//���̕`��
				DrawSpriteColor(m_TextureThunder, m_base->x + m_ThunderPre.pos.x, m_base->y + (m_ThunderPre.pos.y + 512), 600.0f, 1024.0f,
					m_TenguPre.animePtn / 2, 0.0f, PATTERN_ENEMY_WIDTH2, 1.0f,
					D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
			}

			//�_�̕`��
			DrawSpriteColor(m_TextureCloud, m_base->x + m_CloudPre.pos.x, m_base->y + m_CloudPre.pos.y, 192.0f, 256.0f,
				m_CloudPre.anmPtn / 2.0f, 0.0f, 1.0f / 2.0f, 1.0f,
				D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
		}
		//�΍U���̕`��
		for (int i = 0; i < 1; i++)
		{
			if (m_FirePre[i].use == true)
			{
				//�΂̕`��
				DrawSpriteColor(m_TextureFire, m_base->x + m_FirePre[i].pos.x, m_base->y + m_FirePre[i].pos.y, 400.0f, 256.0f,
					m_TenguPre.animePtn / 5, ((int)m_TenguPre.animePtn) % 5 / 5.0f, PATTERN_ENEMY_WIDTH5, 1.0f / 5.0f,
					D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
			}
		}

		//���̍U���̕`��
		for (int i = 0; i < 1; i++)
		{
			if (m_WindPre[i].use == true)
			{
				//���̕`��
				DrawSpriteColor(m_TextureWind, m_base->x + m_WindPre[i].pos.x, m_base->y + m_WindPre[i].pos.y, 250.0f, 310.0f,
					m_TenguPre.animePtn / 4, 0.0f, PATTERN_ENEMY_WIDTH4, 1.0f,
					D3DXCOLOR(0.0f,0.0f,0.5f,1.0f));
			}
		}

	}
	// �����̕`��
	if (m_Exp.use == true)
	{
		DrawSprite(m_TextureExp, m_base->x + m_Tengu.pos.x, m_base->y + m_Tengu.pos.y + 50.0f, 800.0f, 800.0f,
			m_Exp.anmPtn / 5, ((int)m_Exp.anmPtn) % 5 / 6.0f, PATTERN_ENEMY_WIDTH5, 1.0f / 5.0f);
	}

	//HP(��)�̕`��
	for (int i = 3; i >= 1; i--)
	{
		DrawSprite(m_TextureTenguHp0, SCREEN_WIDTH - (100.0f*i), 50.0f, 100.0f, 100.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
	//HP(��)�̕`��
	for (int i = m_Tengu.hp; i >= 1; i--)
	{
		DrawSprite(m_TextureTenguHp1, SCREEN_WIDTH - (100.0f*i), 50.0f, 100.0f, 100.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
	}
}


//----�V��̃p�^�[���J��---------------------------------
void TENGU::TenguPattenrn(void)
{

	if (m_Tengu.use == true)
	{
		//�G�̎��Ԃ�i�߂�
		m_Tengu.frame++;

		//�G�̏�Ԃɂ���ē����؂�ւ���
		switch (m_Tengu.stateteng)
		{
		case TENGU_STATE_STAY:   //�ҋ@���
			TenguState_Stay();
			break;
		case TENGU_STATE_THUNDER1://�����
			TenguState_Thunder();
			break;
		case TENGU_STATE_THUNDER2://�����
			TenguState_Thunder();
			break;
		case TENGU_STATE_THUNDER3://�����
			TenguState_Thunder();
			break;
		case TENGU_STATE_FIRE:   //�΍U�����
			TenguState_Fire();
			break;
		case TENGU_STATE_WIND://���U�����
			TenguState_Wind();
			break;
		case TENGU_STATE_PARTURITION://���g���
			TenguState_Parturition();
			break;
		}

	}
}
//----------------------------------------------------------------------------

//----�V��̑ҋ@����---------------------------------
void TENGU::TenguState_Stay(void)
{
	if (m_Tengu.move == true)
	{
		TextureFlagManager(&m_Tengu.nomalFlag);

		if ((m_Tengu.pos.x <= 0) || (m_Tengu.pos.x >= SCREEN_WIDTH))
			m_Tengu.vel *= -1.0f;

		m_Tengu.pos.x += m_Tengu.vel;

		if (m_TenguPre.use == true)
		{
			r = (rand() % 5) + 2;
		}
		else
		{
			r = (rand() % 6) + 2;
		}

		//�����_���Ŏ��̏�Ԃ�����
		if (m_Tengu.frame >= 180)
		{
			m_Tengu.frame = 0;
			m_Tengu.stateteng = r;
		}
	}

	else // �V�炪�����Ȃ���
	{
		// Ⴢ�Ă���
		if (m_Tengu.thunderHitFlag == true)
		{
			if (m_Tengu.thunderDownFrame >= THUNDER_DOWN_FRAME)
			{
				m_Tengu.thunderDownFrame = 0;
				TextureFlagManager(&m_Tengu.fallFlag);
			}
			m_Tengu.thunderDownFrame++;
		}
		// �����Ă���
		if (m_Tengu.fallFlag == true)
		{
			m_Cloud.use = false;
			m_Thunder.use = false;

			if (m_Tengu.pos.y <= GROUND_POS)
				m_Tengu.pos.y += 5.0f;
			// �n�ʂ܂ŗ�����
			if (m_Tengu.pos.y >= GROUND_POS)
			{
				m_Tengu.pos.y = GROUND_POS;
				TextureFlagManager(&m_Tengu.downFlag);
				m_Tengu.atkFlag = true;
			}
		}
		// �n�ʂ܂ŗ�������
		if (m_Tengu.downFlag == true)
		{
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//Collision_HitTenguPlayerAtk();	// �v���C���[����̍U�����󂯂���
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			if (m_Tengu.downFrame >= DOWN_FRAME)
			{
				m_Tengu.ReturnNomalFlag = true;
				m_Tengu.downFlag = false;
				m_Tengu.downFrame = 0;
			}
			m_Tengu.downFrame++;
		}
		// �U�����󂯂�
		if (m_Tengu.hitFlag == true)
		{
			m_Tengu.downFrame = 0;

			m_Tengu.atkFlag = false;
			TextureFlagManager(&m_Tengu.texHitFlag);

			if (m_Tengu.hitFrame >= HIT_FRAME)
			{
				m_Tengu.ReturnNomalFlag = true;
				m_Tengu.hitFlag = false;
				m_Tengu.hitFrame = 0;
			}
			m_Tengu.hitFrame++;
		}
		// ���̏ꏊ�֖߂�
		if (m_Tengu.ReturnNomalFlag == true)
		{
			TextureFlagManager(&m_Tengu.nomalFlag);

			m_Tengu.pos.y -= 10.0f;
			if (m_Tengu.pos.y <= 200.0f)
			{
				m_Tengu.pos.y = 200.0f;
				m_Tengu.ReturnNomalFlag = false;
				m_Thunder.pos = D3DXVECTOR2(-100.0f, -100.0f);
				m_Tengu.move = true;
			}
		}
	}
}
//----------------------------------------------------------------------------

//----�V��̗��U������---------------------------------
void TENGU::TenguState_Thunder(void)
{
	m_Cloud.frame++;

	if (m_Cloud.frame >= THUNDER_FRAME)
	{
		m_Thunder.frame++;
		//�_������
		m_Thunder.use = true;
		//���̍��W��ݒ�
		m_Thunder.pos = m_Cloud.pos;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//���Ƃ̓����蔻����Ƃ�
		//Collision_Thunder();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		

		if (m_Thunder.frame >= 60)
		{
			//������
			m_Thunder.frame = 0;
			m_Cloud.frame = 0;
			m_Tengu.frame = 0;
			m_Cloud.anmPtn = 0;
			m_Cloud.anmFrame = 0;
			m_Thunder.pos = D3DXVECTOR2(-100.0f, -100.0f); // ��ʓ��ɓ����ȗ����c���Ȃ�
			m_Cloud.use = false;
			m_Thunder.use = false;
			//�ҋ@��ԂɈڍs
			m_Tengu.stateteng = TENGU_STATE_STAY;

		}

	}
	else
	{
		//�v���C���[�ɒǏ]
		TextureFlagManager(&m_Tengu.thunderAtkFrag);

		if(m_Cloud.frame <= THUNDER_FRAME - 20)
		m_Cloud.pos.x = m_playerpos->x;

		m_Cloud.use = true;
		if (m_Cloud.anmFrame >= 20)
		{
			m_Cloud.anmPtn++;
			m_Cloud.anmFrame = 0;
		}
		m_Cloud.anmFrame++;
	}
}
//----------------------------------------------------------------------------

//----�V��̉΍U������---------------------------------
void TENGU::TenguState_Fire(void)
{
	TextureFlagManager(&m_Tengu.fireFlag);

	for (int i = 0; i < 1; i++)
	{
		if (m_Fire[i].use == false)
		{
			//�΂�����
			m_Fire[i].use = true;
			m_Fire[i].pos = m_Tengu.pos;
			m_rand[i] = rand() % SCREEN_WIDTH;
			//�΂̈ړ�����\���n�_��ݒ�
			m_Fire[i].prepos = D3DXVECTOR2(m_rand[i], GROUNDLINE);
		}

		m_Fire[i].vDist = m_Fire[i].prepos - m_Fire[i].pos;
		m_Fire[i].len = D3DXVec2Length(&m_Fire[i].vDist);

		if (m_Fire[i].len >= 2)
		{
			//�V��̉΂��������x�N�g�������
			m_Fire[i].dir = m_Fire[i].prepos - m_Fire[i].pos;
			//�x�N�g���𐳋K������
			D3DXVec2Normalize(&m_Fire[i].dir, &m_Fire[i].dir);

			m_Fire[i].pos += m_Fire[i].dir * m_Fire[i].speed;

			m_Fire[i].frame++;

		}
		else
		{
			if (m_Fire[i].frame != 0)
			{
				m_Fire[i].frame = 0;
				m_Fire[i].onGround = true;
			}
			//�S���n�ʂɕt���Ă�����
			if (m_Fire[0].onGround == true)
			{
				m_Tengu.frame = 0;
				//�ҋ@��ԂɈڍs
				m_Tengu.stateteng = TENGU_STATE_STAY;
			}
		}

	}
}
//----------------------------------------------------------------------------

//----�V��̕��U���̐ݒ�---------------------------------
void TENGU::TenguState_Wind(void)
{
	TextureFlagManager(&m_Tengu.windFlag);

	if (m_Wind[0].use == false)
	{
		m_Wind[0].pos = D3DXVECTOR2(frand() * SCREEN_WIDTH, GROUNDLINE);
		//m_Wind[1].pos = D3DXVECTOR2((frand() * (SCREEN_WIDTH / 2) + SCREEN_WIDTH / 2) - 1, GROUNDLINE);
		m_Wind[0].use = true;
		//m_Wind[1].use = true;
	}
	for (int i = 0; i < 1; i++)
	{

		m_Wind[i].frame++;

		if (m_Wind[i].frame >= 30)
		{
			m_Wind[i].speed.x = frand() * 10.0 - 5.0f;
			m_Wind[i].frame = 0;
		}

		m_Wind[i].pos.y += m_Wind[i].speed.y;

		m_Wind[i].pos.x += m_Wind[i].speed.x;

		if (m_Wind[i].pos.x < 0 || m_Wind[i].pos.x > SCREEN_WIDTH || m_Wind[i].pos.y < 0)
		{
			m_Wind[i].use = false;
		}

		if (m_Wind[0].use == false)
		{
			m_Tengu.frame = 0;
			m_Tengu.stateteng = TENGU_STATE_STAY;
		}

	}
}
//----------------------------------------------------------------------------

//----�V��̕��g��������---------------------------------
void TENGU::TenguState_Parturition(void)
{
	m_TenguPre.pos = D3DXVECTOR2(1000, 200);
	m_TenguPre.use = true;
	m_TenguPre.move = true;

	m_Tengu.stateteng = TENGU_STATE_STAY;
	m_TenguPre.stateteng = TENGU_STATE_STAY;
}
//----------------------------------------------------------------------------


//----�V��(���g)�̃p�^�[���J��---------------------------------
void TENGU::TenguPrePattenrn(void)
{
	if (m_TenguPre.use == true)
	{
		//�G�̎��Ԃ�i�߂�
		m_TenguPre.frame++;

		//�G�̏�Ԃɂ���ē����؂�ւ���
		switch (m_TenguPre.stateteng)
		{
		case TENGU_STATE_STAY:   //�ҋ@���
			TenguPreState_Stay();
			break;
		case TENGU_STATE_THUNDER1://�����
			TenguPreState_Thunder();
			break;
		case TENGU_STATE_THUNDER2://�����
			TenguPreState_Thunder();
			break;
		case TENGU_STATE_THUNDER3://�����
			TenguPreState_Thunder();
			break;
		case TENGU_STATE_FIRE:   //�΍U�����
			TenguPreState_Fire();
			break;
		case TENGU_STATE_WIND://���U�����
			TenguPreState_Wind();
			break;
		}

		// �A�j���[�V�����̍X�V
		if (m_TenguPre.animeCounter > ANIMATION_COUNT)
		{
			m_TenguPre.animePtn++;

			if (m_TenguPre.animePtn >= 25)
				m_TenguPre.animePtn = 0;

			m_TenguPre.animeCounter = 0;
		}
		m_TenguPre.animeCounter++;

	}
}
//----------------------------------------------------------------------------

//----�V��(���g)�̑ҋ@����---------------------------------
void TENGU::TenguPreState_Stay(void)
{
	if (m_TenguPre.move == true)
	{
		if (m_TenguPre.use == true)
		{
			TextureFlagManagerPre(&m_TenguPre.nomalFlag);
			rPre = (rand() % 3) + 2;
		}
		//�����_���Ŏ��̏�Ԃ�����
		if (m_TenguPre.frame >= 360)
		{
			m_TenguPre.frame = 0;
			m_TenguPre.stateteng = rPre;
		}
	}
	else
	{
		// Ⴢ�Ă���
		if (m_TenguPre.thunderHitFlag == true)
		{
			if (m_TenguPre.thunderDownFrame >= THUNDER_DOWN_FRAME)
			{
				m_TenguPre.thunderDownFrame = 0;
				DeletePre(); // ���g������
			}
			m_TenguPre.thunderDownFrame++;
		}
	}

}
//----------------------------------------------------------------------------

//----�V��(���g)�̗��U������---------------------------------
void TENGU::TenguPreState_Thunder(void)
{
	m_CloudPre.frame++;

	if (m_CloudPre.frame >= THUNDER_FRAME)
	{
		m_ThunderPre.frame++;
		//�_������
		m_ThunderPre.use = true;
		//���̍��W��ݒ�
		m_ThunderPre.pos = m_CloudPre.pos;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//���Ƃ̓����蔻����Ƃ�
		//Collision_Thunder();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		if (m_ThunderPre.frame >= 60)
		{
			//������
			m_ThunderPre.frame = 0;
			m_CloudPre.frame = 0;
			m_TenguPre.frame = 0;
			m_ThunderPre.pos = D3DXVECTOR2(-100.0f, -100.0f); // ��ʓ��ɓ����ȗ����c���Ȃ�
			m_CloudPre.use = false;
			m_ThunderPre.use = false;
			//�ҋ@��ԂɈڍs
			m_TenguPre.stateteng = TENGU_STATE_STAY;
		}

	}
	else
	{
		TextureFlagManagerPre(&m_TenguPre.thunderAtkFrag);
		//�v���C���[�ɒǏ]
		if (m_CloudPre.frame <= THUNDER_FRAME - 20)
			m_CloudPre.pos.x = m_playerpos->x;
	
		m_CloudPre.use = true;

		if (m_CloudPre.anmFrame >= 20)
		{
			m_CloudPre.anmPtn++;
			m_CloudPre.anmFrame = 0;
		}
		m_CloudPre.anmFrame++;
	}

}
//----------------------------------------------------------------------------

//----�V��(���g)�̉΍U������---------------------------------
void TENGU::TenguPreState_Fire(void)
{
	TextureFlagManagerPre(&m_TenguPre.fireFlag);
	for (int i = 0; i < 1; i++)
	{
		if (m_FirePre[i].use == false)
		{
			//�΂�����
			m_FirePre[i].use = true;
			m_FirePre[i].pos = m_TenguPre.pos;
			m_randPre[i] = rand() % SCREEN_WIDTH;
			//�΂̈ړ�����\���n�_��ݒ�
			m_FirePre[i].prepos = D3DXVECTOR2(m_randPre[i], GROUNDLINE);
		}

		m_FirePre[i].vDist = m_FirePre[i].prepos - m_FirePre[i].pos;
		m_FirePre[i].len = D3DXVec2Length(&m_FirePre[i].vDist);

		if (m_FirePre[i].len >= 2)
		{
			//�V��̉΂��������x�N�g�������
			m_FirePre[i].dir = m_FirePre[i].prepos - m_FirePre[i].pos;
			//�x�N�g���𐳋K������
			D3DXVec2Normalize(&m_FirePre[i].dir, &m_FirePre[i].dir);

			m_FirePre[i].pos += m_FirePre[i].dir * m_FirePre[i].speed;

			m_FirePre[i].frame++;

		}
		else
		{
			if (m_FirePre[i].frame != 0)
			{
				m_FirePre[i].frame = 0;
				m_FirePre[i].onGround = true;
			}
			//�S���n�ʂɕt���Ă�����
			if (m_FirePre[0].onGround == true)
			{

				m_TenguPre.frame = 0;
				//�ҋ@��ԂɈڍs
				m_TenguPre.stateteng = TENGU_STATE_STAY;
			}
		}

	}
}
//----------------------------------------------------------------------------

//----�V��(���g)�̕��U���̐ݒ�---------------------------------
void TENGU::TenguPreState_Wind(void)
{
	TextureFlagManagerPre(&m_TenguPre.windFlag);
	if (m_WindPre[0].use == false && m_WindPre[1].use == false)
	{
		m_WindPre[0].pos = D3DXVECTOR2(frand() * SCREEN_WIDTH, GROUNDLINE);
		//m_WindPre[1].pos = D3DXVECTOR2(frand() * (SCREEN_WIDTH / 2) + SCREEN_WIDTH / 2, GROUNDLINE);
		m_WindPre[0].use = true;
		//m_WindPre[1].use = true;
	}
	for (int i = 0; i < 1; i++)
	{

		m_WindPre[i].frame++;

		if (m_WindPre[i].frame >= 30)
		{
			m_WindPre[i].speed.x = frand() * 10.0 - 5.0f;
			m_WindPre[i].frame = 0;
		}

		m_WindPre[i].pos.y += m_WindPre[i].speed.y;

		m_WindPre[i].pos.x += m_WindPre[i].speed.x;

		if (m_WindPre[i].pos.x < 0 || m_WindPre[i].pos.x > SCREEN_WIDTH || m_WindPre[i].pos.y < 0)
		{
			m_WindPre[i].use = false;
		}

		if (m_WindPre[0].use == false)
		{
			m_TenguPre.frame = 0;
			m_TenguPre.stateteng = TENGU_STATE_STAY;
		}

	}
}


void TENGU::DeletePre(void)
{
	//���g�������O�ɏ�����
	m_TenguPre.stateteng = TENGU_STATE_STAY;
	m_TenguPre.nomalFlag = true;
	m_TenguPre.thunderAtkFrag = false;
	m_TenguPre.fireFlag = false;
	m_TenguPre.windFlag = false;
	m_TenguPre.animeCounter = 0;
	m_TenguPre.animePtn = 0.0f;

	m_TenguPre.pos = D3DXVECTOR2(-100.0f, -100.0f);
	m_CloudPre.use = false;

	m_ThunderPre.use = false;

	for (int i = 0; i < 3; i++)
	{
		m_FirePre[i].speed = 3.0f;
		m_FirePre[i].onGround = false;
		m_FirePre[i].use = false;
	}

	for (int i = 0; i < 2; i++)
	{
		m_WindPre[i].use = false;
		m_WindPre[i].speed.x = frand() * 10.0 - 5.0f;
		m_WindPre[i].speed.y = -1.0f;
	}

	m_TenguPre.use = false;
}

void TENGU::TenguExp(void)
{
	m_Exp.use = true;
	if (m_Exp.anmFrame >= ANIMATION_COUNT)
	{
		m_Exp.anmPtn++;
		m_Exp.anmFrame = 0.0f;
	}
	m_Exp.anmFrame++;

	if (m_Exp.anmPtn >= 6)
	{
		m_Exp.use = false;
	}
}

void TENGU::TextureFlagManager(bool* Tflag)
{
	m_Tengu.nomalFlag = false;
	m_Tengu.thunderAtkFrag = false;
	m_Tengu.thunderHitFlag = false;
	m_Tengu.fallFlag = false;
	m_Tengu.downFlag = false;
	m_Tengu.texHitFlag = false;
	m_Tengu.fireFlag = false;
	m_Tengu.windFlag = false;

	*Tflag = true;
}

void TENGU::TextureFlagManagerPre(bool* Tflag)
{
	m_TenguPre.nomalFlag = false;
	m_TenguPre.thunderAtkFrag = false;
	m_TenguPre.thunderHitFlag = false;
	m_TenguPre.fallFlag = false;
	m_TenguPre.downFlag = false;
	m_TenguPre.texHitFlag = false;
	m_TenguPre.fireFlag = false;
	m_TenguPre.windFlag = false;

	*Tflag = true;
}
//----------------------------------------------------------------------------
