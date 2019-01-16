#pragma once
#include "../etc/Vector2.h"
#include <string>
#include <memory>
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
	// ローカル座標の取得
	Vec2f GetLocal(void) const {
		return lpos;
	}
	// サイズの取得
	Vec2f GetSize(void) const {
		return size;
	}

protected:
	// 画像の読み込み
	void LoadImg(const std::string& name, const std::string& fileName);

	// 画像の描画
	void Draw(const std::string& name, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);

	// 画像の削除
	void Delete(const std::string& name);
	void Delete(void);


	// アプリケーション
	std::weak_ptr<Application>app;

	// 画像ID
	std::unordered_map<std::string, int>image;

	// 座標
	Vec2f pos;

	// ローカル座標
	Vec2f lpos;

	// サイズ
	Vec2f size;
};
