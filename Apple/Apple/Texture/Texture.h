#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <DirectXMath.h>

struct ID3D12GraphicsCommandList;
struct D3D12_SUBRESOURCE_DATA;
struct ID3D12Resource;
class DescriptorMane;
class TextureLoad;
class Window;
class Device;
class List;
class Root;
class Pipe;

namespace tex {
	// ���_
	struct Vertex {
		//���W
		DirectX::XMFLOAT3 pos;
		//uv
		DirectX::XMFLOAT2 uv;
	};

	struct Info
	{
		//�ړ��s��
		DirectX::XMFLOAT4X4 matrix;
		//�E�B���h�E�T�C�Y
		DirectX::XMFLOAT2 window;
		//uv���W
		DirectX::XMFLOAT2 uvPos;
		//uv�T�C�Y
		DirectX::XMFLOAT2 uvSize;
		//���]
		DirectX::XMFLOAT2 reverse;
		//�A���t�@�l
		float alpha;
	};
}

class Texture
{
	//�摜�f�[�^
	struct Tex {
		//�摜���\�[�X
		ID3D12Resource* rsc;
		//�f�R�[�h
		unsigned char* decode;
		//�T�u�f�[�^
		std::weak_ptr<D3D12_SUBRESOURCE_DATA>sub;
		//�萔���\�[�XID
		int cRsc;
		//�萔���M�f�[�^
		tex::Info* info;
		//���_���\�[�XID
		int vRsc;
		//���_���M�f�[�^
		unsigned int* data;
		//�o���h�����X�g
		std::unique_ptr<List>list;
	};

public:
	// �R���X�g���N�^
	Texture(std::weak_ptr<Window>win, std::weak_ptr<Device>dev, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe);
	// �f�X�g���N�^
	~Texture();

	// �ǂݍ���
	void Load(const std::string& fileName, int& i);

	// �`��
	void Draw(std::weak_ptr<List>list, int& i, const DirectX::XMFLOAT2& pos, const DirectX::XMFLOAT2& size, 
		const DirectX::XMFLOAT2& uvPos, const DirectX::XMFLOAT2& uvSize, const float& alpha = 1.0f, 
		const bool& turnX = false, const bool& turnY = false);

	// �폜
	void Delete(int& i);

private:
	float a;
	// ���_�̃Z�b�g
	void SetVertex(void);

	// �萔���\�[�X�̐���
	long CreateConRsc(int* i);

	// �萔�o�b�t�@�r���[�̐���
	void CreateConView(int* i);

	// �V�F�[�_�[���\�[�X�r���[�̐���
	void CreateShaderView(int* i);

	// �T�u���\�[�X�ɏ�������
	long WriteSub(int* i);

	// �萔�o�b�t�@�̃}�b�v
	long MapCon(int* i);

	// ���_���\�[�X�̐���
	long CreateVertexRsc(int* i);

	// ���_�}�b�v
	long MapVertex(int* i);

	// �o���h���̃Z�b�g
	void SetBundle(int* i);


	// �f�B�X�N���v�^�[�}�l�[�W���[
	DescriptorMane& descMane;

	// �e�N�X�`�����[�_�[
	TextureLoad& loader;

	// �E�B���h�E
	std::weak_ptr<Window>win;

	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// ���[�g�V�O�l�`��
	std::weak_ptr<Root>root;

	// �p�C�v���C��
	std::weak_ptr<Pipe>pipe;

	// ���_
	std::vector<tex::Vertex>vertex;

	// �摜�f�[�^
	std::map<int*, Tex>tex;
};
