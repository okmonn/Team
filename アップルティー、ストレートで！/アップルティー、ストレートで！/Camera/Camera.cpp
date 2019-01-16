#include "Camera.h"
#include "../Typedef.h"

Camera::Camera()
{
	Create();
}

Camera::~Camera()
{
}
void Camera::Init()
{
	pos = {};
}
void Camera::Create(void)
{
	Init();
}

void Camera::UpData(const Vec2f & pos)
{
	static float i = 0;
	float SCROLL_L = WindowSize.x / 8;
	if (pos.x + i< SCROLL_L)
	{
		i -= (pos.x + i - SCROLL_L) / 16;
	}
	float SCROLL_R = WindowSize.x - (WindowSize.x / 4);

	if (pos.x + i> SCROLL_R)
	{
		i -= (pos.x + i - SCROLL_R) / 16;
	}

	this->pos = { i,0 };




}