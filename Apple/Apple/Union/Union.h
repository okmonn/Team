#pragma once
#include "../etc/tString.h"
#include <map>
#include <list>
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
class Point;

class Union
{
public:
	// コンストラクタ
	Union(std::weak_ptr<Window>win);
	// デストラクタ
	~Union();

	// 画像の読み込み
	void LoadImg(const std::string& fileName, int& i);

	// 画像の描画
	void DrawImg(int& i, const float& x, const float& y, const float& sizeX, const float& sizeY, const float& rectX, const float& rectY, 
		const float& rectSizexX, const float& rectSizeY, const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);

	// 点の描画
	void DrawPoint(const float& x, const float& y, const float& r, const float& g, const float& b, const float& alpha = 1.0f);

	// 画面クリア
	void Clear(void);

	// 実行
	void Execution(void);

	// デバイスの取得
	std::shared_ptr<Device>GetDev(void) const {
		return dev;
	}

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

	// ポイント
	std::list<std::shared_ptr<Point>>point;
};
