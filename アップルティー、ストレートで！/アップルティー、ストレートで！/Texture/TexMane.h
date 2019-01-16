#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <DirectXMath.h>

class Texture;
class Window;
class List;
class Root;

class TexMane
{
public:
	// �R���X�g���N�^
	TexMane(std::weak_ptr<Window>win, std::weak_ptr<Root>root);
	// �f�X�g���N�^
	~TexMane();

	// �ǂݍ���
	void Load(int& addr, const std::string& fileName);

	// �`��
	void Draw(std::weak_ptr<List>list, int& addr, const DirectX::XMFLOAT2& pos, const DirectX::XMFLOAT2& size,
		const DirectX::XMFLOAT2& uvPos, const DirectX::XMFLOAT2& uvSize, const float& alpha, const bool& turnX, const bool& turnY);

	// �폜
	void Delete(int& addr);

private:
	// �E�B���h�E
	std::weak_ptr<Window>win;

	// ���[�g
	std::weak_ptr<Root>root;

	// �e�N�X�`��
	std::unordered_map<int*, std::unique_ptr<Texture>>texture;
};
