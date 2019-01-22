#pragma once
#include "Chara.h"

class Player;

class Enemy :
	public Chara
{
public:
	// コンストラクタ
	Enemy();
	// デストラクタ
	virtual ~Enemy();

protected:
	// ローカル座標の更新
	void UpDataLocal(void);

	// ランダムなターゲット座標の生成
	Vec2f GetRandomPos(const Vec2f& range);

	// あたり判定
	bool CheckHit(void);


	// プレイヤー
	std::weak_ptr<Player>pl;

	// ターゲット座標
	Vec2f target;
};
