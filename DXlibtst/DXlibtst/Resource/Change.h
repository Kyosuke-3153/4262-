#pragma once
#include "DxLib.h"

class Change
{
public:
	Change(int blend, int count);
	void SceneIn();
	void SceneOut();
	void Draw();
	void SetCount(int count);
	int GetCount();
	int GetBlend();

private:
	int boxX[2];
	int boxY[2];
	int blend;
	int count;
};

