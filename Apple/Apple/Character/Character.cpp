#include "Character.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// 矩形読み込み用構造体
struct Dummy {
	//矩形座標
	Vec2 pos;
	//矩形サイズ
	Vec2 size;
};

// コンストラクタ
Character::Character() : 
	flam(0), index(0), st("wait"), reverse(false)
{
	rect.clear();
	animTime.clear();
	img.clear();
}

// デストラクタ
Character::~Character()
{
}

// ステータスのセット
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

// 矩形情報の読み込み
int Character::LoadInfo(const std::string & fileName)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		return -1;
	}

	//ステータス数
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

// 画像の読み込み
void Character::Load(const std::string & fileName, const std::string & name)
{
	if (img.find(name) != img.end())
	{
		return;
	}

	un.lock()->LoadImg(fileName, img[name]);
}

// アニメーション管理
void Character::Animator(const float & speed)
{
	flam += speed;
	if (flam >= animTime[st])
	{
		index = (index + 1 >= rect[st].size()) ? 0 : ++index;
		flam = 0.0f;
	}
}

// アニメーション終了確認
bool Character::CheckAnimEnd(void)
{
	if (flam >= animTime[st] - 1.0f && index >= rect[st].size() - 1)
	{
		return true;
	}

	return false;
}

// 画像の描画
void Character::DrawImg(const std::string & name, const float & x, const float & y, const float & sizeX, const float & sizeY, 
	const float & alpha, const bool & turnY)
{
	un.lock()->DrawImg(img[name], x, y, sizeX, sizeY, rect[st][index].pos.x, rect[st][index].pos.y, 
		rect[st][index].size.x, rect[st][index].size.y, alpha, reverse, turnY);
}
