#pragma once
#include "Scene.h"

class Result :
	public Scene
{
public:
	// �R���X�g���N�^
	Result(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Result();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:

};
