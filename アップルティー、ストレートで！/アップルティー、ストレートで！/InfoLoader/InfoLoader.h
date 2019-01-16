#pragma once
#include "../Typedef.h"
#include <memory>
#include <unordered_map>

class InfoLoader
{
public:
	// デストラクタ
	~InfoLoader();

	// インスタンス変数の取得
	static InfoLoader& Get(void) {
		static InfoLoader instance;
		return instance;
	}

	// 読み込み
	int Load(const std::string& fileName);

	// アニメーション・矩形情報の書き込み
	int WriteInfo(const std::string& fileName, const std::vector<Info>& info);

	// アニメーション時間の取得
	std::shared_ptr<std::unordered_map<std::string, float>> GetAnimTime(const std::string& fileName) {
		return animTime[fileName];
	}
	// アニメーション・矩形情報の取得
	std::shared_ptr<std::unordered_map<std::string, std::vector<Rect>>> GetRect(const std::string& fileName) {
		return rect[fileName];
	}

private:
	// コンストラクタ
	InfoLoader();
	InfoLoader(const InfoLoader&) = delete;
	void operator=(const InfoLoader&) = delete;


	// アニメーション時間
	std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, float>>>animTime;

	// アニメーション・矩形情報
	std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::vector<Rect>>>>rect;
};
