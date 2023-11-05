#include "Map.h"

Map::Map()
{
	scrollX = 0;
	blockSize = 48;
	haikeiX = 1400;
	haikeiY = 0;
	FILE* fp;
	fopen_s(&fp, "Resource/01.csv", "r");
	if (fp != NULL)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 377; j++)
			{
				fscanf_s(fp, "%d,", &tutorial[i][j]);
			}
		}
		fclose(fp);
	}

	LoadDivGraph
	(
		"Resource/block.png",  //読み込みたい画像ファイルの名前
		10,             //グラフィックの総分割総数
		3,             //グラフィックの横向きに対する分割数
		4,             //グラフィックの縦向きに対する分割数
		48,            //グラフィックサイズ
		48,            //グラフィックサイズ
		graphHandle    //分割読み込みして得たグラフィックハンドルを保存するint型配列
	);

	for (int i = 0; i < 13; i++)
	{
		graphHandle2[i] = LoadGraph("Resource/Yasiki.png");
	}


}

void Map::Tutorial()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < 13; i++)
	{
		DrawGraph((haikeiX * i) - scrollX, haikeiY, graphHandle2[i], TRUE);
	}
	

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 377; x++)
		{
			if (tutorial[y][x] == BLOCK)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[0], TRUE);
			}
			if (tutorial[y][x] == BLOCK2)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[1], TRUE);
			}
			if (tutorial[y][x] == BLOCK3)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[2], TRUE);
			}
			if (tutorial[y][x] == BLOCK4)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[3], TRUE);
			}
			if (tutorial[y][x] == BLOCK5)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[4], TRUE);
			}
			if (tutorial[y][x] == BLOCK6)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[5], TRUE);
			}
			if (tutorial[y][x] == BLOCK7)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[6], TRUE);
			}
			if (tutorial[y][x] == BLOCK8)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[7], TRUE);
			}
			if (tutorial[y][x] == BLOCK9)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[8], TRUE);
			}
			if (tutorial[y][x] == BLOCK10)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[9], TRUE);
			}
			if (tutorial[y][x] == BLOCK11)
			{
				DrawGraph((x * blockSize) - scrollX, y * blockSize, graphHandle[10], TRUE);
			}
		}
	}
}

