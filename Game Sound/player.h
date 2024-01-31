#pragma once

class Audio;
class AnimationModel;

#include "gameObject.h"
#include <string>

enum PLAYER_STATE
{
	PLAYER_STATE_GROUND,
	PLAYER_STATE_JUMP
};

class Player : public GameObject
{
private:
	PLAYER_STATE m_PlayerState = PLAYER_STATE_GROUND;
	AnimationModel* m_Model{};

	Audio* m_Serif{};
	Audio* m_HeartBeat{};
	
	float m_SoundTime{};

	int m_Time{};
	float m_BlendRate{};
	std::string m_AnimationName{};
	std::string m_NextAnimationName{};
	bool m_IsGround{};

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateGround();
	void UpdateJump();
};