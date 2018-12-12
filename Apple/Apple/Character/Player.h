#pragma once
#include "Character.h"
class Map;

class Player :
	public Character
{
public:
	// コンストラクタ
	Player(std::weak_ptr<Input>in, std::weak_ptr<Union>un,std::weak_ptr<Map>map);
	// デストラクタ
	~Player();

	// 処理
	void UpData(void);

	// 描画
	void Draw(void);

private:
	// ステータス毎の処理のセット
	void SetFunc(void);

	// キーの入力
	bool CheckKey(const int& i);

	// トリガーの入力
	bool Triger(const int& i);

	// 待機時の処理
	void Wait(void);

	// 歩き時の処理
	void Walk(void);

	// 回避時の処理
	void Avoid(void);

	// 攻撃1時の処理
	void Attack1(void);

	// 攻撃2時の処理
	void Attack2(void);

	// スライディング時の処理
	void Sliding(void);

	// ダメージ時の処理
	void Damage(void);


	// 関数ポインタ
	std::unordered_map<std::string, std::function<void(Player*)>>func;
	// マップ情報
	std::weak_ptr<Map>map;
};
