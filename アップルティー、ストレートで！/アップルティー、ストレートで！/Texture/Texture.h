#pragma once
#include "TextureInfo.h"
#include <string>

class Window;
class List;
class Root;
class Pipe;

class Texture
{
public:
	// �R���X�g���N�^
	Texture(std::weak_ptr<Window>win, std::weak_ptr<Root>root, std::weak_ptr<Pipe>pipe);
	// �f�X�g���N�^
	~Texture();

	// �ǂݍ���
	void Load(const std::string& fileName);

	// �`�揀��
	void SetDraw(const DirectX::XMFLOAT2& pos, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT2& uvPos, const DirectX::XMFLOAT2& uvSize,
		const float& alpha, const bool& turnX, const bool& turnY);

	// �`��
	void Draw(std::weak_ptr<List>list);

private:
	// ���_�o�b�t�@�̐���
	void VertexBuffer(void);

	// �萔�o�b�t�@�̐���
	void ConstantBuffer(void);

	// �V�F�[�_�o�b�t�@�̐���
	void ShaderBuffer(void);

	// �T�u���\�[�X�ɏ�������
	long WriteSub(const std::string& fileName);


	// �E�B���h�E
	std::weak_ptr<Window>win;

	// ���[�g
	std::weak_ptr<Root>root;

	// �p�C�v
	std::weak_ptr<Pipe>pipe;

	// �T�u�f�[�^
	std::weak_ptr<D3D12_SUBRESOURCE_DATA>sub;

	// �萔�f�[�^
	tex::CbvInfo* data;

	// �V�F�[�_���\�[�X
	ID3D12Resource* rsc;

	// �萔�o�b�t�@ID
	int constant;

	// ���_���\�[�XID
	int vRsc;
};
