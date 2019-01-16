#pragma once
#include "../etc/Vector2.h"

enum D3D12_COMMAND_LIST_TYPE : int;
enum D3D12_RESOURCE_STATES : int;
enum D3D_PRIMITIVE_TOPOLOGY : int;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
struct ID3D12RootSignature;
struct ID3D12PipelineState;
struct D3D12_VERTEX_BUFFER_VIEW;

class List
{
public:
	// �R���X�g���N�^
	List(const D3D12_COMMAND_LIST_TYPE& type);
	// �f�X�g���N�^
	~List();

	// ���Z�b�g
	void Reset(ID3D12PipelineState* pipe = nullptr);

	// �r���[�|�[�g�̃Z�b�g
	void SetView(const Vec2& size);

	// �V�U�[�̃Z�b�g
	void SetScissor(const Vec2& size);

	// �o���A
	void Barrier(const D3D12_RESOURCE_STATES & befor, const D3D12_RESOURCE_STATES & affter, ID3D12Resource * rsc);

	// �`��p���[�g�V�O�l�`���̃Z�b�g
	void SetRoot(ID3D12RootSignature* root);

	// �R���s���[�g�p���[�g�V�O�l�`���̃Z�b�g
	void SetComputeRoot(ID3D12RootSignature* root);

	// �p�C�v���C���̃Z�b�g
	void SetPipe(ID3D12PipelineState* pipe);

	// �q�[�v�̃Z�b�g
	void SetHeap(ID3D12DescriptorHeap** heap, const size_t& num);

	// �q�[�v�ƕ`��p���[�g�V�O�l�`���̊֘A�t��
	void SetRootTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const unsigned int& index = 0);

	// �q�[�v�ƃR���s���[�g�p���[�g�V�O�l�`���̊֘A�t��
	void SetComputeRootTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const unsigned int& index = 0);

	// ���_�o�b�t�@�̃Z�b�g
	void SetVertexBufferView(const D3D12_VERTEX_BUFFER_VIEW& view);

	// �g�|���W�[�^�C�v�̃Z�b�g
	void SetTopology(const D3D_PRIMITIVE_TOPOLOGY& type);

	// ���_�`��
	void DrawVertex(const size_t& vertexNum, const unsigned int& instance = 1);

	// �R���s���[�g�̎��s
	void Dispatch(const unsigned int& x, const unsigned int& y, const unsigned int& z);

	// ���X�g�̃N���[�Y
	void Close(void);

	// �o���h���̎��s
	void ExecuteBundle(ID3D12GraphicsCommandList* list);

	// �A���P�[�^�̎擾
	ID3D12CommandAllocator* GetAllo(void) const {
		return allo;
	}
	// ���X�g�̎擾
	ID3D12GraphicsCommandList* GetList(void) const {
		return list;
	}

private:
	// �A���P�[�^�̐���
	long CreateAllo(const D3D12_COMMAND_LIST_TYPE& type);

	// ���X�g�̐���
	long CreateList(const D3D12_COMMAND_LIST_TYPE& type);



	// �A���P�[�^
	ID3D12CommandAllocator* allo;

	// ���X�g
	ID3D12GraphicsCommandList* list;
};
