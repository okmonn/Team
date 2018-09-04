#pragma once
#include "../etc/Vector2.h"
#include <map>
#include <string>

class Scene
{
	//画像情報
	struct Data {
		//画像データ
		int image;
		//座標
		Vec2f pos;
		//サイズ
		Vec2f size;
	};
public:
	// コンストラクタ
	Scene();
	// デストラクタ
	virtual ~Scene();

	// 描画
	virtual void Draw(void) = 0;

	// 処理
	virtual void UpData(void) = 0;

protected:
	// 画像情報追加
	void AddImage(const std::string& fileName, const Vec2f& size, const Vec2f& pos = 0.0f);

	// 描画
	int DrawGraph(const std::string& name);

	// 自由変形描画
	int DrawModiGraph(const std::string& name, const Vec2f& size);

	// 短径・拡大・回転描画
	int DrawRectRotaGraph(const std::string& name, const Vec2f& rectPos, const Vec2f& rectSize, float large = 1.0f, float angle = 0.0f, 
		int turnX = 0, int turnY = 0);


	// 画像情報
	std::map<std::string, Data>data;

	// アルファ値
	int alpha;

	// アルファ速度
	int alphaSpeed;
};

