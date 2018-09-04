#pragma once
#include "../etc/Vector2.h"
#include <vector>
#include <string>
#include <map>

class Obj
{
	//画像データ
	struct Data {
		//画像
		int image;
		//サイズ
		Vec2f size;
		//分割数
		Vec2f rect;
		//アニメーションフレーム
		int animTime;
	};

public:
	// コンストラクタ
	Obj();
	// デストラクタ
	~Obj();

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
	Vec2f GetLocalPos(void) const {
		return lpos;
	}
	// ローカル座標のセット
	void SetLocalPos(const Vec2f& lpos) {
		this->lpos = pos;
	}

	// サイズの取得
	Vec2f GetSize(void) const {
		return size;
	}
	// サイズのセット
	void SetSize(const Vec2f& size) {
		this->size = size;
	}

protected:
	// 画像の追加
	void AddImage(const std::string& fileName, const Vec2f& size, const Vec2f& rect, int animTime);


	// 座標
	Vec2f pos;

	// ローカル座標
	Vec2f lpos;

	// サイズ
	Vec2f size;

	// HP
	int hp;

	// 経過フレーム
	int flam;

	// 画像データ
	std::map<std::string, Data>data;
};
