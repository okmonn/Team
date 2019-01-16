#pragma once
#include <string>

namespace std
{
	// ���j�R�[�h
#ifdef _UNICODE
	typedef wchar_t TCHAR;
	// �}���`�o�C�g
#else
	typedef char TCHAR;
#endif

	// �ϐ���
	typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;
}