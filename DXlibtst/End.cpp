#include "End.h"

End::End()
{
	change = new Change(255, 2);
	number = 0;
	keys[255] = { 0 };
	oldkeys[255] = { 0 };
	endFlag = 0;
	count = 0;
	resetFalg = 0;

	graphHandle[0] = LoadGraph("Resource/over.png");
	graphHandle[1] = LoadGraph("Resource/cler.png");
}

void End::GameOver()
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
		resetFalg = 1;
	}

	if (change->GetCount() == 2 && resetFalg == 1)
	{
		count = 1;
	}
}

void End::Clear()
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
		resetFalg = 1;
	}

	if (change->GetCount() == 2 && resetFalg == 1)
	{
		count = 1;
	}
}

void End::Initialization()
{
	change = new Change(255, 2);
	number = 0;
	keys[255] = { 0 };
	oldkeys[255] = { 0 };
	endFlag = 0;
	count = 0;
	resetFalg = 0;
}

void End::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (number == 1)
	{
		DrawGraph(0, 0, graphHandle[0], TRUE);
	}
	else if (number == 2)
	{
		DrawGraph(0, 0, graphHandle[1], TRUE);
		change->Draw();
	}
}

int End::GetCount()
{
	return count;
}

int End::GetEndFlag()
{
	return endFlag;
}

void End::SetCount(int count)
{
	this->count = count;
}

void End::SetNumber(int number)
{
	this->number = number;
}