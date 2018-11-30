#pragma once
#include <memory>

class Input;
class Union;
class Scene;

class Game
{
public:
	// �R���X�g���N�^
	Game(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Game();

	// �V�[���ڍs
	static void ChangeScene(Scene* scene);

	// ����
	void Run(void);

private:
	// �V�[��
	static std::shared_ptr<Scene>scene;
};
