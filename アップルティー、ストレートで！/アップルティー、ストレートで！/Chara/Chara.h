#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

class Application;

class Chara
{
	// ダミー用構造体
	struct Dummy {
		//座標
		Vec2 pos;
		//サイズ
		Vec2 size;
	};

	// アニメーション・矩形情報
	struct Info {
		//ステータス名の文字数
		unsigned char stNameNum;
		//ステータス名
		std::string state;
		//アニメーション時間
		float animTime;
		//アニメーション数
		unsigned char animNum;
		//矩形情報
		std::vector<Dummy>rect;
	};

	// アニメーション・矩形情報
	struct Rect {
		//座標
		Vec2f pos;
		//サイズ
		Vec2f size;
	};

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
	// アニメーション・矩形情報の書き込み
	int WriteInfo(const std::string& fileName, const std::vector<Info>& info);

	// アニメーション・矩形情報の読み込み
	int LoadInfo(const std::string& fileName);

	// 画像の読み込み
	void LoadImg(const std::string& name, const std::string& fileName);

	// アニメーター
	void Animator(const float& speed = 1.0f);

	// アニメーション終了フラグ
	bool CheckAnimEnd(void);

	// 画像の描画
	void DrawImg(const std::string& name, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& alpha = 1.0f, const bool& turnY = false);

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

	// アニメーション時間
	std::unordered_map<std::string, float>animTime;

	// アニメーション・矩形情報
	std::unordered_map<std::string, std::vector<Rect>>rect;
};
