#pragma once
#include "Chara.h"

class Player :
	public Chara
{
public:
	// コンストラクタ
	Player(std::weak_ptr<Application>app);
	// デストラクタ
	~Player();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:

};
