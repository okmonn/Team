#pragma once
#include "Scene.h"

class Title :
	public Scene
{
public:
	// �R���X�g���N�^
	Title(std::weak_ptr<Application>app);
	// �f�X�g���N�^
	~Title();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:

};
