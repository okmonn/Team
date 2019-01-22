#include "GameMane/GameMane.h"
#include "InfoLoader/InfoLoader.h"
#include <Windows.h>

// �G���g���[�|�C���g
#ifdef _DEBUG
int main()
#else
int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nShowCmd)
#endif
{
	//�v���C���[
	unsigned int index = 0;
	std::vector<Info>tmp;

	Info wait{};
	{
			//�X�e�[�^�X��
			wait.st = "wait";
			//�A�j���[�V�����ڍs����
			wait.animTime = 6.0f;
			//�A�j���[�V������`�̐��Z�b�g
			wait.rect.resize(16);
			for (unsigned int i = 0; i < wait.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				wait.rect[i].anim.pos.x = 240.0f * i;
				wait.rect[i].anim.pos.y = 0.0f;
				wait.rect[i].anim.size.x = 240.0f;
				wait.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				wait.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < wait.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			walk.st = "walk";
			//�A�j���[�V�����ڍs����
			walk.animTime = 2.0f;
			//�A�j���[�V������`�̐��Z�b�g
			walk.rect.resize(32);
			for (unsigned int i = 0; i < walk.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				walk.rect[i].anim.pos.x = 240.0f * i;
				walk.rect[i].anim.pos.y = 270.0f;
				walk.rect[i].anim.size.x = 240.0f;
				walk.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				walk.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < walk.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			sliding.st = "sliding";
			//�A�j���[�V�����ڍs����
			sliding.animTime = 2.0f;
			//�A�j���[�V������`�̐��Z�b�g
			sliding.rect.resize(12);
			for (unsigned int i = 0; i < sliding.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				sliding.rect[i].anim.pos.x = 240.0f * i;
				sliding.rect[i].anim.pos.y = 270.0f * 2;
				sliding.rect[i].anim.size.x = 240.0f;
				sliding.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				sliding.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < sliding.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			attack1.st = "attack1";
			//�A�j���[�V�����ڍs����
			attack1.animTime = 2.0f;
			//�A�j���[�V������`�̐��Z�b�g
			attack1.rect.resize(12);
			for (unsigned int i = 0; i < attack1.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				attack1.rect[i].anim.pos.x = 240.0f * i;
				attack1.rect[i].anim.pos.y = 270.0f * 3;
				attack1.rect[i].anim.size.x = 240.0f;
				attack1.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				attack1.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < attack1.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			attack2.st = "attack2";
			//�A�j���[�V�����ڍs����
			attack2.animTime = 2.0f;
			//�A�j���[�V������`�̐��Z�b�g
			attack2.rect.resize(12);
			for (unsigned int i = 0; i < attack2.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				attack2.rect[i].anim.pos.x = 240.0f * i;
				attack2.rect[i].anim.pos.y = 270.0f * 4;
				attack2.rect[i].anim.size.x = 240.0f;
				attack2.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				attack2.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < attack2.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			kick.st = "kick";
			//�A�j���[�V�����ڍs����
			kick.animTime = (10.0f / 16) * 32;
			//�A�j���[�V������`�̐��Z�b�g
			kick.rect.resize(32);
			for (unsigned int i = 0; i < kick.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				kick.rect[i].anim.pos.x = 240.0f * i;
				kick.rect[i].anim.pos.y = 270.0f * 5;
				kick.rect[i].anim.size.x = 240.0f;
				kick.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				kick.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < kick.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			damage.st = "damage";
			//�A�j���[�V�����ڍs����
			damage.animTime = (10.0f / 16) * 12;
			//�A�j���[�V������`�̐��Z�b�g
			damage.rect.resize(12);
			for (unsigned int i = 0; i < damage.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				damage.rect[i].anim.pos.x = 240.0f * i;
				damage.rect[i].anim.pos.y = 270.0f * 6;
				damage.rect[i].anim.size.x = 240.0f;
				damage.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				damage.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < damage.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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


	//�G1
	{
		unsigned int index = 0;
		std::vector<Info>tmp;

		Info wait{};
		{
			//�X�e�[�^�X��
			wait.st = "wait";
			//�A�j���[�V�����ڍs����
			wait.animTime = 10.0f;
			//�A�j���[�V������`�̐��Z�b�g
			wait.rect.resize(16);
			for (unsigned int i = 0; i < wait.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				wait.rect[i].anim.pos.x  = 240.0f * i;
				wait.rect[i].anim.pos.y  = 270.0f * index;
				wait.rect[i].anim.size.x = 240.0f;
				wait.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				wait.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < wait.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			walk.st = "walk";
			//�A�j���[�V�����ڍs����
			walk.animTime = 10.0f;
			//�A�j���[�V������`�̐��Z�b�g
			walk.rect.resize(32);
			for (unsigned int i = 0; i < walk.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				walk.rect[i].anim.pos.x  = 240.0f * i;
				walk.rect[i].anim.pos.y  = 270.0f * index;
				walk.rect[i].anim.size.x = 240.0f;
				walk.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				walk.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < walk.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			attack.st = "attack";
			//�A�j���[�V�����ڍs����
			attack.animTime = 10.0f;
			//�A�j���[�V������`�̐��Z�b�g
			attack.rect.resize(12);
			for (unsigned int i = 0; i < attack.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				attack.rect[i].anim.pos.x = 240.0f * i;
				attack.rect[i].anim.pos.y = 270.0f * index;
				attack.rect[i].anim.size.x = 240.0f;
				attack.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				attack.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < attack.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			damage.st = "damage";
			//�A�j���[�V�����ڍs����
			damage.animTime = 10.0f;
			//�A�j���[�V������`�̐��Z�b�g
			damage.rect.resize(12);
			for (unsigned int i = 0; i < damage.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				damage.rect[i].anim.pos.x = 240.0f * i;
				damage.rect[i].anim.pos.y = 270.0f * index;
				damage.rect[i].anim.size.x = 240.0f;
				damage.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
				damage.rect[i].hit.resize(1);
				for (unsigned int n = 0; n < damage.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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
			//�X�e�[�^�X��
			dead.st = "dead";
			//�A�j���[�V�����ڍs����
			dead.animTime = 10.0f;
			//�A�j���[�V������`�̐��Z�b�g
			dead.rect.resize(16);
			for (unsigned int i = 0; i < dead.rect.size(); ++i)
			{
				//�A�j���[�V�����؂����`�̍��W�E�T�C�Y�̃Z�b�g
				dead.rect[i].anim.pos.x = 240.0f * i;
				dead.rect[i].anim.pos.y = 270.0f * index;
				dead.rect[i].anim.size.x = 240.0f;
				dead.rect[i].anim.size.y = 270.0f;

				//�������`�̐��Z�b�g
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