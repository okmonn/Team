#pragma once
#include "../etc/Vector2.h"
#include <vector>
#include <memory>

class Application;

class Map
{
public:
	// コンストラクタ
	Map(std::weak_ptr<Application>app);
	// デストラクタ
	~Map();

	// １マス分のサイズの取得
	Vec2f GetSize(void) const {
		return size;
	}
	// マス数の取得
	Vec2 GetMass(void) const {
		return mass;
	}
	// 地面座標の取得
	float GetGround(void) const {
		return ground;
	}
	// マップデータの取得
	std::vector<int> GetData(void) const {
		return id;
	}

private:
	//	初期化
	void Init(void);


	// アプリケーション
	std::weak_ptr<Application>app;

	// 1マスのサイズ
	Vec2f size;

	// マス数
	Vec2 mass;

	// 地面位置
	float ground;

	// マップデータ
	std::vector<int>id;
};
