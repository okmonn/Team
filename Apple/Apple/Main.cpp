#include "Application/Application.h"
// �G���g���[�|�C���g
#ifdef _DEBUG
int main()
#else
int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nShowCmd)
#endif
{
	Application& a = Application::Get();
	while (a.CheckMsg())
	{
	
	}

	return 0;
}