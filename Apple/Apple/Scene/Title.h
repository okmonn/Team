#pragma once
#include "Scene.h"

class Title :
	public Scene
{
public:
	// �R���X�g���N�^
	Title(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Title();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:

};
