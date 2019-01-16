#pragma once
#include "../Typedef.h"
#include <memory>
#include <functional>
#include <unordered_map>

class Application;

class Chara
{
public:
	// コンストラクタ
	Chara();
	// デストラクタ
	virtual ~Chara();

	// 描画
	virtual void Draw(void) = 0;

	// 処理
	virtual void UpData(void) = 0;

	// 座標の取得
	Vec2f GetPos(void) const {
		return pos;
	}
	// 座標のセット
	void SetPos(const Vec2f& pos) {
		this->pos = pos;
	}
	// ローカル座標の取得
	Vec2f GetLocal(void) const {
		return lpos;
	}
	// ローカル座標のセット
	void SetLocal(const Vec2f& pos) {
		lpos = pos;
	}
	// サイズの取得
	Vec2f GetSize(void) const {
		return size;
	}
	// サイズのセット
	void SetSize(const Vec2f& size) {
		this->size = size;
	}
	// ステータスの取得
	std::string GetState(void) const {
		return state;
	}
	// ステータスのセット
	void SetState(const std::string& state);
	// 反転フラグの取得
	bool GetReverse(void) const {
		return reverse;
	}
	// 反転フラグのセット
	void SetReverse(const bool& flag) {
		reverse = flag;
	}

protected:
	// アニメーション・矩形情報の読み込み
	void LoadInfo(const std::string& fileName);

	// 画像の読み込み
	void LoadImg(const std::string& name, const std::string& fileName);

	// アニメーター
	void Animator(const float& speed = 1.0f);

	// アニメーション終了フラグ
	bool CheckAnimEnd(void);

	// 画像の描画
	void DrawImg(const std::string& name, const Vec2f& pos, const Vec2f& size, const float& alpha = 1.0f, const bool& turnY = false);

	// 画像の削除
	void Delete(const std::string& name);
	void Delete(void);


	// アプリケーション
	std::weak_ptr<Application>app;

	// 座標
	Vec2f pos;

	// ローカル座標
	Vec2f lpos;

	// サイズ
	Vec2f size;

	// ステータス
	std::string state;

	// infoファイル名
	std::string info;

	// 配列用インデックス
	unsigned int index;

	// 移動速度
	float speed;

	// フレーム
	float flam;

	// 反転フラグ
	bool reverse;

	// 画像ID
	std::unordered_map<std::string, int>image;
};
