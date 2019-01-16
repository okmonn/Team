#pragma once
#include <memory>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE : int;
struct D3D12_INPUT_ELEMENT_DESC;
struct ID3D12PipelineState;
class Root;

class Pipe
{
public:
	// �R���X�g���N�^
	Pipe(std::weak_ptr<Root>root);
	// �f�X�g���N�^
	~Pipe();

	// �`��p�p�C�v���C���̐���
	long CreateGraphics(const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);

	// �v�Z�p�p�C�v���C���̐���
	long CreateCompute(void);

	// �p�C�v���C���̎擾
	ID3D12PipelineState* Get(void) const {
		return pipe;
	}

private:
	// ���[�g
	std::weak_ptr<Root>root;

	// �p�C�v���C��
	ID3D12PipelineState* pipe;
};
