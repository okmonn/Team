#pragma once
#include "Scene.h"

class Over :
	public Scene
{
public:
	// �R���X�g���N�^
	Over(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Over();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:

};
