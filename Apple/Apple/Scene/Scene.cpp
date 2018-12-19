#include "Scene.h"
#include "../Union/Union.h"
#include "../etc/Typedef.h"

// コンストラクタ
Scene::Scene()
{
	img.clear();
}

// デストラクタ
Scene::~Scene()
{
}

// 画像の読み込み
void Scene::Load(const std::string & fileName, const std::string & name)
{
	if (img.find(name) != img.end())
	{
		return;
	}

	un.lock()->LoadImg(fileName, img[name]);
}

// 画像の描画
void Scene::DrawImg(const std::string & name, const float & x, const float & y, const float & sizeX, const float & sizeY, 
	const float & rectX, const float & rectY, const float & rectSizeX, const float & rectSizeY, 
	const float & alpha, const bool & turnX, const bool & turnY)
{
	un.lock()->DrawImg(img[name], x, y, sizeX, sizeY, rectX, rectY, rectSizeX, rectSizeY, alpha, turnX, turnY);
}

// 画像の削除
void Scene::Delete(void)
{
	for (auto itr = img.begin(); itr != img.end(); ++itr)
	{
		un.lock()->DeleteImg(itr->second);
	}
}

int Scene::Screen_FadeIn(const float& s,const int& color)
{

	if (s < 0)
	{
		return -1;
	}
	float Rc = (color >> 16 & 0xff) / 255.0f;
	float Gc = (color >> 8 & 0xff) / 255.0f;
	float Bc = (color & 0xff) / 255.0f;

	static float alpha = 0;
	static float speed = 0;
	speed = s;
	alpha+= speed;
	un.lock()->DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y,
		Rc, Gc, Bc, 1-alpha);
	
	if (alpha >= 1)
	{
		alpha = 0;
		return 1;
	}
	
	return 0;
}

int Scene::Screen_FadeOut(const float& s, const int& color)
{
	if (s < 0)
	{
		return -1;
	}
	float Rc = (color >> 16 & 0xff) / 255.0f;
	float Gc = (color >> 8 & 0xff) / 255.0f;
	float Bc = (color & 0xff) / 255.0f;

	static float alpha = 0;
	static float speed = 0;
	speed = s;
	alpha += speed;
	un.lock()->DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y,
		Rc, Gc, Bc, alpha);

	if (alpha >= 1)
	{
		alpha = 0;
		return 1;
	}

	return 0;
}
