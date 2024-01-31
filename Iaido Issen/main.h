/*==============================================================================

   �e�N�X�`���̕`�� [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"
#include "texture.h"
#include "sprite.h"
#include "renderer.h"
#include "inputx.h"

#pragma warning(pop)


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "xinput.lib")


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)				// �E�C���h�E�̍���

enum SCENE
{
	SCENE_NONE,		// �V�[���ݒ�Ȃ�
	SCENE_TITLE,	//�@�^�C�g��
	SCENE_GAME,		// �Q�[���{��
	SCENE_RESULT,

	SCENE_NUM,		// �I�[�R�[�h
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetScene(SCENE nextScene);
float frand(void);