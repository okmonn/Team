#include "PrimitiveMane.h"
#include "Primitive.h"
#include "../Pipe/PipeMane.h"
#include "../etc/Release.h"

// �g�|���W�[�^�C�v
const D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType[] = {
	D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE
};

// �^�C�v
const std::string pipeName[] = {
	"",
	"point",
	"line",
	"triangle"
};

// �R���X�g���N�^
PrimitiveMane::PrimitiveMane(std::weak_ptr<Window> win, std::weak_ptr<Root> root) : win(win), root(root)
{
	primitive.clear();

	CreatePipe();
}

// �f�X�g���N�^
PrimitiveMane::~PrimitiveMane()
{
}

// �p�C�v�̐���
void PrimitiveMane::CreatePipe(void)
{
	PipeMane::Get().Get().Create(pipeName[static_cast<int>(prm::PrimitiveType::point)], root, topologyType[static_cast<int>(prm::PrimitiveType::point)], { 0, 3 }, false);
	PipeMane::Get().Get().Create(pipeName[static_cast<int>(prm::PrimitiveType::line)], root, topologyType[static_cast<int>(prm::PrimitiveType::line)], { 0, 3 }, false);
	PipeMane::Get().Get().Create(pipeName[static_cast<int>(prm::PrimitiveType::triangle)], root, topologyType[static_cast<int>(prm::PrimitiveType::triangle)], { 0, 3 }, false);
}

// �`��
void PrimitiveMane::Draw(std::weak_ptr<List> list, const prm::PrimitiveType & type, prm::Vertex * vertex, const size_t & num)
{
	primitive.push_back(std::make_unique<Primitive>(win, root, PipeMane::Get().GetPipe(pipeName[static_cast<int>(type)]), type));
	primitive.back()->Draw(list, vertex, num);
}

// �N���A
void PrimitiveMane::Clear(void)
{
	primitive.clear();
}
