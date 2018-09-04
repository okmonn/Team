#include "Game.h"
#include "../Scene/Title.h"
#include "../Touch/Touch.h"
#include "DxLib.h"

// コンストラクタ
Game::Game() : 
	scene(nullptr)
{
}

// デストラクタ
Game::~Game()
{
}

// シーン移行
void Game::ChangeScene(Scene * scene)
{
	this->scene.reset(scene);
}

// 初期化
int Game::Init(void)
{
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

#ifndef __ANDROID__
	SetWindowSizeChangeEnableFlag(true, true);
	SetWindowSize((int)(SHOW_X), (int)(SHOW_Y));
	//true:window　false:ﾌﾙｽｸﾘｰﾝ
	ChangeWindowMode(true);
	//windowテキストの設定
	SetWindowText(_T("HappyApple"));
#endif

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SetFontSize(36);

	ChangeScene(new Title());

	return 0;
}

// 描画
void Game::Draw(void)
{
	ClsDrawScreen();

	scene->Draw();

	Touch::Get().Draw();

	ScreenFlip();
}

// 処理
void Game::UpData(void)
{
	Draw();

	Touch::Get().UpData();

	scene->UpData();
}

// 処理
void Game::Run(void)
{
	if (Init() != 0)
	{
		return;
	}

#ifndef __ANDROID__
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
#else
	while (ProcessMessage() == 0)
#endif
	{
		UpData();
	}

	End();
}

// 終了
void Game::End(void)
{
	DxLib_End();
}
