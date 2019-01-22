#include "Chara.h"
#include "../InfoLoader/InfoLoader.h"
#include "../Camera/Camera.h"
#include "../Application/Application.h"
#include <algorithm>

// �R���X�g���N�^
Chara::Chara() :
	state("wait"), index(0), speed(1.0f), flam(0.0f), reverse(false), dead(false)
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
	if (state == "damage")
	{
		hp -= (hp != 0) ? 1 : 0;
	}
}

// �������`�̎擾
std::vector<HitRect<Vec2f>> Chara::GetRect(void)
{
	auto tmp = InfoLoader::Get().GetInfo(info)->at(state).rect[index].hit;
	std::for_each(tmp.begin(), tmp.end(), [&](HitRect<Vec2f>& rect)->void {
		if (reverse == false)
		{
			rect.rect.pos  = pos - rect.rect.pos;
			rect.rect.size = rect.rect.size * size / InfoLoader::Get().GetInfo(info)->at(state).rect[index].anim.size;
		}
		else
		{
			rect.rect.pos  = Vec2f(pos.x + size.x, pos.y) - rect.rect.pos;
			rect.rect.size = Vec2f(-rect.rect.size.x, rect.rect.size.y) * size / InfoLoader::Get().GetInfo(info)->at(state).rect[index].anim.size;
		}
	});
	
	return tmp;
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
	if (flam >= InfoLoader::Get().GetInfo(info)->at(state).animTime)
	{
		index = (index + 1 >= InfoLoader::Get().GetInfo(info)->at(state).rect.size()) ? 0 : ++index;
		flam = 0.0f;
	}
}

// �A�j���[�V�����I���t���O
bool Chara::CheckAnimEnd(void)
{
	if (flam >= InfoLoader::Get().GetInfo(info)->at(state).animTime - 1.0f
		&& index >= InfoLoader::Get().GetInfo(info)->at(state).rect.size() - 1)
	{
		return true;
	}

	return false;
}

// �摜�̕`��
void Chara::DrawImg(const std::string & name, const float & alpha, const bool & turnY)
{
	if (image.find(name) == image.end())
	{
		return;
	}
	app.lock()->DrawTex(image[name], lpos, size,
		InfoLoader::Get().GetInfo(info)->at(state).rect[index].anim.pos, InfoLoader::Get().GetInfo(info)->at(state).rect[index].anim.size,
		alpha, reverse, turnY);
}

// �������`�̕`��
void Chara::DrawRect(void)
{
	for (auto& i : InfoLoader::Get().GetInfo(info)->at(state).rect[index].hit)
	{
		app.lock()->DrawBox(lpos - i.rect.pos, i.rect.size * (size / InfoLoader::Get().GetInfo(info)->at(state).rect[index].anim.size),
			{ 1.0f, 0.0f, 0.0f, 0.5f });
	}
}

// ���[�J�����W�̍X�V
void Chara::UpDataLocal(void)
{
	lpos = pos + cam.lock()->GetPos();
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
