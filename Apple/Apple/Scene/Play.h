#pragma once
#include "Scene.h"

class Player;

class Play :
	public Scene
{
public:
	// コンストラクタ
	Play(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// デストラクタ
	~Play();

	// 処理
	void UpData(void);

	// 描画
	void Draw(void);
	int a;

private:
	// クラスのインスタンス
	void Create(void);


	// プレイヤー
	std::shared_ptr<Player>pl;
};
