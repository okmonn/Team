#pragma once
#include "../etc/Vector2.h"
#include <list>
#include <string>
#include <memory>
#include <unordered_map>

class Application;
class Enemy;

class EnemyMane
{
public:
	// �f�X�g���N�^
	~EnemyMane();

	// �C���X�^���X�ϐ��̎擾
	static EnemyMane& Get(void) {
		static EnemyMane instance;
		return instance;
	}

	// �G�̐���
	void Create(const std::string& type, const Vec2f& pos, const Vec2f& size);

	// ���X�g�̃N���A
	void ClearEnemy(void);

	// �I���W���̃N���A
	void ClearOrigin(void);

private:
	// �R���X�g���N�^
	EnemyMane();
	EnemyMane(const EnemyMane&) = delete;
	void operator=(const EnemyMane&) = delete;

	// ������
	void Init(void);


	// �G�̃I���W��
	std::unordered_map<std::string, std::shared_ptr<Enemy>>origin;

	// �G
	std::list<std::shared_ptr<Enemy>>enemy;
};
