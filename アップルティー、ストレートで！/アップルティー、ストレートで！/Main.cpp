#include "GameMane/GameMane.h"
#include "InfoLoader/InfoLoader.h"
#include <Windows.h>

// エントリーポイント
#ifdef _DEBUG
int main()
#else
int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nShowCmd)
#endif
{
	Info wait{};
	//ステータス名
	wait.st = "wait";
	//アニメーション移行時間
	wait.animTime = 10.0f;
	//アニメーション矩形の数セット
	wait.rect.resize(16);
	for (unsigned int i = 0; i < wait.rect.size(); ++i)
	{
		//アニメーション切り取り矩形の座標・サイズのセット
		wait.rect[i].anim.pos.x  = 240.0f * i;
		wait.rect[i].anim.pos.y  = 0.0f;
		wait.rect[i].anim.size.x = 240.0f;
		wait.rect[i].anim.size.y = 270.0f;

		//あたり矩形の数セット
		wait.rect[i].hit.resize(1);
		for (unsigned int n = 0; n < wait.rect[i].hit.size(); ++n)
		{
			//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
			wait.rect[i].hit[n].type        = HitType::damage;
			wait.rect[i].hit[n].rect.pos.x  = 0.0f;
			wait.rect[i].hit[n].rect.pos.y  = 0.0f;
			wait.rect[i].hit[n].rect.size.x = 240.0f;
			wait.rect[i].hit[n].rect.size.y = 270.0f;
		}
	}
	std::vector<Info>tmp;
	tmp.push_back(wait);

	InfoLoader::Get().Write("_rsc/info/player.info", tmp);

	GameMane::Get().Run();

	return 0;
}