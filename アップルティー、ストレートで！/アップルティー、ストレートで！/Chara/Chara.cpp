#include "Chara.h"
#include "../InfoLoader/InfoLoader.h"
#include "../Application/Application.h"

#include "../Camera/Camera.h"

// �R���X�g���N�^
Chara::Chara() :
	state("wait"), index(0), speed(1.0f), flam(0.0f), reverse(false)
{
	image.clear();
}
// �f�X�g���N�^
Chara::~Chara()
{
}

// �X�e�[�^�X�̃Z�b�g
void Chara::SetState(const std::string & state)
{
	if (this->state == state)
	{
		return;
	}

	this->state = state;
	index       = 0;
	flam        = 0.0f;
}

// �A�j���[�V�����E��`���̓ǂݍ���
void Chara::LoadInfo(const std::string & fileName)
{
	InfoLoader::Get().Load(fileName);
	info = fileName;
}

// �摜�̓ǂݍ���
void Chara::LoadImg(const std::string & name, const std::string & fileName)
{
	if (image.find(name) != image.end())
	{
		return;
	}

	app.lock()->LoadTex(image[name], fileName);
}

// �A�j���[�^�[
void Chara::Animator(const float & speed)
{
	flam += speed;
	if (flam >= InfoLoader::Get().GetAnimTime(info)->at(state))
	{
		index = (index + 1 >= InfoLoader::Get().GetRect(info)->at(state).size()) ? 0 : ++index;
		flam = 0.0f;
	}
}

// �A�j���[�V�����I���t���O
bool Chara::CheckAnimEnd(void)
{
	if (flam >= InfoLoader::Get().GetAnimTime(info)->at(state) - 1.0f && index >= InfoLoader::Get().GetRect(info)->at(state).size() - 1)
	{
		return true;
	}

	return false;
}

// �摜�̕`��
void Chara::DrawImg(const std::string & name, const Vec2f & pos, const Vec2f & size, const float & alpha, const bool & turnY)
{
	if (image.find(name) == image.end())
	{
		return;
	}

	app.lock()->DrawTex(image[name], pos + cam.lock()->GetPos(), size, InfoLoader::Get().GetRect(info)->at(state)[index].pos, InfoLoader::Get().GetRect(info)->at(state)[index].size, alpha, reverse, turnY);
}

// �摜�̍폜
void Chara::Delete(const std::string & name)
{
	if (image.find(name) != image.end())
	{
		app.lock()->DeleteTex(image[name]);
		image.erase(image.find(name));
	}
}

// �摜�̍폜
void Chara::Delete(void)
{
	for (auto itr = image.begin(); itr != image.end(); ++itr)
	{
		app.lock()->DeleteTex(itr->second);
	}
}
