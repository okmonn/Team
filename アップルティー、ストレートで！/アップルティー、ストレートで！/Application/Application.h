#pragma once
#include "../Sound/Sound.h"
#include "../Helper/Helper.h"
#include "../etc/Color.h"
#include "../etc/InputInfo.h"
#include <memory>

class Window;
class Queue;
class List;
class Fence;
class Swap;
class Render;
class Depth;
class PrimitiveMane;
class TexMane;

class Application
{
public:
	// �R���X�g���N�^
	Application(const Vec2& winSize);
	Application(const Application& app, const Vec2& winSize);
	Application(std::weak_ptr<Application>app, const Vec2& winSize);
	// �f�X�g���N�^
	~Application();

	// �E�B���h�E�T�C�Y�̎擾
	Vec2 GetWinSize(void);

	// ���b�Z�[�W�̊m�F
	bool CheckMsg(void);

	// �|�C���g�̕`��
	void DrawPoint(const Vec2f& pos, const Color& color);

	// ���C���̕`��
	void DrawLine(const Vec2f& pos1, const Vec2f& pos2, const Color& color);

	// �g���C�A���O���̕`��
	void DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const Color& color);

	// �{�b�N�X�̕`��
	void DrawBox(const Vec2f& pos, const Vec2f& size, const Color& color);

	// �摜�̓ǂݍ���
	void LoadTex(int& addr, const std::string& fileName);

	// �摜�̕`��
	void DrawTex(int& addr, const Vec2f& pos, const Vec2f& size, const Vec2f& uvPos, const Vec2f& uvSize,
		const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);

	// ��ʃN���A
	void Clear(void);

	// �R�}���h�̎��s
	void Execution(void);

	// �摜�̍폜
	void DeleteTex(int& addr);

private:
	// �R���X�g���N�^
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	// ���[�g�̐���
	void CreateRoot(void);

	// ������
	void Init(const Vec2& winSize, void* parent = nullptr);


	// �E�B���h�E
	std::shared_ptr<Window>win;

	// �L���[
	std::shared_ptr<Queue>queue;

	// ���X�g
	std::shared_ptr<List>list;

	// �t�F���X
	std::unique_ptr<Fence>fence;

	// �X���b�v
	std::shared_ptr<Swap>swap;

	// �����_�[
	std::unique_ptr<Render>render;

	// �f�v�X
	std::unique_ptr<Depth>depth;

	// �v���~�e�B�u
	std::unique_ptr<PrimitiveMane>primitive;

	// �e�N�X�`��
	std::unique_ptr<TexMane>texture;
};
