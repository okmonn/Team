#pragma once
#include "Scene.h"

class Over :
	public Scene
{
public:
	// コンストラクタ
	Over();
	// デストラクタ
	~Over();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 通常描画
	void NormalDraw(void);

	// 移行描画
	void MoveDraw(void);

	// 通常処理
	void NormalUpData(void);

	// 移行処理
	void MoveUpData(void);

	// 読み込み
	void Load(void);


	// 関数ポインタ
	void (Over::*draw)(void);
	void (Over::*updata)(void);
};

