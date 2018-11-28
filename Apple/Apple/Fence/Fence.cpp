#include "Fence.h"
#include "../Device/Device.h"
#include "../Queue/Queue.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Fence::Fence(std::weak_ptr<Device> dev, std::weak_ptr<Queue> queue) : 
	dev(dev), queue(queue), fence(nullptr), handle(CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS)), cnt(0)
{
	CreateFence();
}

// �f�X�g���N�^
Fence::~Fence()
{
	Release(fence);
	CloseHandle(handle);
}

// �t�F���X�̐���
long Fence::CreateFence(void)
{
	auto hr = dev.lock()->Get()->CreateFence(cnt, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�t�F���X�̐����F���s\n"));
		return hr;
	}

	//�t�F���X�l�̍X�V
	cnt = 1;

	return hr;
}

// �ҋ@
void Fence::Wait(void)
{
	//�t�F���X�l�X�V
	++cnt;

	//�t�F���X�l��ύX
	auto hr = queue.lock()->Get()->Signal(fence, cnt);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�t�F���X�l�̍X�V�F���s\n"));
		return;
	}

	//������ҋ@(�|�[�����O)
	while (fence->GetCompletedValue() != cnt)
	{
		//�t�F���X�C�x���g�̃Z�b�g
		hr = fence->SetEventOnCompletion(cnt, handle);
		if (FAILED(hr))
		{
			OutputDebugString(_T("\n�t�F���X�C�x���g�̃Z�b�g�F���s\n"));
			return;
		}

		//�t�F���X�C�x���g�̑ҋ@
		WaitForSingleObject(handle, INFINITE);
	}
}
