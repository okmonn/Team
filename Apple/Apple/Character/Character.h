#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

class Input;
class Union;

class Character
{
	// 読み込みキャラクターの矩形情報
	struct Rect {
		//矩形座標
		Vec2f pos;
		//矩形サイズ
		Vec2f size;
	};

	// 読み込みキャラクター情報
	struct Info {
		//ステータスの文字列
		unsigned char stNameNum;
		//ステータス
		std::string st;
		//アニメーション時間
		float animTime;
		//いくつアニメーションがあるか
		unsigned char animNum;
	};

public:
	// コンストラクタ
	Character();
	// デストラクタ
	virtual ~Character();

	// 処理
	virtual void UpData(void) = 0;

	// 描画
	virtual void Draw(void) = 0;

	// ワールド座標の取得
	Vec2f GetPos(void) const {
		return pos;
	}
	// ワール座標のセット
	void SetPos(const Vec2f& pos) {
		this->pos = pos;
	}
	// ローカル座標の取得
	Vec2f GetLocal(void) const {
		return local;
	}
	// ローカル座標のセット
	void SetLocal(const Vec2f& local) {
		this->local = local;
	}
	// サイズの取得
	Vec2f GetSize(void) const {
		return size;
	}

	// ステータスの取得
	std::string GetState(void) const {
		return st;
	}
	// ステータスのセット
	void SetState(const std::string& st);

protected:
	// 矩形情報の読み込み
	int LoadInfo(const std::string& fileName);

	// 画像の読み込み
	void Load(const std::string& fileName, const std::string& name);

	// アニメーション管理
	void Animator(const float& speed = 1.0f);

	// アニメーション終了確認
	bool CheckAnimEnd(void);

	// 画像の描画
	void DrawImg(const std::string& name, const float& x, const float& y, const float& sizeX, const float& sizeY,
		const float& alpha = 1.0f, const bool& turnY = false);


	// インプット
	std::weak_ptr<Input>in;

	// ユニオン
	std::weak_ptr<Union>un;

	// ワールド座標
	Vec2f pos;

	// ローカル座標
	Vec2f local;

	// サイズ
	Vec2f size;

	// 移動速度
	float speed;

	// アニメーションフレーム
	float flam;

	// アニメーションインデックス
	unsigned int index;

	// ステータス
	std::string st;

	// 反転フラグ
	bool reverse;

	// 矩形情報
	std::unordered_map<std::string, std::vector<Rect>>rect;

	// アニメーション速度
	std::unordered_map<std::string, float>animTime;

	// 画像ID
	std::unordered_map<std::string, int>img;
};
