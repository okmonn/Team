#include "Title.h"
#include "../etc/Vector2.h"
#include "../Input/Input.h"
#include "../Union/Union.h"
#include "../Game/Game.h"
#include "Play.h"

// 矩形読み込み用構造体
struct Dummy {
	//矩形座標
	Vec2 pos;
	//矩形サイズ
	Vec2 size;
};

// コンストラクタ
Title::Title(std::weak_ptr<Input> in, std::weak_ptr<Union> un)
{
	this->in = in;
	this->un = un;

	CreateInfo("rsc/info/player.info");
}

// デストラクタ
Title::~Title()
{
	Delete();
}

// 処理
void Title::UpData(void)
{
	if (in.lock()->Triger(INPUT_RETURN))
	{
		Game::ChangeScene(new Play(in, un));
	}
}

// 描画
void Title::Draw(void)
{
	un.lock()->DrawBox(0, 0, 640, 240, 1, 0, 0);
}

// 矩形情報のファイルの作成
int Title::CreateInfo(const std::string & fileName)
{
	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "wb") != 0)
	{
		return -1;
	}

	const std::string state[] = {
		"wait", "walk", "avoid", "attack1", "attack2", "sliding", "damage"
	};
	const unsigned char animCnt[] = {
		16, 32, 12, 12, 12, 32, 12
	};

	//ステータス数
	unsigned char stNum = _countof(state);
	fwrite(&stNum, sizeof(stNum), 1, file);

	for (unsigned int cnt = 0; cnt < stNum; ++cnt)
	{
		//ステータスの文字数
		unsigned char stNameNum = (unsigned char)state[cnt].size();
		fwrite(&stNameNum, sizeof(stNameNum), 1, file);

		//ステータス
		std::string st = state[cnt];
		fwrite(&st[0], sizeof(char) * st.size(), 1, file);

		//アニメーション時間
		float animTime = 5.0f;
		fwrite(&animTime, sizeof(animTime), 1, file);

		//アニメーション数
		unsigned char animNum = animCnt[cnt];
		fwrite(&animNum, sizeof(animNum), 1, file);

		//矩形座標・矩形サイズ
		Dummy dummy{};
		dummy.size = { 240, 270 };
		for (int i = 0; i < animNum; ++i)
		{
			dummy.pos = Vec2(dummy.size.x * i, dummy.size.y * cnt);
			fwrite(&dummy, sizeof(dummy), 1, file);
		}
	}

	fclose(file);

	return 0;
}
