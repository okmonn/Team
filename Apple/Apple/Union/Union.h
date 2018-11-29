#pragma once
#include "../etc/tString.h"
#include <map>
#include <list>
#include <memory>

enum D3D12_PRIMITIVE_TOPOLOGY_TYPE : int;
class RootMane;
class PipeMane;
class Window;
class Device;
class Queue;
class List;
class Swap;
class Render;
class Depth;
class Fence;
class Texture;
class Point;

class Union
{
public:
	// �R���X�g���N�^
	Union(std::weak_ptr<Window>win);
	// �f�X�g���N�^
	~Union();

	// �摜�̓ǂݍ���
	void LoadImg(const std::string& fileName, int& i);

	// �摜�̕`��
	void DrawImg(int& i, const float& x, const float& y, const float& sizeX, const float& sizeY, const float& rectX, const float& rectY, 
		const float& rectSizexX, const float& rectSizeY, const float& alpha = 1.0f, const bool& turnX = false, const bool& turnY = false);

	// �_�̕`��
	void DrawPoint(const float& x, const float& y, const float& r, const float& g, const float& b, const float& alpha = 1.0f);

	// ��ʃN���A
	void Clear(void);

	// ���s
	void Execution(void);

	// �f�o�C�X�̎擾
	std::shared_ptr<Device>GetDev(void) const {
		return dev;
	}

private:
	// ���[�g�V�O�l�`���̐���
	void CreateRoot(const std::string& name, const std::tstring& fileName);
	void CreateRoot(void);

	// �p�C�v���C���̐���
	void CreatePipe(const std::string& name, const std::string& rootName, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type,
		const std::initializer_list<int>&index, const bool& depth = false);
	void CreatePipe(void);

	// �N���X�̐���
	void Create(void);

	// ���[�g�}�l�W���[
	RootMane& root;

	// �p�C�v�}�l�W���[
	PipeMane& pipe;

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

	// ���[�g�V�O�l�`��ID
	std::map<std::string, int>rootNo;

	// �p�C�v���C��ID
	std::map<std::string, int>pipeNo;

	// �e�N�X�`��
	std::unique_ptr<Texture>tex;

	// �|�C���g
	std::list<std::shared_ptr<Point>>point;
};
