#include "Loader.h"
#include "DxLib.h"

// コンストラクタ
Loader::Loader()
{
	image.clear();
	sound.clear();
}

// デストラクタ
Loader::~Loader()
{
	for (auto itr = sound.begin(); itr != sound.end(); ++itr)
	{
		DeleteSoundMem(itr->second);
	}
	for (auto itr = image.begin(); itr != image.end(); ++itr)
	{
		DeleteGraph(itr->second);
	}
}

// 画像読み込み
int Loader::LoadImg(const std::string & fileName)
{
	if (image.find(fileName) != image.end())
	{
		return image[fileName];
	}

	//ダミー宣言
	std::string path;

#ifndef __ANDROID__
	path = "../../Android/Android1/Android1.Packaging/assets/" + fileName;
#else
	path = fileName;
#endif

	image[fileName] = LoadGraph(path.c_str());

	return image[fileName];
}

// サウンド読み込み
int Loader::LoadSnd(const std::string & fileName)
{
	if (sound.find(fileName) != sound.end())
	{
		return sound[fileName];
	}

	//ダミー宣言
	std::string path;

#ifndef __ANDROID__
	path = "../../Android/Android1/Android1.Packaging/assets/" + fileName;
#else
	path = fileName;
#endif

	sound[fileName] = LoadSoundMem(path.c_str());

	return sound[fileName];
}
