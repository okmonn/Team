#pragma once
#include "Scene.h"

class Player;

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
	int a;

private:
	// �N���X�̃C���X�^���X
	void Create(void);


	// �v���C���[
	std::shared_ptr<Player>pl;
};
