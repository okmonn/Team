#pragma once
#include "Scene.h"

class Over :
	public Scene
{
public:
	// �R���X�g���N�^
	Over();
	// �f�X�g���N�^
	~Over();

	// �`��
	void Draw(void);

	// ����
	void UpData(void);

private:
	// �ʏ�`��
	void NormalDraw(void);

	// �ڍs�`��
	void MoveDraw(void);

	// �ʏ폈��
	void NormalUpData(void);

	// �ڍs����
	void MoveUpData(void);

	// �ǂݍ���
	void Load(void);


	// �֐��|�C���^
	void (Over::*draw)(void);
	void (Over::*updata)(void);
};

