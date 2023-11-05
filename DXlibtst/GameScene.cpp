#include "GameScene.h"

GameScene::GameScene()
{
	map = new Map;
	player = new Player(map);
	change = new Change(255,2);
	count = 0;
	endFlag = 0;
}

void GameScene::Update()
{
	change->SceneIn();
	change->SceneOut();
	player->Update();

	if (player->GetCount() == 1 && count == 0)
	{
		change->SetCount(1);
		count = 1;
	}
	else if (player->GetCount() == 2 && count == 0)
	{
		change->SetCount(1);
		count = 2;
	}

	if (change->GetCount() == 2 && count == 1)
	{
		endFlag = 1;
	}
	else if (change->GetCount() == 2 && count == 2)
	{
		endFlag = 2;
	}
}

void GameScene::Initialization()
{
	change = new Change(255, 2);
	count = 0;
	endFlag = 0;
	player->Initialization();
	map->Initialization();
}

void GameScene::Draw()
{
	map->Tutorial();
	player->Draw();
	change->Draw();
}

int GameScene::GetCount()
{
	return count;
}

int GameScene::GetEndFlag()
{
	return endFlag;
}