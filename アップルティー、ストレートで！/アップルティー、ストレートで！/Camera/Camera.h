#pragma once
#pragma once
#include "../etc/Vector2.h"
#include <memory>
class Application;

class Camera
{
public:
	Camera();
	Camera(std::weak_ptr<Application> app);

	~Camera();

	void Init();
	void SetPos(Vec2f pos) { this->pos = pos; }
	Vec2f GetPos() { return this->pos; }
	
	void UpData(const Vec2f & pos);
private:
	void Create();
	std::weak_ptr<Application> app;
	Vec2f pos;
};