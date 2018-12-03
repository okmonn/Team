#pragma once
#include "Scene.h"

class Result :
	public Scene
{
public:
	// コンストラクタ
	Result(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// デストラクタ
	~Result();

	// 処理
	void UpData(void);

	// 描画
	void Draw(void);

private:

};
