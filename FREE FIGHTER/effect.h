#pragma once
//=============================================================================
//
// �e���� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


// �o���b�g�\����
struct EFFECT
{
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:�g���Ă���  false:���g�p
	D3DXVECTOR3				pos;	// �o���b�g�̍��W
	D3DXVECTOR3				dir;	// �o���b�g�̈ړ�����
	float					frame;	// �t���[����

	float					uw, vh;
	int						u, v;

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos);

