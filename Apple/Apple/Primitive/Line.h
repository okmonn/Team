#pragma once
#include "Primitive.h"

class Line :
	public Primitive
{
public:
	// �R���X�g���N�^
	Line(std::weak_ptr<Window>win, std::weak_ptr<Device>dev, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe);
	// �f�X�g���N�^
	~Line();

	// ���_�̃Z�b�g
	long SetVertex(const DirectX::XMFLOAT2& pos1, const DirectX::XMFLOAT2& pos2, const DirectX::XMFLOAT3& color, const float& alpha);

	// �`��
	void Draw(std::weak_ptr<List>list);

private:
	// ������
	void Init(void);

	// �o���h���̃Z�b�g
	void Bundle(void);
};
