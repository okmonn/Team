#pragma once
#include "Scene.h"

class Play :
	public Scene
{
public:
	// �R���X�g���N�^
	Play(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Play();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:

};
