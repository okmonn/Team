#pragma once
#include <string>
#include <map>
#include <vector>

class Loader
{
public:
	// デストラクタ
	~Loader();

	// インスタンス変数の取得
	static Loader& Get(void) {
		static Loader instance;
		return instance;
	}

	// 画像読み込み
	int LoadImg(const std::string& fileName);

	// サウンド読み込み
	int LoadSnd(const std::string& fileName);

private:
	// コンストラクタ
	Loader();
	Loader(const Loader&) {
	}
	void operator=(const Loader&) {
	}


	// 画像データ
	std::map<std::string, int>image;

	// サウンドデータ
	std::map<std::string, int>sound;
};