int Map::RightHit(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) + 2) / blockSize > 19 || ((posY + posRadius) - 2) / blockSize > 19)
	{
	return 0;
	}
	if (tutorial[((posY - posRadius) + 2) / blockSize][((posX + posRadius) + 2) / blockSize] <= 0 &&
		tutorial[((posY + posRadius) - 2) / blockSize][((posX + posRadius) + 2) / blockSize] <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Map::LeftHit(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) + 3) / blockSize > 19 || ((posY + posRadius) - 3) / blockSize > 19)
	{
		return 0;
	}
	if (tutorial[((posY - posRadius) + 3) / blockSize][((posX - posRadius) - 3) / blockSize] <= 0 &&
		tutorial[((posY + posRadius) - 3) / blockSize][((posX - posRadius) - 3) / blockSize] <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Map::UpHit(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) - 3) / blockSize > 19 || ((posY - posRadius) - 2) / blockSize > 19)
	{
		return 0;
	}
	if (tutorial[((posY - posRadius) - 3) / blockSize][((posX - posRadius / 2) + 3) / blockSize] <= 0 &&
		tutorial[((posY - posRadius) - 2) / blockSize][((posX + posRadius / 2) - 2) / blockSize] <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Map::DownHit(int posX, int posY, int posRadius)
{
	if (((posY + posRadius) + 2) / blockSize > 19 || ((posY + posRadius) + 3) / blockSize > 19)
	{
		return 0;
	}
	if (tutorial[((posY + posRadius) + 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] > 0 ||
		tutorial[((posY + posRadius) + 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] > 0 ||
		tutorial[((posY + posRadius) + 2) / blockSize][posX / blockSize] > 0)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

int Map::Hit(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) + 2) / blockSize > 19 || ((posY + posRadius) - 2) / blockSize > 19 ||
		((posY - posRadius) + 3) / blockSize > 19 || ((posY + posRadius) - 3) / blockSize > 19 ||
		((posY + posRadius) + 2) / blockSize > 19 || ((posY + posRadius) + 3) / blockSize > 19 ||
		((posY - posRadius) - 3) / blockSize > 19 || ((posY - posRadius) - 2) / blockSize > 19)
	{
		return 0;
	}
	
	if (tutorial[((posY - posRadius) + 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 8 ||
		tutorial[((posY + posRadius) - 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 8 ||
		tutorial[((posY - posRadius) + 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 8 ||
		tutorial[((posY + posRadius) - 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 8 ||
		tutorial[((posY - posRadius) - 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 8 ||
		tutorial[((posY - posRadius) - 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 8 ||
		tutorial[((posY - posRadius) + 2) / blockSize][posX / blockSize] == 8 ||
		tutorial[((posY + posRadius) + 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 8 ||
		tutorial[((posY + posRadius) + 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 8 ||
		tutorial[((posY + posRadius) + 2) / blockSize][posX / blockSize] == 8)			
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int Map::Portion(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) + 2) / blockSize > 19 || ((posY + posRadius) - 2) / blockSize > 19 ||
		((posY - posRadius) + 3) / blockSize > 19 || ((posY + posRadius) - 3) / blockSize > 19 ||
		((posY + posRadius) + 2) / blockSize > 19 || ((posY + posRadius) + 3) / blockSize > 19 ||
		((posY - posRadius) - 3) / blockSize > 19 || ((posY - posRadius) - 2) / blockSize > 19)
	{
		return 0;
	}
	
	if (tutorial[((posY - posRadius) + 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 9 ||
		tutorial[((posY + posRadius) - 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 9 ||
		tutorial[((posY - posRadius) + 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 9 ||
		tutorial[((posY + posRadius) - 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 9 ||
		tutorial[((posY - posRadius) - 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 9 ||
		tutorial[((posY - posRadius) - 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 9 ||
		tutorial[((posY - posRadius) + 2) / blockSize][posX / blockSize] == 9 ||					  
		tutorial[((posY + posRadius) + 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 9 ||
		tutorial[((posY + posRadius) + 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 9 ||
		tutorial[((posY + posRadius) + 2) / blockSize][posX / blockSize] == 9)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int Map::Frag(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) + 2) / blockSize > 19 || ((posY + posRadius) - 2) / blockSize > 19 ||
		((posY - posRadius) + 3) / blockSize > 19 || ((posY + posRadius) - 3) / blockSize > 19 ||
		((posY + posRadius) + 2) / blockSize > 19 || ((posY + posRadius) + 3) / blockSize > 19 ||
		((posY - posRadius) - 3) / blockSize > 19 || ((posY - posRadius) - 2) / blockSize > 19)
	{
		return 0;
	}

	if (tutorial[((posY - posRadius) + 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 11 ||
		tutorial[((posY + posRadius) - 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 11 ||
		tutorial[((posY - posRadius) + 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 11 ||
		tutorial[((posY + posRadius) - 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 11 ||
		tutorial[((posY - posRadius) - 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 11 ||
		tutorial[((posY - posRadius) - 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 11 ||
		tutorial[((posY - posRadius) + 2) / blockSize][posX / blockSize] == 11 ||
		tutorial[((posY + posRadius) + 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 11 ||
		tutorial[((posY + posRadius) + 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 11 ||
		tutorial[((posY + posRadius) + 2) / blockSize][posX / blockSize] == 11)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Map::Clear(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) + 2) / blockSize > 19 || ((posY + posRadius) - 2) / blockSize > 19 ||
		((posY - posRadius) + 3) / blockSize > 19 || ((posY + posRadius) - 3) / blockSize > 19 ||
		((posY + posRadius) + 2) / blockSize > 19 || ((posY + posRadius) + 3) / blockSize > 19 ||
		((posY - posRadius) - 3) / blockSize > 19 || ((posY - posRadius) - 2) / blockSize > 19)
	{
		return 0;
	}
	if (tutorial[((posY - posRadius) + 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 10 ||
		tutorial[((posY + posRadius) - 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 10 ||
		tutorial[((posY - posRadius) + 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 10 ||
		tutorial[((posY + posRadius) - 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 10 ||
		tutorial[((posY - posRadius) - 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 10 ||
		tutorial[((posY - posRadius) - 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 10 ||
		tutorial[((posY - posRadius) + 2) / blockSize][posX / blockSize] == 10 ||
		tutorial[((posY + posRadius) + 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 10 ||
		tutorial[((posY + posRadius) + 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 10 ||
		tutorial[((posY + posRadius) + 2) / blockSize][posX / blockSize] == 10)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int Map::Size(int posX, int posY, int posRadius)
{
	if (((posY - posRadius) + 2) / blockSize > 19 || ((posY + posRadius) - 2) / blockSize > 19 ||
		((posY - posRadius) + 3) / blockSize > 19 || ((posY + posRadius) - 3) / blockSize > 19 ||
		((posY + posRadius) + 2) / blockSize > 19 || ((posY + posRadius) + 3) / blockSize > 19 ||
		((posY - posRadius) - 3) / blockSize > 19 || ((posY - posRadius) - 2) / blockSize > 19)
	{
		return 0;
	}
	if (tutorial[((posY - posRadius) + 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 8 ||
		tutorial[((posY + posRadius) - 2) / blockSize][((posX + posRadius) + 2) / blockSize] == 8 ||
		tutorial[((posY - posRadius) + 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 8 ||
		tutorial[((posY + posRadius) - 3) / blockSize][((posX - posRadius) - 3) / blockSize] == 8 ||
		tutorial[((posY - posRadius) - 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 8 ||
		tutorial[((posY - posRadius) - 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 8 ||
		tutorial[((posY - posRadius) + 2) / blockSize][posX / blockSize] == 8 ||
		tutorial[((posY + posRadius) + 2) / blockSize][((posX + (posRadius / 2)) - 2) / blockSize] == 8 ||
		tutorial[((posY + posRadius) + 3) / blockSize][((posX - (posRadius / 2)) + 3) / blockSize] == 8 ||
		tutorial[((posY + posRadius) + 2) / blockSize][posX / blockSize] == 8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Map::Scroll(int posX)
{
	if (posX >= 700 && posX <= 18000 - 700)
	{
		scrollX = posX - 700;
	}
}

void Map::Initialization()
{
	scrollX = 0;
	blockSize = 48;
	haikeiX = 1400;
	haikeiY = 0;
	
	FILE* fp;
	fopen_s(&fp, "Resource/01.csv", "r");
	if (fp != NULL)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 377; j++)
			{
				fscanf_s(fp, "%d,", &tutorial[i][j]);
			}
		}
		fclose(fp);
	}

	LoadDivGraph
	(
		"Resource/block.png",  //読み込みたい画像ファイルの名前
		9,             //グラフィックの総分割総数
		3,             //グラフィックの横向きに対する分割数
		3,             //グラフィックの縦向きに対する分割数
		48,            //グラフィックサイズ
		48,            //グラフィックサイズ
		graphHandle    //分割読み込みして得たグラフィックハンドルを保存するint型配列
	);

	for (int i = 0; i < 13; i++)
	{
		graphHandle2[i] = LoadGraph("Resource/Yasiki.png");
	}

	
}

int Map::GetScroll()
{
	return scrollX;
}
int Map::Getblocksize()
{
	return blockSize;
}
int Map::GetRight(int posX, int posRadius)
{
	return ((posX + posRadius) + 2) / blockSize * blockSize;
}
int Map::GetLeft(int posX, int posRadius)
{
	return ((posX - posRadius) - 3) / blockSize * blockSize;
}
int Map::GetUp(int posY, int posRadius)
{
	return ((posY - posRadius) - 3) / blockSize * blockSize;
}
int Map::GetDown(int posY, int posRadius)
{
	return ((posY + posRadius) + 2) / blockSize * blockSize;
}