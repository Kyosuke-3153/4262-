#include "Description.h"

Description::Description()
{
	change = new Change(255, 2);
	keys[255] = { 0 };
	oldkeys[255] = { 0 };
	endFlag = 0;
	count = 2;
	graphHandle = LoadGraph("Resource/title2.png");
}

void Description::Update()
{
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	GetHitKeyStateAll(keys);
	change->SceneIn();
	change->SceneOut();

	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && change->GetBlend() <= 0)
	{
		change->SetCount(1);
		count = 1;
	}

	if (change->GetCount() == 2 && count == 1)
	{
		endFlag = 1;
	}
}

void Description::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, graphHandle, TRUE);
	change->Draw();
}

void Description::Initialization()
{
	change = new Change(255, 2);
	keys[255] = { 0 };
	oldkeys[255] = { 0 };
	endFlag = 0;
	count = 2;
}

int Description::GetEndFlag()
{
	return endFlag;
}