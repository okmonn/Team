#include "Effector.h"
#include "../Root/Root.h"
#include "../Root/RootMane.h"
#include "../Pipe/Pipe.h"
#include "../Pipe/PipeMane.h"
#include "../Queue/Queue.h"
#include "../List/List.h"
#include "../Fence/Fence.h"
#include <d3d12.h>

// �R���X�g���N�^
Effector::Effector(const std::wstring & fileName)
{
	Load("effect", fileName);
}

// �f�X�g���N�^
Effector::~Effector()
{
	End();
}

// ���s
void Effector::Execution(void)
{
	list->Reset();

	list->SetComputeRoot(RootMane::Get().GetRoot("effect")->Get());
	list->SetPipe(PipeMane::Get().GetPipe("effect")->Get());

	list->Dispatch(1, 1, 1);

	list->Close();

	ID3D12CommandList* com[] = {
		list->GetList(),
	};
	queue->Execution(com, _countof(com));

	fence->Wait();
}
