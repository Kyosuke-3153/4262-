#pragma once
#include "DxLib.h"
#include "Map.h"
#include "Change.h"

class Player
{
public:
	Player(Map* map);

	//ä÷êî
	void Move();
	void Jump();
	void GraphicMove();

	void Update();
	void Initialization();

	void Draw();

	//ì«Ç›çûÇ›ÅEèëÇ´çûÇ›
	void SetPosX(double playerX);
	void SetPosY(int playerY);
	double GetPosX();
	int GetPosY();
	int GetRadius();
	int GetCount();

private:
	Map* map;

	double playerX;
	int playerY;
	int playerRadius;
	int playerAliveFlag;
	int playerSpeed;
	int playerTimer;
	int playerMoveFlag;
	int playerNumber;
	int jumpFlag;
	int jumpPower;
	int jumpNot;
	int jumpCount;
	int count;
	int PlayerSizeFlag;
	int zCount;

	int portionX;
	int portionY;
	int portion;

	int graphHandleP[1];
	int graphHandle[1];
	
	int graphHandle2[4];
	int graphHandle3[8];
	int graphHandle4[4];

	int graphHandleS[8];
	int graphHandle2S[4];
	int graphHandle3S[8];
	int graphHandle4S[4];
	char keys[256];
	char oldkeys[256];
};
