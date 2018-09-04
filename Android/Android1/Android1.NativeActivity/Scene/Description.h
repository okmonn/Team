#pragma once
#include "Scene.h"

class Description :
	public Scene
{
public:
	// コンストラクタ
	Description();
	// デストラクタ
	~Description();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 読み込み
	void Load(void);

	// 通常処理
	void NormalUpData(void);

	// 移行処理
	void MoveUpData(void);


	// 配列番号
	int index;

	// 関数ポインタ
	void (Description::*func)(void);
};

