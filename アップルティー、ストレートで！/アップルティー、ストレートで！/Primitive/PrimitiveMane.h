#pragma once
#include "PrimitiveInfo.h"
#include <list>
#include <string>
#include <memory>

class Primitive;
class Window;
class List;
class Root;

class PrimitiveMane
{
public:
	// �R���X�g���N�^
	PrimitiveMane(std::weak_ptr<Window>win, std::weak_ptr<Root>root);
	// �f�X�g���N�^
	~PrimitiveMane();

	// �`��
	void Draw(std::weak_ptr<List>list, const prm::PrimitiveType& type, prm::Vertex* vertex, const size_t& num);

	// �N���A
	void Clear(void);

private:
	// �p�C�v�̐���
	void CreatePipe(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// ���[�g
	std::weak_ptr<Root>root;

	// �v���~�e�B�u
	std::list<std::unique_ptr<Primitive>>primitive;
};
