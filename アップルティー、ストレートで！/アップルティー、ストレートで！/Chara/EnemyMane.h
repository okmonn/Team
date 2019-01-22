#pragma once
#include "../etc/Vector2.h"
#include <list>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

class Application;
class Camera;
class Player;
class Enemy;

class EnemyMane
{
public:
	// �R���X�g���N�^
	EnemyMane(std::weak_ptr<Application>app, std::weak_ptr<Camera>cam, std::weak_ptr<Player>pl);
	// �f�X�g���N�^
	~EnemyMane();

	// �G�̐���
	void Create(const std::string& type, const Vec2f& pos, const Vec2f& size);

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

	// ���X�g�̃N���A
	void Clear(void);

private:
	// ������
	void Init(void);


	// �A�v���P�[�V����
	std::weak_ptr<Application>app;

	// �J����
	std::weak_ptr<Camera>cam;

	// �v���C���[
	std::weak_ptr<Player>pl;

	// �G
	std::list<std::shared_ptr<Enemy>>enemy;

	// �֐��|�C���^
	std::unordered_map<std::string, std::function<void(std::list<std::shared_ptr<Enemy>>&, std::weak_ptr<Application>app,std::weak_ptr<Camera>cam, std::weak_ptr<Player>pl, const Vec2f&, const Vec2f&)>>func;
};
