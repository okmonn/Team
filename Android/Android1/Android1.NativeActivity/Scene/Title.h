#pragma once
#include "Scene.h"

class Title :
	public Scene
{
public:
	// コンストラクタ
	Title();
	// デストラクタ
	~Title();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 画像読み込み
	void Load(void);

	// 通常描画
	void NormalDraw(void);

	// 移行描画
	void MoveDraw(void);

	// 通常処理
	void NormalUpData(void);

	// 移行処理
	void MoveUpData(void);

	
	// 拡大率
	float large;

	// 関数ポインタ
	void (Title::*update)(void);
	void (Title::*draw)(void);
};

