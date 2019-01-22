#include "Window.h"
#include "../DescriptorMane/DescriptorMane.h"
#include "Icon.h"
#include "../etc/Release.h"
#include <Windows.h>
#include <DirectXMath.h>

// ���\�[�X��
#define RSC_MAX 1

// �R���X�g���N�^
Window::Window(const Vec2 & size, void * parent) : size(size),
	handle(nullptr), instance(nullptr), name(nullptr), constant(0)
{
	Create(parent);
	ConstantBuffer();
}

// �f�X�g���N�^
Window::~Window()
{
	DescriptorMane::Get().DeleteRsc(constant);
	DescriptorMane::Get().DeleteHeap(constant);
	UnregisterClass(name, static_cast<HINSTANCE>(instance));
}

// �^�C�g�����̕ύX
void Window::ChangeTitle(const std::tstring & title)
{
	auto hr = SetWindowText(reinterpret_cast<HWND>(handle), title.c_str());
	if (hr == 0)
	{
		OutputDebugString(_T("\n�^�C�g�����̕ύX�F���s\n"));
	}
}

// �E�B���h�E�̃R�[���o�b�N
#if _WIN64
long __stdcall Window::WindowProc(void * hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam)
#else
long __stdcall Window::WindowProc(void* hWnd, unsigned int message, long wParam, long lParam)
#endif
{
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		break;

	case WM_DESTROY:
		if (GetParent(reinterpret_cast<HWND>(hWnd)) != nullptr)
		{
			break;
		}
		PostQuitMessage(0);
		return 0;
	}

	return static_cast<long>(DefWindowProc(reinterpret_cast<HWND>(hWnd), message, wParam, lParam));
}

// �E�B���h�E�̐���
void Window::Create(void * parent)
{
	WNDCLASSEX wnd{};
	wnd.cbClsExtra    = 0;
	wnd.cbSize        = sizeof(WNDCLASSEX);
	wnd.cbWndExtra    = 0;
	wnd.hbrBackground = CreateSolidBrush(0x000000);
	wnd.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wnd.hIcon         = LoadIcon(nullptr, MAKEINTRESOURCE(ICON_ID));
	wnd.hIconSm       = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(ICON_ID));
	wnd.hInstance     = GetModuleHandle(0);
	wnd.lpfnWndProc   = reinterpret_cast<WNDPROC>(WindowProc);
	wnd.lpszClassName = _T("��������");
	wnd.lpszMenuName  = _T("��������");
	wnd.style         = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wnd);

	auto flag = (parent == nullptr) ? (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN) : (WS_OVERLAPPEDWINDOW | WS_CHILD);

	RECT rect{};
	rect.bottom = static_cast<long>(size.y);
	rect.left   = 0;
	rect.right  = static_cast<long>(size.x);
	rect.top    = 0;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	handle = CreateWindow(wnd.lpszClassName, _T("��������"), flag, CW_USEDEFAULT, CW_USEDEFAULT,
		(rect.right - rect.left), (rect.bottom - rect.top), reinterpret_cast<HWND>(parent), nullptr, wnd.hInstance, nullptr);
	if (handle == nullptr)
	{
		OutputDebugString(_T("\n�E�B���h�E�̐����F���s\n"));
		return;
	}

	instance = wnd.hInstance;
	name     = wnd.lpszClassName;

	ShowWindow(reinterpret_cast<HWND>(handle), SW_SHOW);
}

// �萔�o�b�t�@�̐���
void Window::ConstantBuffer(void)
{
	DescriptorMane::Get().CreateHeap(constant, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, RSC_MAX,
		D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.CreationNodeMask     = 0;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	prop.VisibleNodeMask      = 0;

	D3D12_RESOURCE_DESC desc{};
	desc.Alignment        = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (sizeof(DirectX::XMFLOAT2) + 0xff) &~0xff;

	DescriptorMane::Get().CreateRsc(constant, prop, desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	DescriptorMane::Get().CBV(constant, constant, (sizeof(DirectX::XMFLOAT2) + 0xff) & ~0xff);

	void* data = nullptr;
	auto hr = DescriptorMane::Get().GetRsc(constant)->Map(0, nullptr, &data);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�E�B���h�E�p���\�[�X�̃}�b�v�F���s\n"));
		return;
	}

	DirectX::XMFLOAT2 winSize = { static_cast<float>(size.x), static_cast<float>(size.y) };
	memcpy(data, &winSize, sizeof(DirectX::XMFLOAT2));

	DescriptorMane::Get().GetRsc(constant)->Unmap(0, nullptr);
}

// �q�[�v�̎擾
ID3D12DescriptorHeap * Window::GetHeap(void)
{
	return DescriptorMane::Get().GetHeap(constant);
}

// ���\�[�X�̎擾
ID3D12Resource * Window::GetRsc(void)
{
	return DescriptorMane::Get().GetRsc(constant);
}
