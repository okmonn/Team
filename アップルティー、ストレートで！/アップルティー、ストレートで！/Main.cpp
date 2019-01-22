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
	Info wait{};
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
		wait.rect[i].anim.pos.y  = 0.0f;
		wait.rect[i].anim.size.x = 240.0f;
		wait.rect[i].anim.size.y = 270.0f;

		//�������`�̐��Z�b�g
		wait.rect[i].hit.resize(1);
		for (unsigned int n = 0; n < wait.rect[i].hit.size(); ++n)
		{
			//�������`�̎�ށE�A�j���[�V�����؂����`���W����̃I�t�Z�b�g�E�T�C�Y�̃Z�b�g
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