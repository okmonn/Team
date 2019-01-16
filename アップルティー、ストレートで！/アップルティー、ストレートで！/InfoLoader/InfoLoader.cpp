#include "InfoLoader.h"

// コンストラクタ
InfoLoader::InfoLoader()
{
	animTime.clear();
	rect.clear();
}

// デストラクタ
InfoLoader::~InfoLoader()
{
}

// 読み込み
int InfoLoader::Load(const std::string & fileName)
{
	if (animTime.find(fileName) != animTime.end())
	{
		return 0;
	}

	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		return -1;
	}

	animTime[fileName] = std::make_shared<std::unordered_map<std::string, float>>();
	rect[fileName]     = std::make_shared<std::unordered_map<std::string, std::vector<Rect>>>();

	//ステータス数
	unsigned char num = 0;
	fread(&num, sizeof(num), 1, file);
	for (unsigned char i = 0; i < num; ++i)
	{
		unsigned char stNum = 0;
		fread(&stNum, sizeof(stNum), 1, file);

		std::string st;
		st.resize(stNum);
		fread(&st[0], st.size(), 1, file);

		
		float time = 0.0f;
		fread(&time, sizeof(time), 1, file);
		animTime[fileName]->insert(std::make_pair(st, time));

		unsigned char animNum = 0;
		fread(&animNum, sizeof(animNum), 1, file);

		Dummy dummy{};
		rect[fileName]->insert(std::make_pair(st, std::vector<Rect>(animNum)));
		rect[fileName]->at(st).resize(animNum);
		for (auto& i : rect[fileName]->at(st))
		{
			fread(&dummy, sizeof(dummy), 1, file);
			i.pos = { static_cast<float>(dummy.pos.x), static_cast<float>(dummy.pos.y) };
			i.size = { static_cast<float>(dummy.size.x), static_cast<float>(dummy.size.y) };
		}
	}

	fclose(file);

	return 0;
}

// アニメーション・矩形情報の書き込み
int InfoLoader::WriteInfo(const std::string & fileName, const std::vector<Info>& info)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "wb") != 0)
	{
		return -1;
	}

	unsigned char stNum = static_cast<unsigned char>(info.size());
	fwrite(&stNum, sizeof(stNum), 1, file);

	for (auto& i : info)
	{
		fwrite(&i.stNameNum, sizeof(i.stNameNum), 1, file);
		fwrite(&i.state[0], i.state.size(), 1, file);
		fwrite(&i.animTime, sizeof(i.animTime), 1, file);
		fwrite(&i.animNum, sizeof(i.animNum), 1, file);
		for (auto& n : i.rect)
		{
			fwrite(&n.pos, sizeof(n.pos), 1, file);
			fwrite(&n.size, sizeof(n.size), 1, file);
		}
	}

	fclose(file);

	return 0;
}
