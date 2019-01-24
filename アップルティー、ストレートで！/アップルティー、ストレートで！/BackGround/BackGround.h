#pragma once
#include "../etc/Vector2.h"
#include <vector>
#include <memory>

class Application;
class Camera;

class BackGround
{
public:
	// �R���X�g���N�^
	BackGround(std::weak_ptr<Application>app, std::weak_ptr<Camera>cam);
	// �f�X�g���N�^
	~BackGround();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// ������
	void Init(void);


	// �A�v���P�[�V����
	std::weak_ptr<Application>app;
	
	// �J����
	std::weak_ptr<Camera>cam;

	// �摜ID
	std::vector<int>image;

	// ���W
	std::vector<Vec2f>pos;

	// �T�C�Y
	Vec2f size;
};
