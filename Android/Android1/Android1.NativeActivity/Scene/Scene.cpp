#include "Scene.h"
#include "../Load/Loader.h"
#include "DxLib.h"

// コンストラクタ
Scene::Scene() : 
	alpha(255), alphaSpeed(5)
{
	data.clear();
}

// デストラクタ
Scene::~Scene()
{
}

// 画像情報追加
void Scene::AddImage(const std::string & fileName, const Vec2f & size, const Vec2f& pos)
{
	auto start = fileName.find_last_of("/");
	auto end = fileName.find_last_of(".");
	std::string dummy = fileName.substr(start + 1, end - start - 1);

	data[dummy].image = Loader::Get().LoadImg(fileName.c_str());
	data[dummy].pos   = pos;
	data[dummy].size  = size;
}

// 描画
int Scene::DrawGraph(const std::string & name)
{
	return DxLib::DrawGraphF(data[name].pos.x, data[name].pos.y, data[name].image, true);
}

// 自由変形描画
int Scene::DrawModiGraph(const std::string & name, const Vec2f & size)
{
	return DxLib::DrawModiGraphF(data[name].pos.x, data[name].pos.y, (data[name].pos.x + size.x), data[name].pos.y,
		(data[name].pos.x + size.x), (data[name].pos.y + size.y), data[name].pos.x, (data[name].pos.y + size.y),
		data[name].image, true);
}

// 短径・拡大・回転描画
int Scene::DrawRectRotaGraph(const std::string & name, const Vec2f & rectPos, const Vec2f & rectSize, 
	float large, float angle, int turnX, int turnY)
{
	return DxLib::DrawRectRotaGraph2F(
		data[name].pos.x + (data[name].size.x * large / 2.0f), data[name].pos.y + (data[name].size.y * large / 2.0f),
		(int)rectPos.x, (int)rectPos.y, (int)rectSize.x, (int)rectSize.y, 
		data[name].size.x / 2.0f, data[name].size.y / 2.0f, 
		(double)large, (double)angle, data[name].image, true, turnX, turnY);
}
