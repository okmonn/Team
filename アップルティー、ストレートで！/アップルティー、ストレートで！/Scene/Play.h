#pragma once
#include "Scene.h"

class Chara;

class Play :
	public Scene
{
public:
	// コンストラクタ
	Play(std::weak_ptr<Application>app);
	// デストラクタ
	~Play();

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

private:
	// 生成
	void Create(void);


	// プレイヤー
	std::shared_ptr<Chara>pl;
};
