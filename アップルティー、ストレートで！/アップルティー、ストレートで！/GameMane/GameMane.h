#pragma once
#include <memory>

class Application;
class Scene;

class GameMane
{
public:
	// �f�X�g���N�^
	~GameMane();

	// �C���X�^���X�ϐ��̎擾
	static GameMane& Get(void) {
		static GameMane instance;
		return instance;
	}

	// �V�[���̈ڍs
	void ChangeScene(Scene* scene);

	// ����
	void Run(void);

private:
	// �R���X�g���N�^
	GameMane();
	GameMane(const GameMane&) = delete;
	void operator=(const GameMane&) = delete;

	// ������
	void Init(void);

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

	// �I��
	void End(void);


	// �A�v���P�[�V����
	std::shared_ptr<Application>app;

	// �V�[��
	std::shared_ptr<Scene>scene;
};
