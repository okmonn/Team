#pragma once
#include <vector>
#include <memory>
#include <DirectXMath.h>

enum D3D_PRIMITIVE_TOPOLOGY : int;
class DescriptorMane;
class Window;
class Device;
class List;
class Root;
class Pipe;

namespace prm {
	struct Vertex
	{
		//���W
		DirectX::XMFLOAT3 pos;
		//�F
		DirectX::XMFLOAT4 color;
	};
}

class Primitive
{
public:
	// �R���X�g���N�^
	Primitive();
	// �f�X�g���N�^
	virtual ~Primitive();

protected:
	// �萔���\�[�X�̐���
	long CreateRsc(void);

	// �萔�o�b�t�@�r���[�̐���
	void CreateView(void);

	// �萔�̃}�b�v
	long Map(void);

	// ���_���\�[�X�̐���
	long CreateVrsc(void);


	// �f�B�X�N���v�^�[�}�l�[�W���[
	DescriptorMane& descMane;

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

	// �萔�q�[�v�E���\�[�X
	int constant;

	// ���_���\�[�X
	int vRsc;

	// ���_
	std::vector<prm::Vertex>vertex;
};
