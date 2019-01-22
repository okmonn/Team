#pragma once
#include "Chara.h"

class Enemy :
	public Chara
{
public:
	// コンストラクタ
	Enemy();
	// デストラクタ
	virtual ~Enemy();

protected:
	// プレイヤー
	std::weak_ptr<Chara>pl;
};
