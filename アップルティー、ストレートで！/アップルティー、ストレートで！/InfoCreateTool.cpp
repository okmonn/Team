#include "Application/Application.h"
#include "InfoLoader/InfoLoader.h"
#include "Input/Input.h"

// �o�b�t�@�T�C�Y
#define BUFFER 256

int main()
{
	char buf[BUFFER];
	printf("�摜�t�@�C���p�X�̓���\n");
	scanf_s("%s", buf, BUFFER);
	fflush(stdin);

	//�摜�t�@�C���p�X
	std::string filePath(buf);

	//�摜�؂���T�C�Y
	Vec2 winSize = 0;
	printf("�摜�̐؂���T�C�YX�F");
	scanf_s("%d", &winSize.x);
	fflush(stdin);
	printf("�摜�̐؂���T�C�YY�F");
	scanf_s("%d", &winSize.y);
	fflush(stdin);
	Vec2f rectSize = { (float)winSize.x, (float)winSize.y };
	
	//�E�B���h�E�̐���
	Application app(winSize);

	//�摜�̓ǂݍ���
	int imag = 0;
	app.LoadTex(imag, filePath);

	//�X�e�[�^�X�̐�
	int stNum;
	printf("�X�e�[�^�X�̐��F");
	scanf_s("%d", &stNum);
	fflush(stdin);

	std::vector<Info>write;
	for (int st = 0; st < stNum; ++st)
	{
		Info info{};
		printf("�X�e�[�^�X���F");
		scanf_s("%s", buf, BUFFER);
		fflush(stdin);
		info.st = buf;

		printf("�A�j���[�V�����ڍs�t���[���F");
		scanf_s("%f", &info.animTime);
		fflush(stdin);

		int animNum = 0;
		printf("�A�j���[�V�������F");
		scanf_s("%d", &animNum);
		fflush(stdin);
		info.rect.resize(animNum);

		for (int i = 0; i < animNum; ++i)
		{
			//�A�j���[�V�����؂����`���
			info.rect[i].anim.pos.x = rectSize.x * i;
			info.rect[i].anim.pos.y = rectSize.y * st;
			info.rect[i].anim.size  = rectSize;

			std::vector<HitRect<Vec2f>>hit;
			HitRect<Vec2f>tmp{};
			bool click = false;
			while (app.CheckMsg())
			{
				app.Clear();
				app.DrawTex(imag, 0.0f, rectSize, info.rect[i].anim.pos, info.rect[i].anim.size);
				for (auto& h : hit)
				{
					Color color{};
					if (h.type == HitType::damage)
					{
						color.g = 1.0f;
					}
					else
					{
						color.r = 1.0f;
					}
					color.a = 0.5f;
					app.DrawBox(h.rect.pos, h.rect.size, color);
				}
				Color color{};
				if (tmp.type == HitType::damage)
				{
					color.g = 1.0f;
				}
				else
				{
					color.r = 1.0f;
				}
				color.a = 0.5f;
				app.DrawBox(tmp.rect.pos, tmp.rect.size, color);
				app.Execution();

				if (Input::Get().InputKey(INPUT_LBUTTON))
				{
					if (click == false)
					{
						Vec2f pos = Vec2f((float)app.GetMousePos().x, (float)app.GetMousePos().y);
						if (pos.x > (float)winSize.x)
						{
							pos.x = (float)winSize.x;
						}
						else if (pos.x < 0.0f)
						{
							pos.x = 0.0f;
						}
						if (pos.y > (float)winSize.y)
						{
							pos.y = (float)winSize.y;
						}
						else if (pos.y < 0.0f)
						{
							pos.y = 0.0f;
						}

						tmp.rect.pos = pos;
						click = true;
					}
					else
					{
						Vec2f pos = Vec2f((float)app.GetMousePos().x, (float)app.GetMousePos().y);
						if (pos.x > (float)winSize.x)
						{
							pos.x = (float)winSize.x;
						}
						else if (pos.x < 0.0f)
						{
							pos.x = 0.0f;
						}
						if (pos.y > (float)winSize.y)
						{
							pos.y = (float)winSize.y;
						}
						else if (pos.y < 0.0f)
						{
							pos.y = 0.0f;
						}

						tmp.rect.size = pos - tmp.rect.pos;
					}
				}
				else
				{
					if (click == true)
					{
						printf("���W  �F%d,%d\n", (int)tmp.rect.pos.x, (int)tmp.rect.pos.y);
						printf("�T�C�Y�F%d,%d\n", (int)tmp.rect.size.x, (int)tmp.rect.size.y);
					}
					click = false;
				}

				if (Input::Get().Triger(INPUT_RBUTTON))
				{
					tmp.type = (tmp.type == HitType::damage) ? HitType::attack : HitType::damage;
				}

				if (Input::Get().Triger(INPUT_SPACE))
				{
					hit.push_back(tmp);
					printf("���W  �F%d,%d\n", (int)tmp.rect.pos.x, (int)tmp.rect.pos.y);
					printf("�T�C�Y�F%d,%d\n", (int)tmp.rect.size.x, (int)tmp.rect.size.y);
					printf("�f�[�^��ǉ����܂���\n");
					tmp = {};
				}

				if (Input::Get().InputKey(INPUT_CTRL) && Input::Get().Triger(INPUT_S))
				{
					info.rect[i].hit = hit;
					printf("%d�̋�`����ۑ����܂���\n", static_cast<int>(hit.size()));
					break;
				}
			}
		}

		write.push_back(info);
	}

	printf("�����o���t�@�C���p�X�̓���\n");
	scanf_s("%s", buf, BUFFER);
	fflush(stdin);

	std::string writePath(buf);
	InfoLoader::Get().Write(writePath, write);

	return 0;
}