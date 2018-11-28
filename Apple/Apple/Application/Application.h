#pragma once
#include "../etc/KeyData.h"
#include <memory>

class Window;
class Input;
class Union;

class Application
{
public:
	// デストラクタ
	~Application();

	// インスタンス変数の取得
	static Application& Get(void) {
		static Application instance;
		return instance;
	}

	// メッセージの確認
	bool CheckMsg(void);

	// キーの入力
	bool InputKey(const int& i);

private:
	// コンストラクタ
	Application();
	Application(const Application&) {
	}
	void operator=(const Application&) {
	}

	// クラスの生成
	void Create(void);


	// ウィンドウ
	std::shared_ptr<Window>win;

	// インプット
	std::shared_ptr<Input>input;

	// ユニオン
	std::shared_ptr<Union>un;
};
