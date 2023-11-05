#pragma once
#include "DxLib.h"

//マップの列(横)の数
enum MapInfo
{
	NONE,
	BLOCK,      //1
	BLOCK2,     //2
	BLOCK3,     //3
	BLOCK4,     //4
	BLOCK5,     //5
	BLOCK6,     //6
	BLOCK7,     //7
	BLOCK8,     //8
	BLOCK9,     //9
	BLOCK10,    //10
	BLOCK11    //11
};

class Map
{
public:
	Map();
	//ステージ
	void Tutorial();
	//関数
	int RightHit(int posX, int posY, int posRadius);
	int LeftHit(int posX, int posY, int posRadius);
	int UpHit(int posX, int posY, int posRadius);
	int DownHit(int posX, int posY, int posRadius);
	int Hit(int posX, int posY, int posRadius);
	int Clear(int posX, int posY, int posRadius);
	int Size(int posX, int posY, int posRadius);
	int Portion(int posX, int posY, int posRadius);
	int Frag(int posX, int posY, int posRadius);
	void Scroll(int posX);
	void Initialization();

	//読み込み・書き込み
	int GetScroll();
	int Getblocksize();
	int GetLeft(int posX, int posRadius);
	int GetRight(int posX, int posRadius);
	int GetDown(int posY, int posRadius);
	int GetUp(int posY, int posRadius);

private:
	int scrollX;
	int blockSize;

	
	int haikeiX;
	int haikeiY;

	int graphHandle[12];
	int graphHandle2[13];
	int graphHandle3[1];
	int tutorial[20][377];

};
