#include "Camera.h"

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
	if (pos.x + i< 110)
	{
		i -= (pos.x + i - 110) / 16;
	}
	if (pos.x + i> 100)
	{
		i -= (pos.x + i - 100) / 4;
	}

	this->pos = { i,0 };




}