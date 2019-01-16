#include "Chara.h"
#include "../Application/Application.h"

// コンストラクタ
Chara::Chara() : 
	state("wait"), index(0), speed(1.0f), flam(0.0f), reverse(false)
{
	image.clear();
	animTime.clear();
	rect.clear();
}

// デストラクタ
Chara::~Chara()
{
}

// ステータスのセット
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

// アニメーション・矩形情報の書き込み
int Chara::WriteInfo(const std::string & fileName, const std::vector<Info> & info)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "wb") != 0)
	{
		return -1;
	}

	unsigned char stNum = static_cast<unsigned char>(info.size());
	fwrite(&stNum, sizeof(stNum), 1, file);

	for (auto& i : info)
	{
		fwrite(&i.stNameNum, sizeof(i.stNameNum), 1, file);
		fwrite(&i.state[0], i.state.size(), 1, file);
		fwrite(&i.animTime, sizeof(i.animTime), 1, file);
		fwrite(&i.animNum, sizeof(i.animNum), 1, file);
		for (auto& n : i.rect)
		{
			fwrite(&n.pos, sizeof(n.pos), 1, file);
			fwrite(&n.size, sizeof(n.size), 1, file);
		}
	}

	fclose(file);

	return 0;
}

// アニメーション・矩形情報の読み込み
int Chara::LoadInfo(const std::string & fileName)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		return -1;
	}

	//ステータス数
	unsigned char num = 0;
	fread(&num, sizeof(num), 1, file);
	for (unsigned char i = 0; i < num; ++i)
	{
		unsigned char stNum = 0;
		fread(&stNum, sizeof(stNum), 1, file);

		std::string st;
		st.resize(stNum);
		fread(&st[0], st.size(), 1, file);

		fread(&animTime[st], sizeof(animTime[st]), 1, file);

		unsigned char animNum = 0;
		fread(&animNum, sizeof(animNum), 1, file);

		Dummy dummy{};
		rect[st].resize(animNum);
		for (auto& i : rect[st])
		{
			fread(&dummy, sizeof(dummy), 1, file);
			i.pos  = { static_cast<float>(dummy.pos.x), static_cast<float>(dummy.pos.y) };
			i.size = { static_cast<float>(dummy.size.x), static_cast<float>(dummy.size.y) };
		}
	}

	fclose(file);

	return 0;
}

// 画像の読み込み
void Chara::LoadImg(const std::string & name, const std::string & fileName)
{
	if (image.find(name) != image.end())
	{
		return;
	}

	app.lock()->LoadTex(image[name], fileName);
}

// アニメーター
void Chara::Animator(const float & speed)
{
	flam += speed;
	if (flam >= animTime[state])
	{
		index = (index + 1 >= rect[state].size()) ? 0 : ++index;
		flam = 0.0f;
	}
}

// アニメーション終了フラグ
bool Chara::CheckAnimEnd(void)
{
	if (flam >= animTime[state] - 1.0f && index >= rect[state].size() - 1)
	{
		return true;
	}

	return false;
}

// 画像の描画
void Chara::DrawImg(const std::string & name, const Vec2f & pos, const Vec2f & size, const Vec2f & uvPos, const Vec2f & uvSize,
	const float & alpha, const bool & turnY)
{
	if (image.find(name) == image.end())
	{
		return;
	}

	app.lock()->DrawTex(image[name], pos, size, uvPos, uvSize, alpha, reverse, turnY);
}

// 画像の削除
void Chara::Delete(const std::string & name)
{
	if (image.find(name) != image.end())
	{
		app.lock()->DeleteTex(image[name]);
		image.erase(image.find(name));
	}
}

// 画像の削除
void Chara::Delete(void)
{
	for (auto itr = image.begin(); itr != image.end(); ++itr)
	{
		app.lock()->DeleteTex(itr->second);
	}
}
