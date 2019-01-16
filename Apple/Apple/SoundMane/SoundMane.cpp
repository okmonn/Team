#include "SoundMane.h"
#include "../Sound/Sound.h"

// コンストラクタ
SoundMane::SoundMane()
{
	sound.clear();
}

// デストラクタ
SoundMane::~SoundMane()
{
	sound.clear();
}

// サウンドの読み込み
void SoundMane::Load(const std::string & name, const std::string & fileName)
{
	if (sound.find(name) != sound.end())
	{
		return;
	}

	sound[name] = std::make_unique<Sound>();
	sound[name]->Load(fileName);
}

// サウンドの再生
void SoundMane::Play(const std::string & name, const bool & loop)
{
	if (sound.find(name) == sound.end())
	{
		return;
	}
	sound[name]->Play(loop);
}

// サウンドの停止
void SoundMane::Stop(const std::string & name)
{
	if (sound.find(name) == sound.end())
	{
		return;
	}
	sound[name]->Stop();
}
