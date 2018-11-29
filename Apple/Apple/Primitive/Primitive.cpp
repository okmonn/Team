#include "Primitive.h"
#include "../Window/Window.h"
#include "../Device/Device.h"
#include "../List/List.h"
#include "../Root/Root.h"
#include "../Pipe/Pipe.h"
#include "../etc/Release.h"

// コンストラクタ
Primitive::Primitive() : 
	heap(nullptr), rsc(nullptr), vRsc(nullptr)
{
	list = std::make_unique<List>(dev);
}

// デストラクタ
Primitive::~Primitive()
{
}

// ヒープの生成
long Primitive::CreateHeap(void)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask       = 0;
	desc.NumDescriptors = 1;
	desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	return 0;
}
