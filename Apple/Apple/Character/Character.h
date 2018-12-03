#pragma once
#include <map>
#include <string>
#include <memory>

class Input;
class Union;

class Character
{
public:
	// �R���X�g���N�^
	Character();
	// �f�X�g���N�^
	virtual ~Character();

	// ����
	virtual void UpData(void) = 0;

	// �`��
	virtual void Draw(void) = 0;

protected:
	// �摜�̓ǂݍ���
	void Load(const std::string& fileName, const std::string& name);

	// �摜�̕`��
	void DrawImg(const std::string& name, const float& x, const float& y, const float& sizeX, const float& sizeY,
		const float& rectX, const float& rectY, const float& rectSizeX, const float& rectSizeY,
		const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);


	// �C���v�b�g
	std::weak_ptr<Input>in;

	// ���j�I��
	std::weak_ptr<Union>un;

	// �摜ID
	std::map<std::string, int>img;
};
