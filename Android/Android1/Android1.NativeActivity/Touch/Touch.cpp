#include "Touch.h"
#include "../etc/Typedef.h"
#include "DxLib.h"
#include <math.h>
#include <algorithm>

// 最大角度
#define ANGLE_MAX 360

// 半径
const float radius = 25.0f;

// 座標のオフセット
const float offset = 50.0f;

// タップ時間
const unsigned int tapTime = 10;

// タイムアウト
const unsigned int timeOut = 10;

// コンストラクタ
Touch::Touch() :
	state(State::non), old_pos(-1.0f), old(-1.0f), dir(DIR::non), angle(0), flam(0), timer(0)
{
	tri.clear();
	pos.clear();

	pos[State::non] = -1.0f;
	pos[State::touch] = -1.0f;

	SetTrigono();
}

// デストラクタ
Touch::~Touch()
{
}

// 三角関数のセット
void Touch::SetTrigono(void)
{
	for (int i = 0; i < ANGLE_MAX; ++i)
	{
		tri.push_back({ std::sin(RAD(i)), std::cos(RAD(i)) });
	}
}

// 状態のセット
void Touch::SetState(const State& st)
{
	state = st;
	flam = 0;
	for (auto itr = pos.begin(); itr != pos.end(); ++itr)
	{
		itr->second = -1.0f;
	}
	old_pos = -1.0f;
}

// 三角形描画
int Touch::DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, unsigned int color, int fill)
{
	return DxLib::DrawTriangle((int)(pos1.x), (int)(pos1.y), (int)(pos2.x), (int)(pos2.y), (int)(pos3.x), (int)(pos3.y), color, fill);
}

// 円描画
int Touch::DrawCircle(const Vec2f & pos, float radius, unsigned int color, int fill)
{
	return DxLib::DrawCircle((int)pos.x, (int)pos.y, (int)radius, color, fill);
}

// 描画
void Touch::Draw(void)
{
	float angle = GetAngle();

	if (pos[State::touch] != -1 && pos[State::non] != -1)
	{
		int n = (int)angle;

		DrawTriangle(
			pos[State::touch],
			{ pos[State::non].x - tri[n].cos * radius, pos[State::non].y + tri[n].sin * radius },
			{ pos[State::non].x + tri[n].cos * radius, pos[State::non].y - tri[n].sin * radius },
			GetColor(255, 255, 255), true);

		DrawTriangle(
			{ pos[State::touch].x - tri[n].cos * radius, pos[State::touch].y + tri[n].sin * radius },
			{ pos[State::non].x - tri[n].cos * radius * 2.0f, pos[State::non].y + tri[n].sin * radius * 2.0f },
			{ pos[State::non].x + tri[n].cos * radius * 2.0f, pos[State::non].y - tri[n].sin * radius * 2.0f },
			GetColor(255, 255, 255), true);

		DrawTriangle(
			{ pos[State::touch].x + tri[n].cos * radius, pos[State::touch].y - tri[n].sin * radius },
			{ pos[State::non].x - tri[n].cos * radius * 2.0f, pos[State::non].y + tri[n].sin * radius * 2.0f },
			{ pos[State::non].x + tri[n].cos * radius * 2.0f, pos[State::non].y - tri[n].sin * radius * 2.0f },
			GetColor(255, 255, 255), true);

		DrawTriangle(
			pos[State::non],
			{ pos[State::touch].x - tri[n].cos * radius, pos[State::touch].y + tri[n].sin * radius },
			{ pos[State::touch].x + tri[n].cos * radius, pos[State::touch].y - tri[n].sin * radius },
			GetColor(255, 255, 255), true);

		DrawCircle(pos[State::non], radius * 2, GetColor(255, 255, 255), true);
		DrawCircle(pos[State::touch], radius, GetColor(255, 255, 255), true);
	}
}

