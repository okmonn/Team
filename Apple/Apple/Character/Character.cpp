#include "Character.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// ��`�ǂݍ��ݗp�\����
struct Dummy {
	//��`���W
	Vec2 pos;
	//��`�T�C�Y
	Vec2 size;
};

// �R���X�g���N�^
Character::Character() : 
	flam(0), index(0), st("wait"), reverse(false)
{
	rect.clear();
	animTime.clear();
	img.clear();
}

// �f�X�g���N�^
Character::~Character()
{
}

// �X�e�[�^�X�̃Z�b�g
void Character::SetState(const std::string & st)
{
	if (this->st == st)
	{
		return;
	}

	this->st = st;
	index    = 0;
	flam     = 0.0f;
}

// ��`���̓ǂݍ���
int Character::LoadInfo(const std::string & fileName)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		return -1;
	}

	//�X�e�[�^�X��
	unsigned int stNum = 0;
	fread(&stNum, sizeof(stNum), 1, file);

	Info info{};
	for (unsigned int cnt = 0; cnt < stNum; ++cnt)
	{
		fread(&info.stNameNum, sizeof(info.stNameNum), 1, file);
		info.st.resize(info.stNameNum);
		fread(&info.st[0], info.stNameNum, 1, file);

		fread(&info.animTime, sizeof(info.animTime), 1, file);
		animTime[info.st] = info.animTime;

		fread(&info.animNum, sizeof(info.animNum), 1, file);

		rect[info.st].resize(info.animNum);
		Dummy dummy{};
		for (auto& i : rect[info.st])
		{
			fread(&dummy, sizeof(dummy), 1, file);

			i.pos = { (float)dummy.pos.x,  (float)dummy.pos.y };
			i.size = { (float)dummy.size.x, (float)dummy.size.y };
		}
	}

	fclose(file);

	return 0;
}

// �摜�̓ǂݍ���
void Character::Load(const std::string & fileName, const std::string & name)
{
	if (img.find(name) != img.end())
	{
		return;
	}

	un.lock()->LoadImg(fileName, img[name]);
}

// �A�j���[�V�����Ǘ�
void Character::Animator(const float & speed)
{
	flam += speed;
	if (flam >= animTime[st])
	{
		index = (index + 1 >= rect[st].size()) ? 0 : ++index;
		flam = 0.0f;
	}
}

// �A�j���[�V�����I���m�F
bool Character::CheckAnimEnd(void)
{
	if (flam >= animTime[st] - 1.0f && index >= rect[st].size() - 1)
	{
		return true;
	}

	return false;
}

// �摜�̕`��
void Character::DrawImg(const std::string & name, const float & x, const float & y, const float & sizeX, const float & sizeY, 
	const float & alpha, const bool & turnY)
{
	un.lock()->DrawImg(img[name], x, y, sizeX, sizeY, rect[st][index].pos.x, rect[st][index].pos.y, 
		rect[st][index].size.x, rect[st][index].size.y, alpha, reverse, turnY);
}
