#include "Title.h"

Title::Title()
{
	change = new Change(0,0);
	count = 0;
	keys[255] = { 0 };
	oldkeys[255] = { 0 };
	endFlag = 0;

	graphHandle = LoadGraph("Resource/title.png");
}

void Title::Start()
{
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
	{
		change->SetCount(1);
		count = 1;
	}

	if (change->GetCount() == 2 && count == 1)
	{
		endFlag = 1;
	}
}

void Title::Update()
{
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	GetHitKeyStateAll(keys);
	Start();
	change->SceneIn();
	change->SceneOut();
}

void Title::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, graphHandle, TRUE);
	change->Draw();
}

void Title::Initialization()
{
	change = new Change(255, 1);
	count = 0;
	keys[255] = { 0 };
	oldkeys[255] = { 0 };
	endFlag = 0;
}

int Title::GetEndFlag()
{
	return endFlag;
}