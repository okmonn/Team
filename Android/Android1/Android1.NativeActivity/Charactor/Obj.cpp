#include "Obj.h"
#include "../Load/Loader.h"

// コンストラクタ
Obj::Obj() : 
	pos(0.0f), lpos(0.0f), size(0.0f), hp(0), flam(0)
{
	data.clear();
}

// デストラクタ
Obj::~Obj()
{
}

// 画像の追加
void Obj::AddImage(const std::string& fileName, const Vec2f& size, const Vec2f& rect, int animTime)
{
	auto start = fileName.find_last_of("/");
	auto end = fileName.find_last_of(".");
	std::string dummy = fileName.substr(start + 1, end - start - 1);

	data[dummy].image = Loader::Get().LoadImg(fileName.c_str());
	data[dummy].size  = size;
	data[dummy].rect = rect;
	data[dummy].animTime = animTime;
}
