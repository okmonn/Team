#pragma once
#include <memory>

class Input;
class Union;
class Scene;

class Game
{
public:
	// コンストラクタ
	Game(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// デストラクタ
	~Game();

	// シーン移行
	static void ChangeScene(Scene* scene);

	// 処理
	void Run(void);

private:
	// シーン
	static std::shared_ptr<Scene>scene;
};
