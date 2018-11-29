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
		//���W
		DirectX::XMFLOAT3 pos;
		//�F
		DirectX::XMFLOAT3 color;
		//�A���t�@�l
		float alpha;
	};

public:
	// �R���X�g���N�^
	Primitive();
	// �f�X�g���N�^
	virtual ~Primitive();

protected:
	// �q�[�v�̐���
	long CreateHeap(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// ���X�g
	std::unique_ptr<List>list;

	// ���[�g
	std::weak_ptr<Root>root;

	// �p�C�v
	std::weak_ptr<Pipe>pipe;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// �萔���\�[�X
	ID3D12Resource* rsc;

	// ���_���\�[�X
	ID3D12Resource* vRsc;
};
