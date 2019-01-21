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
				wait.rect[i].anim.pos.x = 240.0f * i;
				wait.rect[i].anim.pos.y = 270.0f * index;
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
				walk.rect[i].anim.pos.x = 240.0f * i;
				walk.rect[i].anim.pos.y = 270.0f * index;
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
					walk.rect[i].hit[n].rect.size.x = 240.0f;
					walk.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}

			++index;
			tmp.push_back(walk);
		}

		InfoLoader::Get().Write("_rsc/info/player.info", tmp);
	}
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
				wait.rect[i].anim.pos.x = 240.0f * i;
				wait.rect[i].anim.pos.y = 270.0f * index;
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
				for (unsigned int n = 0; n < dead.rect[i].hit.size(); ++n)
				{
					//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
					dead.rect[i].hit[n].type = HitType::damage;
					dead.rect[i].hit[n].rect.pos.x = 0.0f;
					dead.rect[i].hit[n].rect.pos.y = 0.0f;
					dead.rect[i].hit[n].rect.size.x = 240.0f;
					dead.rect[i].hit[n].rect.size.y = 270.0f;
				}
			}

			++index;
			tmp.push_back(dead);
		}

		InfoLoader::Get().Write("_rsc/info/enemy1.info", tmp);
	}

	GameMane::Get().Run();

	return 0;
}