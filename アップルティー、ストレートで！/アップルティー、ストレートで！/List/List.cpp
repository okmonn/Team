#include "List.h"
#include "../Device/Device.h"
#include "../etc/Release.h"

// �R���X�g���N�^
List::List(const D3D12_COMMAND_LIST_TYPE & type) : 
	allo(nullptr), list(nullptr)
{
	CreateAllo(type);
	CreateList(type);
}

// �f�X�g���N�^
List::~List()
{
	Release(list);
	Release(allo);
}

// �A���P�[�^�̐���
long List::CreateAllo(const D3D12_COMMAND_LIST_TYPE & type)
{
	auto hr = Device::Get().GetDev()->CreateCommandAllocator(type, IID_PPV_ARGS(&allo));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�A���P�[�^�̐����F���s\n"));
	}

	return hr;
}

// ���X�g�̐���
long List::CreateList(const D3D12_COMMAND_LIST_TYPE & type)
{
	auto hr = Device::Get().GetDev()->CreateCommandList(0, type, allo, nullptr, IID_PPV_ARGS(&list));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n���X�g�̐����F���s\n"));
		return hr;
	}

	list->Close();

	return hr;
}

// ���Z�b�g
void List::Reset(ID3D12PipelineState * pipe)
{
	allo->Reset();
	list->Reset(allo, pipe);
}

// �r���[�|�[�g�̃Z�b�g
void List::SetView(const Vec2 & size)
{
	D3D12_VIEWPORT view{};
	view.Height   = static_cast<float>(size.y);
	view.MaxDepth = 1.0f;
	view.MinDepth = 0.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;
	view.Width    = static_cast<float>(size.x);

	list->RSSetViewports(1, &view);
}

// �V�U�[�̃Z�b�g
void List::SetScissor(const Vec2 & size)
{
	RECT scissor{};
	scissor.bottom = static_cast<long>(size.y);
	scissor.left   = 0;
	scissor.right  = static_cast<long>(size.x);
	scissor.top    = 0;

	list->RSSetScissorRects(1, &scissor);
}

// �o���A
void List::Barrier(const D3D12_RESOURCE_STATES & befor, const D3D12_RESOURCE_STATES & affter, ID3D12Resource * rsc)
{
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE::D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource   = rsc;
	barrier.Transition.StateBefore = befor;
	barrier.Transition.StateAfter  = affter;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;

	list->ResourceBarrier(1, &barrier);
}

// �`��p���[�g�V�O�l�`���̃Z�b�g
void List::SetRoot(ID3D12RootSignature * root)
{
	list->SetGraphicsRootSignature(root);
}

// �R���s���[�g�p���[�g�V�O�l�`���̃Z�b�g
void List::SetComputeRoot(ID3D12RootSignature * root)
{
	list->SetComputeRootSignature(root);
}

// �p�C�v���C���̃Z�b�g
void List::SetPipe(ID3D12PipelineState * pipe)
{
	list->SetPipelineState(pipe);
}

// �q�[�v�̃Z�b�g
void List::SetHeap(ID3D12DescriptorHeap ** heap, const size_t & num)
{
	list->SetDescriptorHeaps(num, heap);
}

// �q�[�v�ƕ`��p���[�g�V�O�l�`���̊֘A�t��
void List::SetRootTable(const unsigned int & id, ID3D12DescriptorHeap * heap, const unsigned int & index)
{
	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().GetDev()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * index;

	list->SetGraphicsRootDescriptorTable(id, handle);
}

// �q�[�v�ƃR���s���[�g�p���[�g�V�O�l�`���̊֘A�t��
void List::SetComputeRootTable(const unsigned int & id, ID3D12DescriptorHeap * heap, const unsigned int & index)
{
	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().GetDev()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * index;

	list->SetComputeRootDescriptorTable(id, handle);
}

// ���_�o�b�t�@�̃Z�b�g
void List::SetVertexBufferView(const D3D12_VERTEX_BUFFER_VIEW & view)
{
	list->IASetVertexBuffers(0, 1, &view);
}

// �g�|���W�[�^�C�v�̃Z�b�g
void List::SetTopology(const D3D_PRIMITIVE_TOPOLOGY & type)
{
	list->IASetPrimitiveTopology(type);
}

// ���_�`��
void List::DrawVertex(const size_t & vertexNum, const unsigned int & instance)
{
	list->DrawInstanced(static_cast<unsigned int>(vertexNum), instance, 0, 0);
}

// �R���s���[�g�̎��s
void List::Dispatch(const unsigned int & x, const unsigned int & y, const unsigned int & z)
{
	list->Dispatch(x, y, z);
}

// ���X�g�̃N���[�Y
void List::Close(void)
{
	list->Close();
}

// �o���h���̎��s
void List::ExecuteBundle(ID3D12GraphicsCommandList * list)
{
	this->list->ExecuteBundle(list);
}
