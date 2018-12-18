#pragma once
#include "Scene.h"

class Player;
class Enemy;
class Map;

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

private:
	// クラスのインスタンス
	void Create(void);


	// プレイヤー
	std::shared_ptr<Player>pl;
	std::shared_ptr<Enemy>en;

	// マップ
	std::shared_ptr<Map>map;

};
