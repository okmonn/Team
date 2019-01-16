#pragma once
#include "Enemy.h"

class Enemy1 :
	public Enemy
{
public:
	// コンストラクタ
	Enemy1(std::weak_ptr<Application>app, const Vec2f& pos = 0.0f, const Vec2f& size = 100.0f);
	// デストラクタ
	~Enemy1();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:

};
