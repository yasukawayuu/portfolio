//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "bullet.h"
#include "wall.h"
#include "shadow.h"
#include "score.h"
#include "wall.h"
#include "player.h"
#include "color.h"
#include "effect.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


void Collision_Bullet_Wall(void);
void Collision_Player_Wall(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	Collision_Bullet_Wall();

	Collision_Player_Wall();
}


void Collision_Bullet_Wall(void)
{
	BULLET *bullet = GetBullet();	// �e�̃|�C���^�[��������

	//�g�p����Ă��Ȃ��e�͉������Ȃ�
	if (bullet->use)
	{
		for (int i = 0; i < ALL_WALL_NUM; i++)
		{
			WALL  *wall = GetWall(i);		// �G�l�~�[�̃|�C���^�[��������

			for (int n = 0; n < WALL_NUM; n++)
			{
				//�g�p����Ă��Ȃ��G�͉������Ȃ�
				if (wall[n].use == false)
					continue;

				if (CollisionBB(bullet->pos, wall[n].pos, bullet->size, wall[n].size))
				{
					if (wall[n].color == bullet->color)
					{
						// �_�������Z����
						AddScore(10);
						//�@�ǂ�����
						wall[n].use = false;
						bullet->color = frand() * 4;
					}
					
					// �e������
					bullet->use = false;
					ReleaseShadow(bullet->shadow);

				
				}
			}
		}
	}
}

void Collision_Player_Wall(void)
{
	PLAYER *player = GetPlayer();	// �e�̃|�C���^�[��������

	for (int i = 0; i < ALL_WALL_NUM; i++)
	{
		WALL  *wall = GetWall(i);		// �G�l�~�[�̃|�C���^�[��������

		for (int n = 0; n < WALL_NUM; n++)
		{
			//�g�p����Ă��Ȃ��G�͉������Ȃ�
			if (wall[n].use == false)
				continue;

			if (CollisionBB(player->pos, wall[n].pos, player->size, wall[n].size))
			{
				wall[n].use = false;
				// �v���C���[������
				player->use = false;
				SetEffect(player->pos);
				ReleaseShadow(player->shadow);

				SceneTransition(SCENE_RESULT);
			}
		}
	}
}

//=============================================================================
// ���E��(BB)�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	float Axmax = pos1.x + (size1.x / 2);
	float Axmin = pos1.x - (size1.x / 2);
	float Aymax = pos1.y + (size1.y / 2);
	float Aymin = pos1.y - (size1.y / 2);
	float Azmax = pos1.z + (size1.z / 2);
	float Azmin = pos1.z - (size1.z / 2);

	float Bxmax = pos2.x + (size2.x / 2);
	float Bxmin = pos2.x - (size2.x / 2);
	float Bymax = pos2.y + (size2.y / 2);
	float Bymin = pos2.y - (size2.y / 2);
	float Bzmax = pos2.z + (size2.z / 2);
	float Bzmin = pos2.z - (size2.z / 2);

	if ((Axmax > Bxmin) && (Axmin < Bxmax))
	{
		if ((Aymin < Bymax) && (Aymax > Bymin))
		{
			if ((Azmax > Bzmin) && (Azmin < Bzmax))
			{
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// ���E��(BS)�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR3 dist = pos2 - pos1;

	//������x�N�g���̑傫�����v�Z����
//	float length = D3DXVec3Length(&dist);

	//Sq�����Ă���֐��͕������̌v�Z�����Ȃ��o�[�W����
	float length = D3DXVec3LengthSq(&dist);

	//1��2�̔��a�𑫂�
//	float size = size1 + size2;

	//�������̌v�Z�����Ȃ��̂Ŕ��肷�鑊��̕����悷��
	float size = (size1 + size2) * (size1 + size2);

	//���a�̕����傫���Ƃ��A��̉~�͏d�Ȃ��Ă���
	if (length < size)
		return true;

	return false;
}
