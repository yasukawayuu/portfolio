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
	std::list<GameObject*> m_GameObject[3];//レイヤー有りSTLのリスト構造

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

			m_GameObject[i].clear();//リスト構造の削除
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

	template <typename T>//テンプレート関数 型をかえう
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <typename T>//テンプレート関数 型をかえう
	T* GetGameObject()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject *object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//型を調べる（RTTI動的型情報）
				{
					return (T*)object;
				}
			}
		}
		return nullptr;
	}



	template <typename T>//テンプレート関数 型をかえう
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;//STLの配列
		for (int i = 0; i < 3; i++)
		{
			for (GameObject *object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//型を調べる（RTTI動的型情報）
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

//Spriteコンポーネントを完成させる　〇

//できたら・・・
//・ゲームオブジェクトを空のオブジェクトにしとく
//・Planeコンポーネント
//・Modelコンポーネント
//・完全コンポーネント化（Camera等もコンポーネント化）

//・Renderer、Manager→シングルトン　〇
//・タイトル画面作成		〇
//・モデル、フィールド作成

//描画ソート
//モデル→フライフェイト　〇

//プレイヤーめり込む

//・サウンドフェード 〇
//atan2		〇