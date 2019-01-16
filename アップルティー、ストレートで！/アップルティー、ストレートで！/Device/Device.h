#pragma once

struct ID3D12Device;

class Device
{
public:
	// �f�X�g���N�^
	~Device();

	// �C���X�^���X�ϐ��̎擾
	static Device& Get(void) {
		static Device instance;
		return instance;
	}

	// �f�o�C�X�̎擾
	ID3D12Device* GetDev(void) const {
		return dev;
	}

private:
	// �R���X�g���N�^
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	// �f�o�C�X�̐���
	long Create(void);


	// �f�o�C�X
	ID3D12Device* dev;
};
