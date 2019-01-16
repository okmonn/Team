#include "Input.h"
#include "../Helper/Helper.h"

// �R���X�g���N�^
Input::Input()
{
	memset(&key[0], 0, sizeof(key));
	memset(&old[0], 0, sizeof(old));
}

// �f�X�g���N�^
Input::~Input()
{
}

// �L�[�̓���
bool Input::InputKey(const int & i)
{
	old[i] = key[i];
	key[i] = help::CheckKey(i);
	if (key[i])
	{
		return true;
	}

	return false;
}

// �g���K�[�̓���
bool Input::Triger(const int & i)
{
	if (InputKey(i) == true && old[i] != key[i])
	{
		return true;
	}

	return false;
}
