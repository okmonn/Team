#pragma once
#include <memory>

class Window;
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

	// ユニオン
	std::shared_ptr<Union>un;
};
