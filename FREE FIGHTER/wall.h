//=============================================================================
//
// �n�ʏ��� [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WALL_NUM 4
#define ALL_WALL_NUM 10

struct WALL
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		dir;		// �ړ�����
	int				color;

	bool			use;		// �\���t���O

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall (void);
void DrawWall(void);

WALL *GetWall(int i);
