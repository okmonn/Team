#pragma once
#include <memory>

class Window;
class Device;
class Queue;
class List;
class Swap;
class Render;
class Depth;
class Fence;

class Union
{
public:
	// コンストラクタ
	Union(std::weak_ptr<Window>win);
	// デストラクタ
	~Union();

	// 描画
	void Draw(void);

private:
	// クラスの生成
	void Create(void);


	// ウィンドウ
	std::weak_ptr<Window>win;

	// デバイス
	std::shared_ptr<Device>dev;

	// キュー
	std::shared_ptr<Queue>queue;

	// リスト
	std::shared_ptr<List>list;

	// スワップ
	std::shared_ptr<Swap>swap;

	// レンダー
	std::unique_ptr<Render>ren;

	// 深度
	std::unique_ptr<Depth>depth;

	// フェンス
	std::unique_ptr<Fence>fence;
};
