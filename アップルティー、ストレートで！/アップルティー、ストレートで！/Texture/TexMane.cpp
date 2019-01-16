#include "TexMane.h"
#include "Texture.h"
#include "../Pipe/PipeMane.h"
#include "../etc/Release.h"

// �R���X�g���N�^
TexMane::TexMane(std::weak_ptr<Window> win, std::weak_ptr<Root> root) : win(win), root(root)
{
	texture.clear();

	PipeMane::Get().Create("tex", root, D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0, 2 }, false);
}

// �f�X�g���N�^
TexMane::~TexMane()
{
}

// �ǂݍ���
void TexMane::Load(int & addr, const std::string & fileName)
{
	if (texture.find(&addr) != texture.end())
	{
		return;
	}

	texture[&addr] = std::make_unique<Texture>(win, root, PipeMane::Get().GetPipe("tex"));
	texture[&addr]->Load(fileName);
}

// �`��
void TexMane::Draw(std::weak_ptr<List> list, int & addr, const DirectX::XMFLOAT2 & pos, const DirectX::XMFLOAT2 & size,
	const DirectX::XMFLOAT2 & uvPos, const DirectX::XMFLOAT2 & uvSize, const float & alpha, const bool & turnX, const bool & turnY)
{
	if (texture.find(&addr) == texture.end())
	{
		return;
	}

	texture[&addr]->SetDraw(pos, size, uvPos, uvSize, alpha, turnX, turnY);
	texture[&addr]->Draw(list);
}

// �폜
void TexMane::Delete(int & addr)
{
	if (texture.find(&addr) != texture.end())
	{
		texture.erase(texture.find(&addr));
	}
}
