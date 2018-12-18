#pragma once
#include "Scene.h"
#include <map>
#include <string>

class Title :
	public Scene
{
public:
	// コンストラクタ
	Title(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// デストラクタ
	~Title();

	// 処理
	void UpData(void);

	// 描画
	void Draw(void);

private:
	// 矩形情報のファイルの作成
	int CreateInfo(const std::string& fileName);
	// アニメーション制御用カウンタ
	// ~-1 非描画、 0~ カウンタが0になるまで減算を続ける
	
	std::map<std::string,int> animCnt;
};

