#include "Over.h"
#include "../Game/Game.h"
#include "Title.h"
#include "../etc/Typedef.h"
#include "DxLib.h"

// �ړ����x
const float speed = 10.0f;

// �R���X�g���N�^
Over::Over()
{
	alpha = 0;
	draw = &Over::NormalDraw;
	updata = &Over::NormalUpData;

	Load();
}

// �f�X�g���N�^
Over::~Over()
{
}

// �ǂݍ���
void Over::Load(void)
{
	AddImage("Over/overback.png", { 1080.0f, 1920.0f }, {0.0f, -1920.0f});
	AddImage("Over/over.png", { 605.0f,  194.0f }, {WINDOW_X / 2 - 605 / 2, WINDOW_Y / 2 - 194 / 2});
}

// �ʏ�`��
void Over::NormalDraw(void)
{
	DrawGraph("overback");
}

// �ڍs�`��
void Over::MoveDraw(void)
{
	DrawGraph("overback");
	DrawGraph("over");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

// �`��
void Over::Draw(void)
{
	(this->*draw)();
}

// �ʏ폈��
void Over::NormalUpData(void)
{
	if (data["overback"].pos.y < 0)
	{
		data["overback"].pos.y += speed;
	}
	else
	{
		draw = &Over::MoveDraw;
		updata = &Over::MoveUpData;
	}
}

// �ڍs����
void Over::MoveUpData(void)
{
	if (alpha < 255)
	{
		alpha += alphaSpeed / 2;
	}
	else
	{
		Game::Get().ChangeScene(new Title());
	}
}

// ����
void Over::UpData(void)
{
	(this->*updata)();
}
