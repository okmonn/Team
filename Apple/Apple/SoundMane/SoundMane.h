#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Effector;
class Sound;

class SoundMane
{
public:
	// デストラクタ
	~SoundMane();

	// インスタンス変数の取得
	static SoundMane& Get(void) {
		static SoundMane instance;
		return instance;
	}

	// サウンドの読み込み
	void Load(const std::string& name, const std::string& fileName);

	// サウンドの再生
	void Play(const std::string& name, const bool& loop = false);

	// サウンドの停止
	void Stop(const std::string& name);

private:
	// コンストラクタ
	SoundMane();
	SoundMane(const SoundMane&) = delete;
	void operator=(const SoundMane&) = delete;


	// サウンド
	std::unordered_map<std::string, std::unique_ptr<Sound>>sound;
};
