#include "Character.h"
#include "../Input/Input.h"
#include "../Union/Union.h"

// コンストラクタ
Character::Character()
{
	img.clear();
}

// デストラクタ
Character::~Character()
{
}

// 画像の読み込み
void Character::Load(const std::string & fileName, const std::string & name)
{
	if (img.find(name) != img.end())
	{
		return;
	}

	un.lock()->LoadImg(fileName, img[name]);
}

// 画像の描画
void Character::DrawImg(const std::string & name, const float & x, const float & y, const float & sizeX, const float & sizeY, 
	const float & rectX, const float & rectY, const float & rectSizeX, const float & rectSizeY, 
	const float & alpha, const bool & turnX, const bool & turnY)
{
	un.lock()->DrawImg(img[name], x, y, sizeX, sizeY, rectX, rectY, rectSizeX, rectSizeY, alpha, turnX, turnY);
}
