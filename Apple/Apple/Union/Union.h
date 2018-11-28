#pragma once
#include <memory>

class Window;
class Device;
class Queue;
class List;
class Swap;
class Render;
class Depth;
class Fence;

class Union
{
public:
	// �R���X�g���N�^
	Union(std::weak_ptr<Window>win);
	// �f�X�g���N�^
	~Union();

	// �`��
	void Draw(void);

private:
	// �N���X�̐���
	void Create(void);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �f�o�C�X
	std::shared_ptr<Device>dev;

	// �L���[
	std::shared_ptr<Queue>queue;

	// ���X�g
	std::shared_ptr<List>list;

	// �X���b�v
	std::shared_ptr<Swap>swap;

	// �����_�[
	std::unique_ptr<Render>ren;

	// �[�x
	std::unique_ptr<Depth>depth;

	// �t�F���X
	std::unique_ptr<Fence>fence;
};
