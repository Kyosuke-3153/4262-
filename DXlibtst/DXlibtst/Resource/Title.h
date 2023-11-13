#pragma once
#include "DxLib.h"
#include "Change.h"

class Title
{
public:
	Title();
	void Start();
	void Update();
	void Draw();
	void Initialization();

	int GetEndFlag();

private:
	Change* change;
	int count;
	char keys[256];
	char oldkeys[256];
	int endFlag;

	int graphHandle;
};