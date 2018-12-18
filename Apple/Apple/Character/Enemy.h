#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	// コンストラクタ
	Enemy(Map map);
	// デストラクタ
	virtual ~Enemy();

protected:
	// 待機時の処理
	void Wait(void);

	// 移動時の処理
	void Walk(void);

	// 攻撃時の処理
	void Attack(void);

	// ダメージ時の処理
	void Damage(void);
};