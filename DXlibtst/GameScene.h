#pragma once
#include "Player.h"
#include "Map.h"
#include "Change.h"

class GameScene
{
public:
	GameScene();

	void Update();
	void Initialization();
	void Draw();

	//“Ç‚İ‚İE‘‚«‚İ
	int GetCount();
	int GetEndFlag();

private:
	Player* player;
	Map* map;
	Change* change;
	int count;
	int endFlag;
};
