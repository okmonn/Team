#pragma once
#include <memory>
#include <DirectXMath.h>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Window;
class Device;
class List;
class Root;
class Pipe;

class Primitive
{
	struct Vertex
	{
		//座標
		DirectX::XMFLOAT3 pos;
		//色
		DirectX::XMFLOAT3 color;
		//アルファ値
		float alpha;
	};

public:
	// コンストラクタ
	Primitive();
	// デストラクタ
	virtual ~Primitive();

protected:
	// ヒープの生成
	long CreateHeap(void);


	// ウィンドウ
	std::weak_ptr<Window>win;

	// デバイス
	std::weak_ptr<Device>dev;

	// リスト
	std::unique_ptr<List>list;

	// ルート
	std::weak_ptr<Root>root;

	// パイプ
	std::weak_ptr<Pipe>pipe;

	// ヒープ
	ID3D12DescriptorHeap* heap;

	// 定数リソース
	ID3D12Resource* rsc;

	// 頂点リソース
	ID3D12Resource* vRsc;
};
