#include "GameMane/GameMane.h"
#include <Windows.h>

// �G���g���[�|�C���g
#ifdef _DEBUG
int main()
#else
int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nShowCmd)
#endif
{
	GameMane::Get().Run();

	return 0;
}