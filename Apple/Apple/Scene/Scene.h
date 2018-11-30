#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Input;
class Union;

class Scene
{
public:
	// コンストラクタ
	Scene();
	// デストラクタ
	virtual ~Scene();

	// 処理
	virtual void UpData(void) = 0;

	// 描画
	virtual void Draw(void) = 0;

protected:
	// 画像の読み込み
	void Load(const std::string& fileName, const std::string& name);

	// 画像の描画
	void DrawImg(const std::string& name, const float& x, const float& y, const float& sizeX, const float& sizeY,
		const float& rectX, const float& rectY, const float& rectSizeX, const float& rectSizeY,
		const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);


	// インプット
	std::weak_ptr<Input>in;

	// ユニオン
	std::weak_ptr<Union>un;

	// 画像のID
	std::unordered_map<std::string, int>img;
};
