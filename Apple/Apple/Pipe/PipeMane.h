#pragma once
#include <map>
#include <memory>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE : int;
struct D3D12_INPUT_ELEMENT_DESC;
class Device;
class Swap;
class Root;
class RootCompute;
class Pipe;
class PipeCompute;

class PipeMane
{
public:
	// �f�X�g���N�^
	~PipeMane();

	// �C���X�^���X�ϐ��̎擾
	static PipeMane& Get(void) {
		static PipeMane instance;
		return instance;
	}

	// �p�C�v���C���̐���
	void CreatePipe(int& i, std::weak_ptr<Device>dev, std::weak_ptr<Swap>swap, std::weak_ptr<Root>root, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<int>&index, const bool& depth);

	// �p�C�v���C���N���X�̎擾
	std::shared_ptr<Pipe>Get(int& i) {
		return pipe[&i];
	}

private:
	// �R���X�g���N�^
	PipeMane();
	PipeMane(const PipeMane&) {
	}
	void operator=(const PipeMane&) {
	}

	// �p�C�v���C��
	std::map<int*, std::shared_ptr<Pipe>>pipe;
};
