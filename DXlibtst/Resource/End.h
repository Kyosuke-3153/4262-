#pragma once
#include "Change.h"

class End
{
public:
	End();
	void GameOver();
	void Clear();
	void Initialization();
	void Draw();

	int GetCount();
	int GetEndFlag();
	void SetCount(int count);
	void SetNumber(int number);


private:
	Change* change;
	int count;
	int number;
	int endFlag;
	int resetFalg;
	char keys[256];
	char oldkeys[256];

	int graphHandle[2];
};