// 処理
void Touch::UpData(void)
{
	old_pos = pos[State::touch];
	if (old_pos != -1.0f)
	{
		old = old_pos;
	}
#ifndef __ANDROID__
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		Vec2 n = 0;
		if (state != State::non)
		{
			GetMousePoint(&n.x, &n.y);

			if ((0 < n.x && n.x < WINDOW_X) && (0 < n.y && n.y < WINDOW_Y))
			{
				pos[State::touch].x = static_cast<float>(n.x);
				pos[State::touch].y = static_cast<float>(n.y);
			}
		}
		else
		{
			SetState(State::touch);
			GetMousePoint(&n.x, &n.y);

			if ((0 < n.x && n.x < WINDOW_X) && (0 < n.y && n.y < WINDOW_Y))
			{
				pos[State::non].x = static_cast<float>(n.x);
				pos[State::non].y = static_cast<float>(n.y);
			}
		}
		++flam;
	}
#else
	if (GetTouchInputNum() > 0)
	{
		Vec2 n = 0;
		if (state != State::non)
		{
			GetTouchInput(0, &n.x, &n.y);

			if ((0 < n.x && n.x < WINDOW_X) && (0 < n.y && n.y < WINDOW_Y))
			{
				pos[State::touch].x = static_cast<float>(n.x);
				pos[State::touch].y = static_cast<float>(n.y);
			}
		}
		else
		{
			SetState(State::touch);
			GetTouchInput(0, &n.x, &n.y);

			if ((0 < n.x && n.x < WINDOW_X) && (0 < n.y && n.y < WINDOW_Y))
			{
				pos[State::non].x = static_cast<float>(n.x);
				pos[State::non].y = static_cast<float>(n.y);
			}
		}
		++flam;
	}
#endif
	else
	{
		pos[State::touch] = -1;
		++timer;
		if (timer >= timeOut)
		{
			SetState(State::non);
			timer = 0;
		}
	}
}

// 角度の取得
float Touch::GetAngle(void)
{
	if (pos[State::non] == -1.0f || old_pos == -1)
	{
		return 0.0f;
	}

	float angle = ANGLE(std::atan2(old_pos.x - pos[State::non].x, old_pos.y - pos[State::non].y));

	float tmp = 0.0f;
	if (ANGLE(angle) < 0.0f)
	{
		tmp = static_cast<float>(ANGLE_MAX) + angle;
		if (tmp >= static_cast<float>(ANGLE_MAX))
		{
			tmp = 0;
		}
	}
	else
	{
		tmp = angle;
	}

	return tmp;
}

// タップの確認
bool Touch::Tap(void)
{
	float x = std::abs(pos[State::non].x - old_pos.x);
	float y = std::abs(pos[State::non].y - old_pos.y);

#ifndef __ANDROID__
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0
		&& flam <= tapTime && pos[State::touch] == -1.0f && old_pos != -1.0f
		&& x <= offset && y <= offset)
	{
		SetState(State::non);
		dir = DIR::non;
		return true;
	}
#else
	if (GetTouchInputNum() <= 0
		&& flam <= tapTime && pos[State::touch] == -1.0f && old_pos != -1.0f
		&& x <= offset && y <= offset)
	{
		SetState(State::non);
		dir = DIR::non;
		return true;
	}
#endif
	return false;
}

// フリックの確認
bool Touch::Flick(void)
{
	float x = std::abs(pos[State::non].x - old_pos.x);
	float y = std::abs(pos[State::non].y - old_pos.y);

#ifndef __ANDROID__
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0
		&& flam <= tapTime && pos[State::touch] == -1.0f && old_pos != -1.0f
		&& (x > offset || y > offset))
	{
		float tmp = GetAngle();

		if (pos[State::non].x < old_pos.x
			&& 45.0f <= tmp && tmp < 135.0f)
		{
			dir = DIR::right;
		}
		else if (pos[State::non].y > old_pos.y
			&& 135.0f <= tmp && tmp < 225.0f)
		{
			dir = DIR::up;
		}
		else if (pos[State::non].x > old_pos.x
			&& 225.0f <= tmp && tmp < 315.0f)
		{
			dir = DIR::left;
		}
		else
		{
			dir = DIR::down;
		}
		angle = tmp;
		SetState(State::non);
		return true;
	}
