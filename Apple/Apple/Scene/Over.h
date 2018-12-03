#pragma once
#include "Scene.h"

class Over :
	public Scene
{
public:
	// コンストラクタ
	Over(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// デストラクタ
	~Over();

	// 処理
	void UpData(void);

	// 描画
	void Draw(void);

private:

};
