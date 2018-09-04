#pragma once
#include "Scene.h"

class Play :
	public Scene
{
public:
	// コンストラクタ
	Play();
	// デストラクタ
	~Play();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 通常処理
	void NormalUpData(void);

	// 移行処理
	void MoveUpData(void);


	// フェードフラグ
	bool fade;

	// 色
	unsigned int color;

	// 関数ポインタ
	void (Play::*draw)(void);
	void (Play::*updata)(void);
};

