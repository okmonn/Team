#pragma once
#include "Scene.h"

class Clear :
	public Scene
{
public:
	// コンストラクタ
	Clear();
	// デストラクタ
	~Clear();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:

};

