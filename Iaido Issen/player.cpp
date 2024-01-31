/*==============================================================================

   ���_�Ǘ� [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "sound1.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define DIVIDE_X 3	//���̕�����
#define DIVIDE_Y 2	//�c�̕�����
#define RUN_DIVIDE_X 8	//���̕�����
#define RUN_DIVIDE_Y 2	//�c�̕�����

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)
#define RUN_PATTERN_WIDTH (1.0f / RUN_DIVIDE_X)
#define RUN_PATTERN_HEIGHT (1.0f / RUN_DIVIDE_Y)

#define PLAYER_DISP_X (SCREEN_WIDTH/2)	//�v���C���[�̕\�����WX
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)	//�v���C���[�̕\�����WY

#define SPEED (6.0f)				// �ړ��X�s�[�h

#define ANIMATION_SPEED	6			

#define DECREASE	200	// �󒆂Ń`���[�W�����Ă���Ƃ��̗������x (2 ������� 1/2 )
#define OVERHEAT_FRAME 60 // �e��X�����ő�l�̎��ɃI�[�o�[�q�[�g����܂ł̃t���[����
#define OVERHEAT_PENALTY_FRAME 120
#define SHADOW_MAX 600


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static int g_Sound_p_at1 = 0;
static int g_Sound_p_at2 = 0;
static int g_Sound_p_la = 0;
static int g_Sound_p_w = 0;



PLAYER::~PLAYER()
{

}
//=============================================================================
// ����������
//=============================================================================
void PLAYER::Init(void)
{
	m_Textureplayer = LoadTexture((char*)"data/TEXTURE/player.png");		//�v���C���[
	m_Texturereservoir = LoadTexture((char*)"data/TEXTURE/reservoir.png");	//�v���C���[�̗���
	m_Texturehp = LoadTexture((char*)"data/TEXTURE/zeni.png");				//HP
	m_Texturehpunder = LoadTexture((char*)"data/TEXTURE/zero.png");			//HP(��)
	m_Texturelive = LoadTexture((char*)"data/TEXTURE/live.png");
	m_Texturecrouching = LoadTexture((char*)"data/TEXTURE/crouching.png"); //���Ⴊ�ݏ��

	g_Sound_p_at1 = LoadSound((char*)"data/SE/P_At_01.wav");
	g_Sound_p_at2 = LoadSound((char*)"data/SE/P_At_02.wav");
	g_Sound_p_la = LoadSound((char*)"data/SE/P_landing.wav");
	g_Sound_p_w = LoadSound((char*)"data/SE/P_walk.wav");


	//----�f�[�^�̏�����----------------------------------------------------------

	m_pos = D3DXVECTOR2(100.0f, 0.0f);
	m_vel = D3DXVECTOR2(SPEED, SPEED);
	m_muki = 1;
	m_crouchingtime = 0.0f;
	m_animePtn = 0;
	m_animeReservoirPtn = 0;
	m_animeCounter = 0;
	m_movetime = 0.0f;
	m_height = 0.02f;
	m_gravity = 0.0f;
	m_hp = 5;
	m_live = 2;
	m_size = 256.0f;
	m_overheatframe = 0.0f;
	m_overheatflag = false;
	m_onGround = false;
	m_predict = false;
	m_crouching = false;
	m_slashFlag = 0;
	m_diagonalSlash = false;
	m_gopredictpos = true;
	m_walkSoundFlag = false;
	m_landingSoundFlag = false;
	m_AtSoundFlag = false;
	m_use = true;
	m_unrivaled = false;
	m_unrivaledtime = 0;


	
	//----------------------------------------------------------------------------

				
}

//=============================================================================
// �I������
//=============================================================================
void PLAYER::Uninit(void)
{
	
}

//=============================================================================
// �X�V����
//=============================================================================
void PLAYER::Update(void)
{
	if (GetKeyboardTrigger(DIK_K))
	{
		m_hp--;
	}
	if (m_use == true)
	{
		m_oldpos = m_pos;
		

		if (m_pos.y > SCREEN_HEIGHT + 500.0f)
		{
			m_hp = 0;
		}

		if (m_unrivaled == true)
		{
			m_unrivaledtime--;
			m_a -= 0.01f;
		}

		if (m_a < 0.5f)
		{
			m_a = 1.0f;
		}

		if (m_unrivaledtime == 0)
		{
			m_unrivaled = false;
			m_unrivaledtime = 300;
			m_a = 1.0f;
		}

		//�n�ʂɂ��Ȃ�������0.5�b���Ⴊ�ݎ��Ԃ�������
		if (m_onGround == false)
		{
			m_crouchingtime = 20.0f;
		}

		if (m_pos.y + m_predictpos.y > SCREEN_HEIGHT || m_pos.x + m_predictpos.x < 0)
		{
			m_gopredictpos = false;
		}


		//----�v���C���[�̈ړ�---------------------------------------------------------

			//�\���Ƃ��Ⴊ�݂��I���܂œ����Ȃ�
		if (m_predict == false && m_crouching == false && m_overheatflag == false)
		{

			if (GetKeyboardPress(DIK_A) || (GetThumbLeftX(0) < 0))			//A�����Ă�Ƃ�
			{
				/*if(m_onGround == true && m_predictpos.x == 0.0f)
				m_Effect->SetRun(D3DXVECTOR2(m_pos.x + 150.0f, m_pos.y + 128.0f));*/

				m_pos.x -= m_vel.x;											//�v���C���[�̈ʒu-�X�s�[�h
				m_muki = 0;	                                                //������

				if (m_walkSoundFlag == false)
				{
					PlaySound(g_Sound_p_w, 0);
					m_walkSoundFlag = true;
				}

				if (m_animeCounter > ANIMATION_SPEED)
				{
					//�A�j���[�V�����p�^�[����؂�ւ���
					m_animePtn++;											//�v���C���[�𓮂���
					//�Ō�̃A�j���[�V�����p�^�[����\�������烊�Z�b�g����
					if (m_animePtn >= 8)
						m_animePtn = 3;

					m_animeCounter = 0;
				}
			}
			else if (GetKeyboardPress(DIK_D) || (GetThumbLeftX(0) > 0)) //�E�ړ�
			{
				/*if (m_onGround == true && m_predictpos.x == 0.0f)
				m_Effect->SetRun(D3DXVECTOR2(m_pos.x,m_pos.y + 128.0f));*/

				m_pos.x += m_vel.x;
				m_muki = 1;

				if (m_walkSoundFlag == false)
				{
					PlaySound(g_Sound_p_w, 0);
					m_walkSoundFlag = true;
				}

				if (m_animeCounter > ANIMATION_SPEED)
				{
					//�A�j���[�V�����p�^�[����؂�ւ���
					m_animePtn++;
					//�Ō�̃A�j���[�V�����p�^�[����\�������烊�Z�b�g����
					if (m_animePtn >= 8)
						m_animePtn = 3;
					m_animeCounter = 0;


				}
			}
			else
			{
				m_Effect->ResetRun();
				m_animePtn = 1;
				m_walkSoundFlag = false;
				StopSound(g_Sound_p_w);
			}

			m_mukiOld = m_muki;
		}


		m_animeCounter++;


		//----�v���C���[���X�e�[�W�ɂ��Ȃ��̎��ɗ����鏈��---------------------------------

		if (m_onGround == false && m_predict == false)
		{
			//���񂾂�������ė�����
			m_height -= m_gravity;
			//�d�͉����x�̏���l�܂�
			if (m_gravity < 0.098f)
				m_gravity += 0.01f;

			m_pos.y -= m_height;
		}
		else if (m_onGround == false && m_skychage == true)
		{
			//���񂾂�������ė�����
			m_height -= m_gravity;
			//�d�͉����x�̏���l�܂�
			if (m_gravity < 5.0f)
				m_gravity += 0.0001f;

			m_pos.y -= m_height / DECREASE;
		}
		else {
			//�d�͉����x�̃��Z�b�g
			m_height = 0.02f;
			m_gravity = 0;
		}
		//----------------------------------------------------------------------------------

		if (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W))
		{
			m_Effect->SetCharge(m_pos);
			m_Effect->ResetRun();
			if (m_AtSoundFlag == false)
			{
				PlaySound(g_Sound_p_at1, 0);
				m_AtSoundFlag = true;
			}
			if (m_predict == false)
				m_muki = 2;
		}
		else if (GetKeyboardPress(DIK_D) && GetKeyboardPress(DIK_W))
		{
			m_Effect->SetCharge(m_pos);
			if (m_AtSoundFlag == false)
			{
				PlaySound(g_Sound_p_at1, 0);
				m_AtSoundFlag = true;
			}
			m_Effect->ResetRun();
			if (m_predict == false)
				m_muki = 3;
		}
		else
		{
			m_muki = m_mukiOld;
		}

		//----�v���C���[�̃`���[�W�ƍU��----------------------------------------------

		//���Z�b�g�ƍU��//���̓�A���łĂ鎞�Ԃ�0�b��������
		if (GetKeyboardRelease(DIK_W) && m_crouching == false && m_nextcontinuitytime == 0.0f ||	// �L�[�{�[�h����
			m_useRightStick == true && (GetThumbRightY(0) == 0.0f) && (GetThumbRightX(0) == 0.0f) && m_crouching == false && m_nextcontinuitytime == 0.0f)	// PAD����
		{
			if (m_overheatflag == true) // �I�[�o�[�q�[�g������ɃX�e�B�b�N��߂�����
			{
				m_useRightStick = false;
			}
			else
			{
				m_overheatinit = true;
				m_skychage = false;

				//�\�����Q����G�Ƃ��Ԃ��Ă��Ȃ����
				if (m_gopredictpos == true)
				{
					//�A���̃J�E���g����ȏォ��b�ȓ��ɂ�����x�A��������
					if (m_continuity == 1 && m_continuitytime > 0.0f)
					{
						m_continuity += 1;
					}
					else
					{
						m_continuitytime = 60.0f;
						m_continuity += 1;
					}
					//�����̃��[�V����
					m_animeReservoirPtn = 4;

					PlaySound(g_Sound_p_at2, 0);
					//�u�Ԉړ����̃G�t�F�N�g���Z�b�g
					if (m_predictpos > 0)
					{
						m_Effect->SetTeleportation(D3DXVECTOR2(m_pos.x, m_pos.y + 80.0f));
					}
					//�\����ɔ��
					m_pos += m_predictpos;
					//�U�����铁���Z�b�g����
					m_slash->SetSlash(m_pos, m_muki);

					//�`���[�W�G�t�F�N�g�����Z�b�g
					m_Effect->SetFlag(1); // �`���[�W����߂�
					m_AtSoundFlag = false;

					m_useRightStick = false;
				}

				//�A�������ȏ�ɂȂ�����
				if (m_continuity == 2)
				{
					//���̓�A���łĂ�܂�2�b�Ԃ�����
					m_nextcontinuitytime = 120.0f;
					//�A���̃J�E���g�����Z�b�g����
					m_continuity = 0;
				}


				if (m_diagonalSlash == true)
				{
					m_onGround = false;
				}

				m_diagonalSlash = false;

				m_predictpos = D3DXVECTOR2(0.0f, 0.0f);


			}

			m_overheatframe = 0.0f;
		}

		//�A�����Ԃ�1�b�̃J�E���g�_�E��
		if (m_continuitytime > 0.0f)
			m_continuitytime -= 1.0f;

		//���̓�A���łĂ�܂ł̃J�E���g�_�E��
		if (m_nextcontinuitytime > 0.0f)
			m_nextcontinuitytime -= 1.0f;

		//�n�ʂƓ������Ă��Ă����Ⴊ�ݎ���0.5�b�̃J�E���g�_�E��
		if (m_onGround == true && m_crouchingtime > 0.0f)
		{
			m_Effect->SetFlag(2); // �I�[�o�[�q�[�g�͂Q
			m_crouchingtime -= 1.0f;
			//���Ⴊ��ł���
			if (m_landingSoundFlag == false)
			{
				PlaySound(g_Sound_p_la, 0);
				m_landingSoundFlag = true;
			}
			m_crouching = true;
		}
		else
		{
			//���Ⴊ��ł��Ȃ�
			m_crouching = false;
			m_landingSoundFlag = false;
		}


		//�\������ϓ�
		if (m_overheatflag == false &&
			((GetKeyboardPress(DIK_W) && m_crouching == false && m_nextcontinuitytime == 0.0f) ||	// �L�[�{�[�h����
			(GetThumbRightY(0) != 0) && m_crouching == false && m_nextcontinuitytime == 0.0f))	// PAD����
		{

			if (m_overheatinit == true)
			{
				m_overheatframe = 0;

				m_overheatinit = false;
			}

			if (GetThumbRightY(0) != 0 && m_useRightStick == false)
			{

				m_useRightStick = true;
				m_playerY = 0;
			}

			m_movetime = 200.0f;
			m_predict = true;
			m_skychage = true;

			if (m_predictpos.x <= SHADOW_MAX && m_predictpos.x >= -600.0f && m_predictpos.y >= -SHADOW_MAX)
			{
				if (m_useRightStick == false)
				{
					switch (m_muki)
					{
					case 0:
						m_animeReservoirPtn = 1;
						m_predictpos.x -= 15.0f;
						break;
					case 1:
						m_animeReservoirPtn = 1;
						m_predictpos.x += 15.0f;
						break;
					case 2:
						m_animeReservoirPtn = 0;
						m_predictpos.x -= 15.0f;
						m_predictpos.y -= 15.0f;
						m_diagonalSlash = true;
						break;
					case 3:
						m_animeReservoirPtn = 0;
						m_predictpos.x += 15.0f;
						m_predictpos.y -= 15.0f;
						m_diagonalSlash = true;
						break;
					}
				}

				// PAD�p

				if (m_useRightStick == true)
				{
					m_Effect->SetCharge(m_pos);
					m_Effect->ResetRun();
					// �e��X���ő�l�ł͂Ȃ���
					if (m_muki == 0)
					{
						m_predictpos.x -= 15.0f; // ��
					}
					else if (m_muki == 1)
					{
						m_predictpos.x += 15.0f; // �E
					}
				}
			}
			else // �e��X���W��MAX�̎�
			{
				if (m_overheatframe >= OVERHEAT_FRAME)
				{
					m_Effect->SetFlag(2);
					m_overheatflag = true;
				}
				m_overheatframe++;
			}
			// �e��Y���ő�l�ł͂Ȃ���
			m_playerY -= GetThumbRightY(0) * 15.0f;
			// �`���[�W����UV�l��ݒ�
			switch (m_muki)
			{
			case 0:
				if (GetThumbRightY(0) >= 0.5f)
				{
					m_animeReservoirPtn = 0;

					break;
				}
				else if (GetThumbRightY(0) < 0.5f && GetThumbRightY(0) > -0.5f)
				{
					m_animeReservoirPtn = 1;

					break;
				}
				else
				{
					m_animeReservoirPtn = 3;

					break;
				}

			case 1:
				if (GetThumbRightY(0) >= 0.5f)
				{
					m_animeReservoirPtn = 0;

					break;
				}
				else if (GetThumbRightY(0) < 0.5f && GetThumbRightY(0) > -0.5f)
				{
					m_animeReservoirPtn = 1;

					break;
				}
				else
				{
					m_animeReservoirPtn = 3;

					break;
				}
			}

			if (m_playerY <= SHADOW_MAX && m_playerY >= -SHADOW_MAX)
			{
				m_predictpos.y = m_playerY;
			}
		}

		if (m_overheatflag == true)
		{
			if (m_penaltyframe >= OVERHEAT_PENALTY_FRAME)
			{
				m_Effect->SetFlag(1);
				m_overheatflag = false;
				m_penaltyframe = 0;
				m_predictpos = D3DXVECTOR2(0.0f, 0.0f);
			}
			else
			{
				m_penaltyframe++;
			}
		}

		else if (m_overheatflag == true)
		{
			m_predictpos = D3DXVECTOR2(0.0f, 0.0f);
		}

		if (m_movetime == 0.0f)
		{
			m_predict = false;
		}
		else
		{
			m_movetime -= 10.0f;
		}
		//----------------------------------------------------------------------------


		if (m_hp < 1)
		{
			m_hp = 5;
			m_live -= 1;
			if (m_pos.x > 0 && m_pos.x < SCREEN_WIDTH)
			{
				m_pos = D3DXVECTOR2(100.0f, 0.0f);
			}
			if (m_pos.x > SCREEN_WIDTH && m_pos.x < SCREEN_WIDTH * 2)
			{
				m_pos = D3DXVECTOR2(SCREEN_WIDTH + 100.0f, 0.0f);
			}
			if (m_pos.x > SCREEN_WIDTH * 2 && m_pos.x < SCREEN_WIDTH * 3)
			{
				m_pos = D3DXVECTOR2(SCREEN_WIDTH * 2 + 100.0f, 0.0f);
			}
			if (m_pos.x > SCREEN_WIDTH * 3 && m_pos.x < SCREEN_WIDTH * 4)
			{
				m_pos = D3DXVECTOR2(SCREEN_WIDTH * 3 + 100.0f, 0.0f);
			}
		}

		if (m_live < 1)
		{
			m_use = false;
		}

		if (m_pos.x < 49.0f)
			m_pos = m_oldpos;
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void PLAYER::Draw(void)
{
//----�v���C���[��HP�̕`��--------------------------------------------------
	// HP(���@��)
	for (int i = 0; i < 5; i++)
	{
		DrawSpriteLeftTop(m_Texturehpunder,
			0.0f + (102.0f * i),
			0.0f,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}


// HP(��@�t��)
	for (int i = 0; i < m_hp; i++)
	{
		DrawSpriteLeftTop(m_Texturehp,
			0.0f + (102.0f * i),
			0.0f,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}

	for (int i = 0; i < m_live; i++)
	{
		DrawSpriteLeftTop(m_Texturelive,
			0.0f + (102.0f * i),
			102.0f,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}

//----------------------------------------------------------------------------
	
	if (m_use == true)
	{

		//----�v���C���[�̕`��--------------------------------------------------------
			//�\�������Ⴊ��ł����Ȃ�������
		if (m_predict == false && m_crouching == false && m_overheatflag == false)
		{
			DrawSpriteColor(m_Textureplayer,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y,
				192.0f, m_size,
				m_AnimeTable[m_animePtn],
				m_MukiTable[m_muki],
				RUN_PATTERN_WIDTH,
				RUN_PATTERN_HEIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_a));
		}

		//�n�ʂƓ������Ă��Ă����Ⴊ�ݎ��ԓ���������
		if (m_onGround == true && m_crouchingtime > 0.0f || m_overheatflag == true)
		{
			DrawSpriteColor(m_Texturecrouching,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y + 30.0f,
				192.0f, m_size,
				0.333f,
				m_MukiTable[m_muki],
				PATTERN_WIDTH,
				PATTERN_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, m_a));
		}

		//�v���C���[�̗\���s���̕`��
		if (m_predict == true && m_overheatflag == false)
		{

			DrawSpriteColor(m_Texturereservoir,
				m_base->x + m_pos.x,
				m_base->y + m_pos.y,
				192.0f, m_size,
				m_AnimeReservoirTable[m_animeReservoirPtn],
				m_MukiTable[m_muki],
				0.2f,
				0.5f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, m_a));

			DrawSpriteColor(m_Texturereservoir,
				m_base->x + m_pos.x + m_predictpos.x,
				m_base->y + m_pos.y + m_predictpos.y,
				192.0f, m_size,
				m_AnimeReservoirTable[m_animeReservoirPtn],
				m_MukiTable[m_muki],
				0.2f,
				0.5f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8));
		}

		//----------------------------------------------------------------------------
	}
}

D3DXVECTOR2 * PLAYER::GetPlayerPos(void)
{
	return &m_pos;
}

D3DXVECTOR2 * PLAYER::GetOldPlayerPos(void)
{
	return &m_oldpos;
}

bool * PLAYER::GetOnGround(void)
{
	return &m_onGround;
}

bool * PLAYER::GetGoPredictPos(void)
{
	return &m_gopredictpos;
}










