#pragma once

#include "gameObject.h"
#include "audioManager.h"
#include "modelManager.h"
#include <list>
#include <typeinfo>
#include <vector>

class Scene
{
protected:
	std::list<GameObject*> m_GameObject[3];//���C���[�L��STL�̃��X�g�\��

public:
	virtual void Init(){}

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (auto *gameObject : m_GameObject[i])
			{
				gameObject->Uninit();
				delete gameObject;
			}

			m_GameObject[i].clear();//���X�g�\���̍폜
		}

		AudioManager::GetInstance()->Uninit();
		ModelManager::GetInstance()->Unload();
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (auto *gameObject : m_GameObject[i])
			{
				gameObject->Update();
			}

			m_GameObject[i].remove_if([](GameObject *object) {return object->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			for (auto *gameObject : m_GameObject[i])
			{
				gameObject->Draw();
			}
		}
		

	}

	template <typename T>//�e���v���[�g�֐� �^��������
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <typename T>//�e���v���[�g�֐� �^��������
	T* GetGameObject()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject *object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�iRTTI���I�^���j
				{
					return (T*)object;
				}
			}
		}
		return nullptr;
	}



	template <typename T>//�e���v���[�g�֐� �^��������
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;//STL�̔z��
		for (int i = 0; i < 3; i++)
		{
			for (GameObject *object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�iRTTI���I�^���j
				{
					objects.push_back((T*)object);
				}
			}
		}

		return objects;
	}


	std::list<GameObject*> GetGameObejctList(int i)
	{
		return m_GameObject[i];
	}
};

//Sprite�R���|�[�l���g������������@�Z

//�ł�����E�E�E
//�E�Q�[���I�u�W�F�N�g����̃I�u�W�F�N�g�ɂ��Ƃ�
//�EPlane�R���|�[�l���g
//�EModel�R���|�[�l���g
//�E���S�R���|�[�l���g���iCamera�����R���|�[�l���g���j

//�ERenderer�AManager���V���O���g���@�Z
//�E�^�C�g����ʍ쐬		�Z
//�E���f���A�t�B�[���h�쐬

//�`��\�[�g
//���f�����t���C�t�F�C�g�@�Z

//�v���C���[�߂荞��

//�E�T�E���h�t�F�[�h �Z
//atan2		�Z