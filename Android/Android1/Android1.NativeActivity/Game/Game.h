#pragma once
#include <memory>

class Scene;

class Game
{
public:
	// デストラクタ
	~Game();

	// インスタンス変数の取得
	static Game& Get(void) {
		static Game instance;
		return instance;
	}

	// シーン移行
	void ChangeScene(Scene* scene);

	// 処理
	void Run(void);

private:
	// コンストラクタ
	Game();
	Game(const Game&) {
	}
	void operator=(const Game&) {
	}

	// 初期化
	int Init(void);

	// 終了
	void End(void);

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);


	// シーン
	std::shared_ptr<Scene>scene;
};

