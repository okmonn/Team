#include "Union.h"
#include "../Window/Window.h"
#include "../Device/Device.h"
#include "../Queue/Queue.h"
#include "../List/List.h"
#include "../Swap/Swap.h"
#include "../Render/Render.h"
#include "../Depth/Depth.h"
#include "../Fence/Fence.h"
#include "../Root/RootMane.h"
#include "../Root/Root.h"
#include "../Pipe/PipeMane.h"
#include "../Pipe/Pipe.h"
#include "../Texture/Texture.h"
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

int n = 0;
int a = 0;

// コンストラクタ
Union::Union(std::weak_ptr<Window>win) : 
	root(RootMane::Get()), pipe(PipeMane::Get()), win(win)
{
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	rootNo.clear();
	pipeNo.clear();

	Create();
}

// デストラクタ
Union::~Union()
{
}

// ルートシグネチャの生成
void Union::CreateRoot(const std::string & name, const std::tstring & fileName)
{
	if (rootNo.find(name) != rootNo.end())
	{
		return;
	}

	rootNo[name] = 0;
	root.CreateRoot(rootNo[name], dev, fileName);
}

// ルートシグネチャの生成
void Union::CreateRoot(void)
{
	CreateRoot("texture", L"Shader/Texture.hlsl");
}

// パイプラインの生成
void Union::CreatePipe(const std::string & name, const std::string & rootName, const D3D12_PRIMITIVE_TOPOLOGY_TYPE & type,
	const std::initializer_list<int> & index, const bool & depth)
{
	if (pipeNo.find(name) != pipeNo.end())
	{
		return;
	}

	pipeNo[name] = 0;
	pipe.CreatePipe(pipeNo[name], dev, swap, root.Get(rootNo[rootName]), type, index, depth);
}

// パイプラインの生成
void Union::CreatePipe(void)
{
	CreatePipe("texture", "texture", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0, 2 }, false);
}

// クラスの生成
void Union::Create(void)
{
	dev = std::make_shared<Device>();
	queue = std::make_shared<Queue>(dev);
	list = std::make_shared<List>(dev);
	swap = std::make_shared<Swap>(win, queue);
	ren = std::make_unique<Render>(dev, swap);
	depth = std::make_unique<Depth>(dev, win.lock()->GetX(), win.lock()->GetY());
	fence = std::make_unique<Fence>(dev, queue);

	CreateRoot();
	CreatePipe();

	tex = std::make_unique<Texture>(win, dev, root.Get(rootNo["texture"]), pipe.Get(pipeNo["texture"]));
	tex->Load("avicii.png", n);
	tex->Load("avicii.png", a);
}

// 描画
void Union::Draw(void)
{
	list->Reset();

	list->SetView(win.lock()->GetX(), win.lock()->GetY());
	list->SetScissor(win.lock()->GetX(), win.lock()->GetY());

	list->SetBarrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, ren->Get());

	depth->Clear(list);
	ren->Clear(list, depth->GetHeap());

	tex->Draw(list, n, { 0,0 }, { 320,480 }, { 0,0 }, { 320,320 });
	tex->Draw(list, a, { 320,0 }, { 320,480 }, { 0,0 }, { 320,320 }, 0.5f, true, true);

	list->SetBarrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, ren->Get());

	list->GetList()->Close();

	ID3D12CommandList* com[] = {
		list->GetList(),
	};
	queue->Get()->ExecuteCommandLists(_countof(com), com);

	swap->Get()->Present(1, 0);

	fence->Wait();
}
