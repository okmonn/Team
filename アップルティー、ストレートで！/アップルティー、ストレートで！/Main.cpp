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
	//プレイヤー
	unsigned int index = 0;
	std::vector<Info>tmp;

	Info wait{};
	{
			//ステータス名
			wait.st = "wait";
			//アニメーション移行時間
			wait.animTime = 6.0f;
			//アニメーション矩形の数セット
			wait.rect.resize(16);
			for (unsigned int i = 0; i < wait.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				wait.rect[i].anim.pos.x = 240.0f * i;
				wait.rect[i].anim.pos.y = 0.0f;
				wait.rect[i].anim.size.x = 240.0f;
				wait.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				wait.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < wait.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					wait.rect[i].hit[n].type = HitType::damage;
					wait.rect[i].hit[n].rect.pos.x = 0.0f;
					wait.rect[i].hit[n].rect.pos.y = 0.0f;
					wait.rect[i].hit[n].rect.size.x = 240.0f;
					wait.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}
		}
	Info walk{};
	{
			//ステータス名
			walk.st = "walk";
			//アニメーション移行時間
			walk.animTime = 2.0f;
			//アニメーション矩形の数セット
			walk.rect.resize(32);
			for (unsigned int i = 0; i < walk.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				walk.rect[i].anim.pos.x = 240.0f * i;
				walk.rect[i].anim.pos.y = 270.0f;
				walk.rect[i].anim.size.x = 240.0f;
				walk.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				walk.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < walk.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					walk.rect[i].hit[n].type = HitType::damage;
					walk.rect[i].hit[n].rect.pos.x = 0.0f;
					walk.rect[i].hit[n].rect.pos.y = 0.0f;
					walk.rect[i].hit[n].rect.size.x = 120.0f;
					walk.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}
		}
	Info sliding{};
	{
			//ステータス名
			sliding.st = "sliding";
			//アニメーション移行時間
			sliding.animTime = 2.0f;
			//アニメーション矩形の数セット
			sliding.rect.resize(12);
			for (unsigned int i = 0; i < sliding.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				sliding.rect[i].anim.pos.x = 240.0f * i;
				sliding.rect[i].anim.pos.y = 270.0f * 2;
				sliding.rect[i].anim.size.x = 240.0f;
				sliding.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				sliding.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < sliding.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					sliding.rect[i].hit[n].type = HitType::damage;
					sliding.rect[i].hit[n].rect.pos.x = 0.0f;
					sliding.rect[i].hit[n].rect.pos.y = 0.0f;
					sliding.rect[i].hit[n].rect.size.x = 240.0f;
					sliding.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}
		}
	Info attack1{};
	{
			//ステータス名
			attack1.st = "attack1";
			//アニメーション移行時間
			attack1.animTime = 2.0f;
			//アニメーション矩形の数セット
			attack1.rect.resize(12);
			for (unsigned int i = 0; i < attack1.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				attack1.rect[i].anim.pos.x = 240.0f * i;
				attack1.rect[i].anim.pos.y = 270.0f * 3;
				attack1.rect[i].anim.size.x = 240.0f;
				attack1.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				attack1.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < attack1.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					attack1.rect[i].hit[n].type = HitType::damage;
					attack1.rect[i].hit[n].rect.pos.x = 0.0f;
					attack1.rect[i].hit[n].rect.pos.y = 0.0f;
					attack1.rect[i].hit[n].rect.size.x = 240.0f;
					attack1.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}
		}
	Info attack2{};
	{
			//ステータス名
			attack2.st = "attack2";
			//アニメーション移行時間
			attack2.animTime = 2.0f;
			//アニメーション矩形の数セット
			attack2.rect.resize(12);
			for (unsigned int i = 0; i < attack2.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				attack2.rect[i].anim.pos.x = 240.0f * i;
				attack2.rect[i].anim.pos.y = 270.0f * 4;
				attack2.rect[i].anim.size.x = 240.0f;
				attack2.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				attack2.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < attack2.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					attack2.rect[i].hit[n].type = HitType::damage;
					attack2.rect[i].hit[n].rect.pos.x = 0.0f;
					attack2.rect[i].hit[n].rect.pos.y = 0.0f;
					attack2.rect[i].hit[n].rect.size.x = 240.0f;
					attack2.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}
		}
	Info kick{};
	{
			//ステータス名
			kick.st = "kick";
			//アニメーション移行時間
			kick.animTime = (10.0f / 16) * 32;
			//アニメーション矩形の数セット
			kick.rect.resize(32);
			for (unsigned int i = 0; i < kick.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				kick.rect[i].anim.pos.x = 240.0f * i;
				kick.rect[i].anim.pos.y = 270.0f * 5;
				kick.rect[i].anim.size.x = 240.0f;
				kick.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				kick.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < kick.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					kick.rect[i].hit[n].type = HitType::damage;
					kick.rect[i].hit[n].rect.pos.x = 0.0f;
					kick.rect[i].hit[n].rect.pos.y = 0.0f;
					kick.rect[i].hit[n].rect.size.x = 240.0f;
					kick.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}
		}
	Info damage{};
	{
			//ステータス名
			damage.st = "damage";
			//アニメーション移行時間
			damage.animTime = (10.0f / 16) * 12;
			//アニメーション矩形の数セット
			damage.rect.resize(12);
			for (unsigned int i = 0; i < damage.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				damage.rect[i].anim.pos.x = 240.0f * i;
				damage.rect[i].anim.pos.y = 270.0f * 6;
				damage.rect[i].anim.size.x = 240.0f;
				damage.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				damage.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < damage.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					damage.rect[i].hit[n].type = HitType::damage;
					damage.rect[i].hit[n].rect.pos.x = 0.0f;
					damage.rect[i].hit[n].rect.pos.y = 0.0f;
					damage.rect[i].hit[n].rect.size.x = 240.0f;
					damage.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}
		}

	tmp.push_back(wait);
	tmp.push_back(walk);
	tmp.push_back(attack1);
	tmp.push_back(attack2);
	tmp.push_back(sliding);
	tmp.push_back(kick);
	tmp.push_back(damage);

	InfoLoader::Get().Write("_rsc/info/player.info", tmp);


	//敵1
	{
		unsigned int index = 0;
		std::vector<Info>tmp;

		Info wait{};
		{
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
				wait.rect[i].anim.pos.y  = 270.0f * index;
				wait.rect[i].anim.size.x = 240.0f;
				wait.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				wait.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < wait.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					wait.rect[i].hit[n].type = HitType::damage;
					wait.rect[i].hit[n].rect.pos.x  = 0.0f;
					wait.rect[i].hit[n].rect.pos.y  = 0.0f;
					wait.rect[i].hit[n].rect.size.x = 240.0f;
					wait.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}

			++index;
			tmp.push_back(wait);
		}

		Info walk{};
		{
			//ステータス名
			walk.st = "walk";
			//アニメーション移行時間
			walk.animTime = 10.0f;
			//アニメーション矩形の数セット
			walk.rect.resize(32);
			for (unsigned int i = 0; i < walk.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				walk.rect[i].anim.pos.x  = 240.0f * i;
				walk.rect[i].anim.pos.y  = 270.0f * index;
				walk.rect[i].anim.size.x = 240.0f;
				walk.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				walk.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < walk.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					walk.rect[i].hit[n].type = HitType::damage;
					walk.rect[i].hit[n].rect.pos.x  = 0.0f;
					walk.rect[i].hit[n].rect.pos.y  = 0.0f;
					walk.rect[i].hit[n].rect.size.x = 240.0f;
					walk.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}

			++index;
			tmp.push_back(walk);
		}

		Info attack{};
		{
			//ステータス名
			attack.st = "attack";
			//アニメーション移行時間
			attack.animTime = 10.0f;
			//アニメーション矩形の数セット
			attack.rect.resize(12);
			for (unsigned int i = 0; i < attack.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				attack.rect[i].anim.pos.x = 240.0f * i;
				attack.rect[i].anim.pos.y = 270.0f * index;
				attack.rect[i].anim.size.x = 240.0f;
				attack.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				attack.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < attack.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					attack.rect[i].hit[n].type = HitType::damage;
					attack.rect[i].hit[n].rect.pos.x = 0.0f;
					attack.rect[i].hit[n].rect.pos.y = 0.0f;
					attack.rect[i].hit[n].rect.size.x = 240.0f;
					attack.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}

			++index;
			tmp.push_back(attack);
		}

		Info damage{};
		{
			//ステータス名
			damage.st = "damage";
			//アニメーション移行時間
			damage.animTime = 10.0f;
			//アニメーション矩形の数セット
			damage.rect.resize(12);
			for (unsigned int i = 0; i < damage.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				damage.rect[i].anim.pos.x = 240.0f * i;
				damage.rect[i].anim.pos.y = 270.0f * index;
				damage.rect[i].anim.size.x = 240.0f;
				damage.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				damage.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < damage.rect[i].hit.size(); ++n)
				{
					//あたり矩形の種類・アニメーション切り取り矩形座標からのオフセット・サイズのセット
					damage.rect[i].hit[n].type = HitType::damage;
					damage.rect[i].hit[n].rect.pos.x = 0.0f;
					damage.rect[i].hit[n].rect.pos.y = 0.0f;
					damage.rect[i].hit[n].rect.size.x = 240.0f;
					damage.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}

			++index;
			tmp.push_back(damage);
		}

		Info dead{};
		{
			//ステータス名
			dead.st = "dead";
			//アニメーション移行時間
			dead.animTime = 10.0f;
			//アニメーション矩形の数セット
			dead.rect.resize(16);
			for (unsigned int i = 0; i < dead.rect.size(); ++i)
			{
				//アニメーション切り取り矩形の座標・サイズのセット
				dead.rect[i].anim.pos.x = 240.0f * i;
				dead.rect[i].anim.pos.y = 270.0f * index;
				dead.rect[i].anim.size.x = 240.0f;
				dead.rect[i].anim.size.y = 270.0f;

				//あたり矩形の数セット
				dead.rect[i].hit.resize(0);
			}

			++index;
			tmp.push_back(dead);
		}

		InfoLoader::Get().Write("_rsc/info/enemy1.info", tmp);
	}

	GameMane::Get().Run();

	return 0;
}