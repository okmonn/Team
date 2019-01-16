#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Root;

class RootMane
{
public:
	// �f�X�g���N�^
	~RootMane();

	// �C���X�^���X�ϐ��̎擾
	static RootMane& Get(void) {
		static RootMane instance;
		return instance;
	}

	// ���[�g�̐���
	void Create(const std::string& name, const std::wstring& fileName);

	// ���[�g�̍폜
	void Delete(const std::string& name);

	// ���[�g�̎擾
	std::shared_ptr<Root> GetRoot(const std::string& name) {
		return root[name];
	}

private:
	// �R���X�g���N�^
	RootMane();
	RootMane(const Root&) = delete;
	void operator=(const Root&) = delete;


	// ���[�g
	std::unordered_map<std::string, std::shared_ptr<Root>>root;
};
