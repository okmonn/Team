#pragma once
#include "../etc/tString.h"
#include <map>
#include <memory>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE : int;
class RootMane;
class PipeMane;
class Window;
class Device;
class Queue;
class List;
class Swap;
class Render;
class Depth;
class Fence;
class Texture;

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
	// ルートシグネチャの生成
	void CreateRoot(const std::string& name, const std::tstring& fileName);
	void CreateRoot(void);

	// パイプラインの生成
	void CreatePipe(const std::string& name, const std::string& rootName, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type,
		const std::initializer_list<int>&index, const bool& depth = false);
	void CreatePipe(void);

	// クラスの生成
	void Create(void);

	// ルートマネジャー
	RootMane& root;

	// パイプマネジャー
	PipeMane& pipe;

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

	// ルートシグネチャID
	std::map<std::string, int>rootNo;

	// パイプラインID
	std::map<std::string, int>pipeNo;

	// テクスチャ
	std::unique_ptr<Texture>tex;
};
