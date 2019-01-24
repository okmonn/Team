#pragma once
#include "Scene.h"

class Camera;
class BackGround;
class Player;
class EnemyMane;

class Play :
	public Scene
{
public:
	// �R���X�g���N�^
	Play(std::weak_ptr<Application>app);
	// �f�X�g���N�^
	~Play();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// ����
	void Create(void);


	// �J����
	std::shared_ptr<Camera>cam;

	// �w�i
	std::shared_ptr<BackGround>back;

	// �v���C���[
	std::shared_ptr<Player>pl;

	// �G
	std::shared_ptr<EnemyMane>enemy;
};
