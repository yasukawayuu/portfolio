#pragma once
#include "main.h"
#include "game.h"

class RESET
{
private:
	GAME *m_game;
public:
	RESET(GAME *game) :m_game(game){};
};