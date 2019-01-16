#pragma once
#include "PrimitiveInfo.h"
#include <vector>
#include <memory>

struct ID3D12Resource;
class Window;
class List;
class Root;
class Pipe;

class Primitive
{
public:
	// �R���X�g���N�^
	Primitive(std::weak_ptr<Window>win, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe, const prm::PrimitiveType& type);
	// �f�X�g���N�^
	~Primitive();

	// �`��
	void Draw(std::weak_ptr<List>list, const prm::Vertex* vertex, const size_t& num);

protected:
	// ���_�o�b�t�@�̐���
	void VertexBuffer(void);

	// �}�b�v
	long Map(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// ���[�g
	std::weak_ptr<Root>root;

	// �p�C�v
	std::weak_ptr<Pipe>pipe;

	// �v���~�e�B�u�^�C�v
	prm::PrimitiveType type;

	// ���\�[�XID
	int rsc;

	// ���_�f�[�^
	std::vector<prm::Vertex>vertex;
};
