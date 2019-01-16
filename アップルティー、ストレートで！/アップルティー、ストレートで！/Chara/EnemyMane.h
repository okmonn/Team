#pragma once
#include "../etc/Vector2.h"
#include <list>
#include <string>
#include <memory>
#include <unordered_map>

class Application;
class Enemy;

class EnemyMane
{
public:
	// デストラクタ
	~EnemyMane();

	// インスタンス変数の取得
	static EnemyMane& Get(void) {
		static EnemyMane instance;
		return instance;
	}

	// 敵の生成
	void Create(const std::string& type, const Vec2f& pos, const Vec2f& size);

	// リストのクリア
	void ClearEnemy(void);

	// オリジンのクリア
	void ClearOrigin(void);

private:
	// コンストラクタ
	EnemyMane();
	EnemyMane(const EnemyMane&) = delete;
	void operator=(const EnemyMane&) = delete;

	// 初期化
	void Init(void);


	// 敵のオリジン
	std::unordered_map<std::string, std::shared_ptr<Enemy>>origin;

	// 敵
	std::list<std::shared_ptr<Enemy>>enemy;
};
