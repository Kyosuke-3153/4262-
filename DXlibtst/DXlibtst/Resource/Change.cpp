#include "Change.h"

Change::Change(int blend, int count)
{
	boxX[0] = 0;
	boxX[1] = 1400;
	boxY[0] = 0;
	boxY[1] = 960;
	this->blend = blend;
	this->count = count;
}

void Change::SceneIn()
{
	if (count == 1)
	{
		blend += 3;

		if (blend >= 
			5)
		{
			blend = 255;
			count = 2;
		}
	}
}

void Change::SceneOut()
{
	if (count == 2)
	{
		blend -= 10;

		if (blend < 0)
		{
			blend = 0;
			count = 0;
		}
	}
}

void Change::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
	DrawBox(boxX[0], boxY[0], boxX[1], boxY[1], GetColor(0, 0, 0), TRUE);
}

void Change::SetCount(int count)
{
	this->count = count;
}

int Change::GetCount()
{
	return count;
}

int Change::GetBlend()
{
	return blend;
}