#include "Camera.h"
#include "../Application/Application.h"
#include "../Typedef.h"

Camera::Camera()
{
}
Camera::Camera(std::weak_ptr<Application> app)
{
	this->app = app;

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
	float SCROLL_L = app.lock()->GetWinSize().x / 8;
	if (pos.x + i< SCROLL_L)
	{
		i -= (pos.x + i - SCROLL_L) / 16;
	}
	float SCROLL_R = app.lock()->GetWinSize().x - (app.lock()->GetWinSize().x / 4);

	if (pos.x + i> SCROLL_R)
	{
		i -= (pos.x + i - SCROLL_R) / 16;
	}

	this->pos = { i,0 };




}