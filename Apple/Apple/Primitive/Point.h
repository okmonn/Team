#pragma once
#include "Primitive.h"

class Point :
	public Primitive
{
public:
	// �R���X�g���N�^
	Point(std::weak_ptr<Window>win, std::weak_ptr<Device>dev, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe);
	// �f�X�g���N�^
	~Point();

	// ���_�̃Z�b�g
	long SetVertex(const DirectX::XMFLOAT2& pos, const DirectX::XMFLOAT3& color, const float& alpha);

	// �`��
	void Draw(std::weak_ptr<List>list);

private:
	// ������
	void Init(void);

	// �o���h���̃Z�b�g
	void Bundle(void);
};
