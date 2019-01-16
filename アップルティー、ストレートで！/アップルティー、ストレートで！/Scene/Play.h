#pragma once
#include "Scene.h"

class Chara;

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


	// �v���C���[
	std::shared_ptr<Chara>pl;
};
