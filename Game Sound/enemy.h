#pragma once

class Audio;
#include "gameObject.h"

enum ENEMY_STATE
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_MOVE,
	ENEMY_STATE_CHASE
};

class Enemy : public GameObject
{
private:
	AnimationModel* m_Model{};
	
	Audio* m_FootStep{};
	float m_SoundTime{};

	int m_Time{};
	float m_BlendRate{};
	std::string m_AnimationName{};
	std::string m_NextAnimationName{};

	int m_NextStateTime;

	ENEMY_STATE m_State = ENEMY_STATE_IDLE;
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateIdel();
	void UpdateMove();
	void UpdateChase();

	ENEMY_STATE GetState() const { return m_State; }
};