
#include "main.h"
#include "player.h"
#include "enemymanager.h"
#include "camera.h"
#include "slash.h"
#include "collision.h"
#include "stagemanager.h"
#include "obstacle.h"
#include "effect.h"

class GAME
{
private:
	PLAYER m_Player;
	ENEMYMANAGER m_Enemy;
	CAMERA m_Camera;
	SLASH  m_Slash;
	COLLISION m_Collision;
	STAGEMANAGER m_Stage;
	OBSTACLE m_Obstacle;
	EFFECT m_Effect;
	GAMEOVER m_gameover;
public:
	GAME() : m_Enemy(&m_Stage,m_Player.GetPlayerPos(), m_Camera.GetBase(), &m_Effect,m_Player.GetPlayerHp(),m_Player.GetUnrivaled())
			,m_Player(m_Camera.GetBase(), &m_Slash,&m_Effect)
		    ,m_Camera(m_Player.GetPlayerPos())
		    ,m_Slash(m_Camera.GetBase(),&m_Effect)
		    ,m_Collision(&m_Stage,&m_Player,&m_Enemy,&m_Slash)
		    ,m_Stage(m_Player.GetPlayerPos(),m_Camera.GetBase(),m_Enemy.GetKyuubi(),m_Enemy.GetTengu(),m_Player.GetPlayerHp(), m_Player.GetPlayerLive(),m_Player.GetOnGround())
		    ,m_Obstacle(m_Camera.GetBase())
		    ,m_Effect(m_Camera.GetBase()){}
	~GAME();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReChallenge(void);
};