#pragma once
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Window;
class List;

class Depth
{
public:
	// �R���X�g���N�^
	Depth(std::weak_ptr<Window>win);
	// �f�X�g���N�^
	~Depth();

	// �N���A
	void Clear(std::weak_ptr<List>list);

	// �q�[�v�̎擾
	ID3D12DescriptorHeap* GetHeap(void);
	// ���\�[�X�̎擾
	ID3D12Resource* GetRsc(void);

private:
	// �f�v�X�̐���
	void Create(void);


	// �E�B���h�E
	std::weak_ptr<Window>win; 

	// �q�[�vID
	int heap;

	// ���\�[�X��ID
	int rsc;
};
