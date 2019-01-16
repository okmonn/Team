#pragma once
#include <DirectXMath.h>

namespace prm {
	// ���W
	struct Vertex
	{
		//���W
		DirectX::XMFLOAT3 pos;
		//�F
		DirectX::XMFLOAT4 color;
	};
	// �^�C�v
	enum class PrimitiveType {
		point = 1,
		line,
		triangle
	};
}
