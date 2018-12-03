#pragma once
#include "Character.h"

class Player :
	public Character
{
public:
	// コンストラクタ
	Player(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// デストラクタ
	~Player();

	// 処理
	void UpData(void);

	// 描画
	void Draw(void);

private:
	// キーの入力
	bool CheckKey(const int& i);

	// トリガーの入力
	bool Triger(const int& i);

	// 待機時の処理
	void Wait(void);

	// 歩き時の処理
	void Walk(void);


	// 関数ポインタ
	void(Player::*updata)(void);
};
