#pragma once
#include "../etc/Typedef.h"
#include "../etc/Vector2.h"
#include <vector>
#include <map>

class Touch
{
	// 三角関数
	struct Trigono
	{
		float sin;
		float cos;
	};

	// 状態
	enum class State
	{
		non,
		touch
	};

public:
	// デストラクタ
	~Touch();

	// インスタンス変数の取得
	static Touch& Get(void) {
		static Touch instance;
		return instance;
	}

	// 描画
	void Draw(void);

	// 処理
	void UpData(void);

	// 角度の取得
	float GetAngle(void);

	// タップの確認
	bool Tap(void);

	// フリックの確認
	bool Flick(void);

	// プレスの確認
	bool Press(void);

	// スワイプの確認
	bool Swaipe(void);

	// サインの取得
	float GetSin(int i) const {
		return tri[i].sin;
	}
	// コサインの取得
	float GetCos(int i) const {
		return tri[i].cos;
	}

	// 現在の座標の取得
	Vec2f GetPos(void) {
		return pos[state];
	}
	// 前座標の取得
	Vec2f GetOldPos(void) const {
		return old;
	}

	// 向きの取得
	DIR GetDir(void) const {
		return dir;
	}

private:
	// コンストラクタ
	Touch();
	Touch(const Touch&) {
	}
	void operator=(const Touch&) {
	}

	// 三角関数のセット
	void SetTrigono(void);

	// 状態のセット
	void SetState(const State& st);

	// 三角形描画
	int DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, unsigned int color, int fill);

	// 円描画
	int DrawCircle(const Vec2f& pos, float radius, unsigned int color, int fill);


	// 三角関数
	std::vector<Trigono>tri;

	// ステータス
	State state;

	// 座標
	std::map<State, Vec2f>pos;

	// 前座標
	Vec2f old_pos;

	// 保険
	Vec2f old;

	// 向き
	DIR dir;

	// 角度
	float angle;

	// タッチしているフレーム
	unsigned int flam;

	// タイムアウトフレーム
	unsigned int timer;
};

