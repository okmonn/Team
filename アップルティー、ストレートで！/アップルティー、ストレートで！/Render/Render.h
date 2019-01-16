#pragma once
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class List;
class Swap;

class Render
{
public:
	// �R���X�g���N�^
	Render(std::weak_ptr<Swap>swap);
	// �f�X�g���N�^
	~Render();

	// �N���A
	void Clear(std::weak_ptr<List>list, ID3D12DescriptorHeap* depth = nullptr);

	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(void);

	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(void);
	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(const unsigned int& i);

private:
	// �����_�[�̐���
	void Create(void);


	// �X���b�v
	std::weak_ptr<Swap>swap;

	// �q�[�vID
	int heap;

	// ���\�[�XID
	std::vector<int>rsc;
};
