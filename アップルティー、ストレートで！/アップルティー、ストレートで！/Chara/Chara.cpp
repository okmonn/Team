#include "Chara.h"
#include "../InfoLoader/InfoLoader.h"
#include "../Application/Application.h"

#include "../Camera/Camera.h"

// コンストラクタ
Chara::Chara() :
	state("wait"), index(0), speed(1.0f), flam(0.0f), reverse(false)
{
	image.clear();
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

// アニメーション・矩形情報の読み込み
void Chara::LoadInfo(const std::string & fileName)
{
	InfoLoader::Get().Load(fileName);
	info = fileName;
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
	if (flam >= InfoLoader::Get().GetAnimTime(info)->at(state))
	{
		index = (index + 1 >= InfoLoader::Get().GetRect(info)->at(state).size()) ? 0 : ++index;
		flam = 0.0f;
	}
}

// アニメーション終了フラグ
bool Chara::CheckAnimEnd(void)
{
	if (flam >= InfoLoader::Get().GetAnimTime(info)->at(state) - 1.0f && index >= InfoLoader::Get().GetRect(info)->at(state).size() - 1)
	{
		return true;
	}

	return false;
}

// 画像の描画
void Chara::DrawImg(const std::string & name, const Vec2f & pos, const Vec2f & size, const float & alpha, const bool & turnY)
{
	if (image.find(name) == image.end())
	{
		return;
	}

	app.lock()->DrawTex(image[name], pos + cam.lock()->GetPos(), size, InfoLoader::Get().GetRect(info)->at(state)[index].pos, InfoLoader::Get().GetRect(info)->at(state)[index].size, alpha, reverse, turnY);
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
