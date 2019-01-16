#include "RootMane.h"
#include "Root.h"

// �R���X�g���N�^
RootMane::RootMane()
{
	root.clear();
}

// �f�X�g���N�^
RootMane::~RootMane()
{
}

// ���[�g�̐���
void RootMane::Create(const std::string & name, const std::wstring & fileName)
{
	if (root.find(name) != root.end())
	{
		return;
	}

	root[name] = std::make_shared<Root>(fileName);
}

// ���[�g�̍폜
void RootMane::Delete(const std::string & name)
{
	if (root.find(name) != root.end())
	{
		root.erase(root.find(name));
	}
}
