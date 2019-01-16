#pragma once
#include "etc/Vector2.h"
#include <string>
#include <vector>

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
