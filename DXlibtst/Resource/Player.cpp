#include "Player.h"

Player::Player(Map* map)
{
//初期設定
	
		playerX = 300.0f;
		playerY = 818;
		playerRadius = 46;
		playerAliveFlag = 1;
		playerSpeed = 12;
		PlayerSizeFlag = 1;
		playerTimer = 0;
		playerMoveFlag = 0;
		playerNumber = 0;
		jumpFlag = 0;
		jumpPower = 0;
		count = 0;
		jumpNot = 0;
		jumpCount = 0;

		portionX = 1000;
		portionY = 600;
	
	// 最新のキーボード情報用
	keys[255] = { 0 };
	// 1ループ(フレーム)前のキーボード情報
	oldkeys[255] = { 0 };

	this->map = map;
}

void Player::Move()
{
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	GetHitKeyStateAll(keys);

	if (keys[KEY_INPUT_RIGHT] == 0 && oldkeys[KEY_INPUT_RIGHT] == 1)
	{
		playerMoveFlag = 0;
	}
	else if (keys[KEY_INPUT_RIGHT] == 1 && map->RightHit((int)playerX, playerY, playerRadius))
	{
		playerX += playerSpeed;
		if (playerMoveFlag == 1 || playerMoveFlag == 5)
		{
			playerMoveFlag = 2;
		}
	}

	if (keys[KEY_INPUT_LEFT] == 0 && oldkeys[KEY_INPUT_LEFT] == 1)
	{
		playerMoveFlag = 4;
	}
	else if (keys[KEY_INPUT_LEFT] == 1 && map->LeftHit((int)playerX, playerY, playerRadius))
	{
		playerX -= playerSpeed;
		if (playerMoveFlag == 1 || playerMoveFlag == 5)
		{
			playerMoveFlag = 6;
		}
	}

	if (!map->RightHit((int)playerX, playerY, playerRadius))
	{
		playerX = map->GetRight((int)playerX, playerRadius) - playerRadius;
	}
	else if (!map->LeftHit((int)playerX, playerY, playerRadius))
	{
		playerX = map->GetLeft((int)playerX, playerRadius) + map->Getblocksize() + playerRadius;
	}


	if (PlayerSizeFlag == 1 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 &&
		jumpFlag == 0 && map->DownHit((int)playerX, playerY, playerRadius) && jumpNot == 0 || PlayerSizeFlag == 1 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 &&jumpFlag == 0 && jumpNot == 1 && zCount == 0)
	{
		jumpFlag = 1;
		jumpPower = -30;

		jumpNot = 1;
	}



	if (PlayerSizeFlag == 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 &&
		jumpFlag == 0 && map->DownHit((int)playerX, playerY, playerRadius) && jumpNot == 0||
		PlayerSizeFlag == 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && jumpFlag == 0 && jumpNot == 1 && zCount == 0)
	{
		jumpFlag = 1;
		jumpPower = -40;
		jumpNot = 1;
	}

	if (PlayerSizeFlag == 0&& keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0)
	{
		PlayerSizeFlag = 1;//通常
	}
	if (map->Portion((int)playerX, playerY, playerRadius))
	{
		if (PlayerSizeFlag == 1 && keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0)
		{
			PlayerSizeFlag = 0;//ミニ
		}
	}
	Jump();
}

void Player::Jump()
{

	if (jumpFlag == 1 && map->UpHit((int)playerX, playerY, playerRadius))
	{
		playerY += jumpPower;
		jumpPower += 2;
	}

	if (jumpFlag == 0 && !map->DownHit((int)playerX, playerY, playerRadius))
	{
		playerY += jumpPower;
		jumpPower += 2;
		jumpNot = 1;
	}
	if (!map->UpHit((int)playerX, playerY, playerRadius))
	{
		playerY = map->GetUp(playerY, playerRadius) + map->Getblocksize() + playerRadius;
		jumpFlag = 0;
	}

	if (jumpFlag == 0 && map->DownHit((int)playerX, playerY, playerRadius))
	{
		playerY = map->GetDown(playerY, playerRadius) - playerRadius;
		jumpFlag = 0;
		jumpPower = 0;
	}
	/*
	if (jumpNot == 1)
	{
		jumpCount = 1;
		if(jumpCount ==1)
		{
			jumpNot = 0;
			jumpCount = 0;
		}
	}
	*/
	if (playerY - playerRadius < 0)
	{
		playerY = 0 + playerRadius;
	}

	if (jumpFlag == 1 && map->DownHit((int)playerX, playerY, playerRadius))
	{
		playerY = map->GetDown(playerY, playerRadius) - playerRadius - 4;
		jumpFlag = 0;
		jumpPower = 0;
	}
}

