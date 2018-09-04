#pragma once

// 画面サイズ
#define WINDOW_X 1080
#define WINDOW_Y 1920

// 表示サイズ
#define SHOW_X 608.0f / 1.5f
#define SHOW_Y 1080.0f / 1.5f

// 円周率
#define PI 3.14159264f

// ラジアン変換
#define RAD(X) (X) * (PI / 180.0f)

// アングル変換
#define ANGLE(X) (X) * (18.0f * PI)

// 向き
enum class DIR
{
	non,
	right,
	left,
	up,
	down,
	max
};
