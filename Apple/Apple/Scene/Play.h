#pragma once
#include "Scene.h"
#include <map>

class Player;
class Enemy;
class Map;

class Play :
	public Scene
{
public:
	// �R���X�g���N�^
	Play(std::weak_ptr<Input>in, std::weak_ptr<Union>un);
	// �f�X�g���N�^
	~Play();

	// ����
	void UpData(void);

	// �`��
	void Draw(void);

private:
	// �N���X�̃C���X�^���X
	void Create(void);

	// 
	std::map<std::string, bool>fadeflg;
	// �v���C���[
	std::shared_ptr<Player>pl;
	std::shared_ptr<Enemy>en;

	// �}�b�v
	std::shared_ptr<Map>map;



};
