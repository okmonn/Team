#include "Union.h"
#include "../Window/Window.h"
#include "../Device/Device.h"
#include "../Queue/Queue.h"
#include "../List/List.h"
#include "../Swap/Swap.h"
#include "../Render/Render.h"
#include "../Depth/Depth.h"
#include "../Fence/Fence.h"
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

// コンストラクタ
Union::Union(std::weak_ptr<Window>win) : 
	win(win)
{
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	Create();
}

// デストラクタ
Union::~Union()
{
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

	list->SetBarrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, ren->Get());

	list->GetList()->Close();

	ID3D12CommandList* com[] = {
		list->GetList(),
	};
	queue->Get()->ExecuteCommandLists(_countof(com), com);

	swap->Get()->Present(1, 0);

	fence->Wait();
}