void Player::GraphicMove()
{
	playerTimer++;

	if (playerMoveFlag == 0 || playerMoveFlag == 2 || playerMoveFlag == 4 || playerMoveFlag == 6)
	{
		playerMoveFlag++;
		playerNumber = 0;
	}
	else if (playerMoveFlag == 1 && playerTimer >= 10)
	{
		playerNumber++;
		if (playerNumber > 7)
		{
			playerNumber = 0;
		}
		playerTimer = 0;
	}
	else if (playerMoveFlag == 3 && playerTimer >= 5)
	{
		playerNumber++;
		if (playerNumber > 3)
		{
			playerNumber = 0;
		}
		playerTimer = 0;
	}
	else if (playerMoveFlag == 5 && playerTimer >= 10)
	{
		playerNumber++;
		if (playerNumber > 7)
		{
			
			playerNumber = 0;
		}
		playerTimer = 0;
	}
	else if (playerMoveFlag == 7 && playerTimer >= 5)
	{
		playerNumber++;
		if (playerNumber > 3)
		{
			playerNumber = 0;
		}
		playerTimer = 0;
	}
}

void Player::Update()
{
	Move();
	GraphicMove();
	if (map->Hit((int)playerX, playerY, playerRadius) || playerY - playerRadius >= 960)
	{
		playerAliveFlag = 0;
		count = 1;
	}
	if (map->Clear((int)playerX, playerY, playerRadius))
	{
		count = 2;
	}

	map->Scroll(playerX);
}

void Player::Initialization()
{

		playerX = 300.0f;
		playerY = 818;
		playerRadius = 46;
		playerAliveFlag = 1;
		playerSpeed = 12;
		playerTimer = 0;
		playerMoveFlag = 0;
		playerNumber = 0;
		PlayerSizeFlag = 1;
		jumpFlag = 0;
		jumpPower = 0;
		count = 0;
		jumpNot = 0;
		jumpCount = 0;

		portionX = 1000;
		portionY = 600;
	
	}

void Player::Draw()
{
	//描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);



	if (PlayerSizeFlag == 1)
	{
		LoadDivGraph
		(
			"Resource/chraMove.png",  //読み込みたい画像ファイルの名前
			4,             //グラフィックの総分割総数
			4,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandle2    //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);
		LoadDivGraph
		(
			"Resource/chraWaitMove2.png",  //読み込みたい画像ファイルの名前
			8,             //グラフィックの総分割総数
			8,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandle3    //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);
		LoadDivGraph
		(
			"Resource/chraWaitMove.png",  //読み込みたい画像ファイルの名前
			8,             //グラフィックの総分割総数
			8,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandle    //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);
		LoadDivGraph
		(
			"Resource/chraMove2.png",  //読み込みたい画像ファイルの名前
			4,             //グラフィックの総分割総数
			4,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandle4    //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);

		for (int i = 0; i < 1; i++)
		{
			DrawGraph((portionX * i) + map->GetScroll(), portionY , graphHandleP[i], TRUE);
		}
		for (int i = 0; i < 1; i++)
		{
	//		graphHandleP[i] = LoadGraph("portion.png");
		}
	}
	
	if (playerAliveFlag == 1 && playerMoveFlag == 1 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 3 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle2[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 5 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle3[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 7 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle4[playerNumber], TRUE);
	}
	if (PlayerSizeFlag == 0)
	{
		LoadDivGraph
		(
			"Resource/chraMoveS.png",  //読み込みたい画像ファイルの名前
			4,             //グラフィックの総分割総数
			4,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandle2S    //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);
		LoadDivGraph
		(
			"Resource/chraWaitMove2S.png",  //読み込みたい画像ファイルの名前
			8,             //グラフィックの総分割総数
			8,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandle3S   //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);
		LoadDivGraph
		(
			"Resource/chraWaitMoveS.png",  //読み込みたい画像ファイルの名前
			8,             //グラフィックの総分割総数
			8,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandleS    //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);
		LoadDivGraph
		(
			"Resource/chraMove2S.png",  //読み込みたい画像ファイルの名前
			4,             //グラフィックの総分割総数
			4,             //グラフィックの横向きに対する分割数
			1,             //グラフィックの縦向きに対する分割数
			93,           //グラフィックサイズ
			100,            //グラフィックサイズ
			graphHandle4S    //分割読み込みして得たグラフィックハンドルを保存するint型配列
		);
	}


	if (playerAliveFlag == 1 && playerMoveFlag == 1&& PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandleS[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 3 && PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle2S[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 5 && PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle3S[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 7 && PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle4S[playerNumber], TRUE);
	}


}

void Player::SetPosX(double playerX)
{
	this->playerX = playerX;
}

void Player::SetPosY(int playerY)
{
	this->playerY = playerY;
}

double Player::GetPosX()
{
	return playerX;
}

int Player::GetPosY()
{
	return playerY;
}

int Player::GetRadius()
{
	return playerRadius;
}

int Player::GetCount()
{
	return count;
}