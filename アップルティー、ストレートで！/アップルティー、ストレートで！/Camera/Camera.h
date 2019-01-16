#pragma once

#pragma once
#include "../etc/Vector2.h"

class Camera
{
public:
	static Camera& Get(void) {
		static Camera instance;
		return instance;
	}

	void Init();
	void SetPos(Vec2f pos) { this->pos = pos; }
	Vec2f GetPos() { return this->pos; }
	void UpData(const Vec2f & pos);

private:
	void Create();
	Camera();
	~Camera();
	Vec2f pos;
};