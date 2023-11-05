#include "DxLib.h"
#include "Title.h"
#include "Description.h"
#include "GameScene.h"
#include "End.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GOGO";

// ウィンドウ横幅
const int WIN_WIDTH = 1400;

// ウィンドウ縦幅 
const int WIN_HEIGHT = 960;	

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0xFF);			

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み

	int bgm[4];
	bgm[0] = LoadSoundMem("小さな魔女.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[0]);
	bgm[1] = LoadSoundMem("Hope_Amidst_Youthful_Poverty.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[1]);
	bgm[2] = LoadSoundMem("いたずら３きょうだい.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[2]);
	bgm[3] = LoadSoundMem("b47a1cbcadc45b8c.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[2]);

	// ゲームループで使う変数の宣言

	Title* title = new Title;
	Description* description = new Description;
	GameScene* gameScene = new GameScene;
	End* end = new End;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		
		if (title->GetEndFlag() == 0)
		{
			title->Update();

			if (CheckSoundMem(bgm[1]) == 1)
			{
				StopSoundMem(bgm[1]);
			}
			if (CheckSoundMem(bgm[2]) == 1)
			{
				StopSoundMem(bgm[2]);
			}
			if (CheckSoundMem(bgm[3]) == 1)
			{
				StopSoundMem(bgm[3]);
			}
			if (CheckSoundMem(bgm[0]) == 0)
			{
				PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
			}
		}
		if(title->GetEndFlag() == 1 && description->GetEndFlag() == 0)
		{
			description->Update();
		}
		if (description->GetEndFlag() == 1 && gameScene->GetEndFlag() == 0)
		{
			gameScene->Update();

			if (CheckSoundMem(bgm[0]) == 1)
		
			{
				StopSoundMem(bgm[0]);
			}
			if (CheckSoundMem(bgm[2]) == 1)
			{
				StopSoundMem(bgm[2]);
			}
			if (CheckSoundMem(bgm[3]) == 1)
			{
				StopSoundMem(bgm[3]);
			}
			if (CheckSoundMem(bgm[1]) == 0)
			{
				PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP);
			}
		}
		if(gameScene->GetEndFlag() == 1)
		{
			end->GameOver();
			end->SetNumber(1);

			if (CheckSoundMem(bgm[0]) == 1)
			{
				StopSoundMem(bgm[0]);
			}
			if (CheckSoundMem(bgm[1]) == 1)
			{
				StopSoundMem(bgm[1]);
			}
			if (CheckSoundMem(bgm[3]) == 1)
			{
				StopSoundMem(bgm[3]);
			}
			if (CheckSoundMem(bgm[2]) == 0)
			{
				PlaySoundMem(bgm[2], DX_PLAYTYPE_LOOP);
			}
		}
		if (gameScene->GetEndFlag() == 2)
		{
			end->Clear();
			end->SetNumber(2);

			if (CheckSoundMem(bgm[0]) == 1)
			{
				StopSoundMem(bgm[0]);
			}
			if (CheckSoundMem(bgm[1]) == 1)
			{
				StopSoundMem(bgm[1]);
			}
			if (CheckSoundMem(bgm[2]) == 1)
			{
				StopSoundMem(bgm[2]);
			}
			if (CheckSoundMem(bgm[3]) == 0)
			{
				PlaySoundMem(bgm[3], DX_PLAYTYPE_LOOP);
			}
		}
		if (end->GetCount() == 1)
		{
			title->Initialization();
			description->Initialization();
			gameScene->Initialization();
			end->Initialization();
		}

		// 描画処理

		
		if (title->GetEndFlag() == 0)
		{
		//タイトル
			title->Draw();
		}
		if(title->GetEndFlag() == 1  && description->GetEndFlag() == 0)
		{
			//ルール説明
			description->Draw();
		}
		if (description->GetEndFlag() == 1 && gameScene->GetEndFlag() == 0)
		{
			//ゲーム本体
			gameScene->Draw();
		}
		if (gameScene->GetEndFlag() >= 1)
		{
			//ゲームオーバー
			end->Draw();
		}

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();	

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	
	;
}