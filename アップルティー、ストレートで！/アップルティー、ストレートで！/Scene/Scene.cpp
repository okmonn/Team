#include "Scene.h"
#include "../Application/Application.h"

// �R���X�g���N�^
Scene::Scene()
{
}

// �f�X�g���N�^
Scene::~Scene()
{
}

// �摜�̓ǂݍ���
void Scene::LoadImg(const std::string & name, const std::string & fileName)
{
	if (image.find(name) == image.end())
	{
		return;
	}

	app.lock()->LoadTex(image[name], fileName);
}

// �摜�̕`��
void Scene::Draw(const std::string & name, const Vec2f & pos, const Vec2f & size, const Vec2f & uvPos, const Vec2f & uvSize, const float & alpha, const bool & turnX, const bool & turnY)
{
	if (image.find(name) == image.end())
	{
		return;
	}

	app.lock()->DrawTex(image[name], pos, size, uvPos, uvSize, alpha, turnX, turnY);
}

// �摜�̍폜
void Scene::Delete(const std::string & name)
{
	if (image.find(name) != image.end())
	{
		app.lock()->DeleteTex(image[name]);
		image.erase(image.find(name));
	}
}

// �摜�̍폜
void Scene::Delete(void)
{
	for (auto itr = image.begin(); itr != image.end(); ++itr)
	{
		app.lock()->DeleteTex(itr->second);
	}
}
