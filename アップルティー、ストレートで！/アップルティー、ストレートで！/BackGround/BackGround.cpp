#include "BackGround.h"
#include "../Camera/Camera.h"
#include "../Application/Application.h"
#include "../Input/Input.h"
#include <algorithm>

// �摜��
#define IMAG_MAX 2

// �摜�T�C�Y
const Vec2f imagSize = { 2560.0f, 720.0f };

// �R���X�g���N�^
BackGround::BackGround(std::weak_ptr<Application> app, std::weak_ptr<Camera> cam) : app(app), cam(cam),
	size(0.0f)
{
	image.resize(IMAG_MAX);
	pos.resize(IMAG_MAX);

	Init();
}

// �f�X�g���N�^
BackGround::~BackGround()
{
	for (auto& i : image)
	{
		app.lock()->DeleteTex(i);
	}
}

// ������
void BackGround::Init(void)
{
	auto win = app.lock()->GetWinSize();
	size = { static_cast<float>(win.x), static_cast<float>(win.y) };

	for (unsigned int i = 0; i < image.size(); ++i)
	{
		app.lock()->LoadTex(image[i], "_rsc/img/haikei.png");
		pos[i] = { size.x * i, 0.0f };
	}
}

// �`��
void BackGround::Draw(void)
{
	for (unsigned int i = 0; i < pos.size(); ++i)
	{
		app.lock()->DrawTex(image[i], pos[i], size, 0.0f, imagSize);
	}
}

// ����
void BackGround::UpData(void)
{
	for (unsigned int i = 0; i < pos.size(); ++i)
	{
		pos[i] = { std::fmod(cam.lock()->GetPos().x, size.x), 0.0f };
		pos[i].x += size.x * i;
	}
}
