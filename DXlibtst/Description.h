#pragma once
#include "Change.h"

class Description
{
public:
	Description();
	void Update();
	void Draw();
	void Initialization();
	int GetEndFlag();
private:
	Change* change;
	int count;
	int endFlag;
	char keys[256];
	char oldkeys[256];
	int graphHandle;
};

