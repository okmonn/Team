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

};
