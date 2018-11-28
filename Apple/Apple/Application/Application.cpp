#include "Application.h"
#include "../Window/Window.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include <Windows.h>

// コンストラクタ
Application::Application()
{
	Create();
}

// デストラクタ
Application::~Application()
{
}

// クラスの生成
void Application::Create(void)
{
	win   = std::make_shared<Window>();
	input = std::make_shared<Input>(win);
	un    = std::make_shared<Union>(win);
}

// メッセージの確認
bool Application::CheckMsg(void)
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//呼び出し側スレッドが所有しているウィンドウに送信されたメッセージの保留されている物を取得
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//仮想キーメッセージを文字メッセージに変換
		TranslateMessage(&msg);
		//1つのウィドウプロシージャにメッセージを送出する
		DispatchMessage(&msg);
	}
	else
	{
		un->Draw();
	}

	return true;
}

// キーの入力
bool Application::InputKey(const int & i)
{
	return input->CheckKey(i);
}
