#pragma once
#include "Compute.h"

class Effector :
	public Compute
{
public:
	// �R���X�g���N�^
	Effector(const std::wstring& fileName);
	// �f�X�g���N�^
	~Effector();

	// ���s
	void Execution(void);

private:

};
