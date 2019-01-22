#pragma once
#include <string>
#include <memory>
#include <unordered_map>

template<typename T>
class Vector2;
typedef Vector2<float> Vec2f;
class Application;

class Scene
{
public:
	// �R���X�g���N�^
	Scene();
	// �f�X�g���N�^
	virtual ~Scene();

	// �`��
	virtual void Draw(void) = 0;

	// ����
	virtual void UpData(void) = 0;

protected:
	// �摜�̓ǂݍ���
	void LoadImg(const std::string& name, const std::string& fileName);

	// �摜�̕`��
	void DrawImg(const std::string& name, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);

	// �摜�̍폜
	void Delete(const std::string& name);
	void Delete(void);


	// �A�v���P�[�V����
	std::weak_ptr<Application>app;

	// �摜�n���h��
	std::unordered_map<std::string, int>image;
};