#else
	if (GetTouchInputNum() <= 0
		&& flam <= tapTime && pos[State::touch] == -1.0f && old_pos != -1.0f
		&& (x > offset || y > offset))
	{
		float tmp = GetAngle();

		if (pos[State::non].x < old_pos.x
			&& 45.0f <= tmp && tmp < 135.0f)
		{
			dir = DIR::right;
		}
		else if (pos[State::non].y > old_pos.y
			&& 135.0f <= tmp && tmp < 225.0f)
		{
			dir = DIR::up;
		}
		else if (pos[State::non].x > old_pos.x
			&& 225.0f <= tmp && tmp < 315.0f)
		{
			dir = DIR::left;
		}
		else
		{
			dir = DIR::down;
		}
		angle = tmp;
		SetState(State::non);
		return true;
	}
#endif

	return false;
}

// プレスの確認
bool Touch::Press(void)
{
	float x = abs(pos[State::non].x - pos[State::touch].x);
	float y = abs(pos[State::non].y - pos[State::touch].y);

#ifndef __ANDROID__
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0
		&& flam > tapTime && pos[State::touch] != -1.0f && old_pos != -1.0f
		&& x <= offset && y <= offset)
	{
		float tmp = GetAngle();
		dir = DIR::non;
		angle = tmp;

		return true;
	}
#else
	if (GetTouchInputNum() > 0
		&& flam > tapTime && pos[State::touch] != -1.0f && old_pos != -1.0f
		&& x <= offset && y <= offset)
	{
		float tmp = GetAngle();
		dir = DIR::non;
		angle = tmp;

		return true;
	}
#endif
	if (flam > tapTime && pos[State::touch] == -1.0f
		&& old_pos != -1.0f)
	{
		dir = DIR::non;
		SetState(State::non);
	}

	return false;
}

// スワイプの確認
bool Touch::Swaipe(void)
{
	float x = abs(pos[State::non].x - pos[State::touch].x);
	float y = abs(pos[State::non].y - pos[State::touch].y);

#ifndef __ANDROID__
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0
		&& flam > tapTime && pos[State::touch] != -1.0f && old_pos != -1.0f
		&& (x > offset || y > offset))
	{
		float tmp = GetAngle();

		if (pos[State::non].x < old_pos.x
			&& 45.0f <= tmp && tmp < 135.0f)
		{
			dir = DIR::right;
		}
		else if (pos[State::non].y > old_pos.y
			&& 135.0f <= tmp && tmp < 225.0f)
		{
			dir = DIR::up;
		}
		else if (pos[State::non].x > old_pos.x
			&& 225.0f <= tmp && tmp < 315.0f)
		{
			dir = DIR::left;
		}
		else
		{
			dir = DIR::down;
		}
		angle = tmp;

		return true;
	}
#else
	if (GetTouchInputNum() > 0
		&& flam > tapTime && pos[State::touch] != -1.0f && old_pos != -1.0f
		&& (x > offset || y > offset))
	{
		float tmp = GetAngle();

		if (pos[State::non].x < old_pos.x
			&& 45.0f <= tmp && tmp < 135.0f)
		{
			dir = DIR::right;
		}
		else if (pos[State::non].y > old_pos.y
			&& 135.0f <= tmp && tmp < 225.0f)
		{
			dir = DIR::up;
		}
		else if (pos[State::non].x > old_pos.x
			&& 225.0f <= tmp && tmp < 315.0f)
		{
			dir = DIR::left;
		}
		else
		{
			dir = DIR::down;
		}
		angle = tmp;

		return true;
	}
#endif
	if (flam > tapTime && pos[State::touch] == -1.0f
		&& old_pos != -1.0f)
	{
		dir = DIR::non;
		SetState(State::non);
	}

	return false;
}
