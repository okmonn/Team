#pragma once
#include "../Obj.h"

class Player :
	public Obj
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 読み込み
	void Load(void);
};

