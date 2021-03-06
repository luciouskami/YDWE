#pragma once

#include <base/filesystem.h>
#include <bee/utility/path_helper.h>
#include <Windows.h>

// http://blogs.msdn.com/oldnewthing/archive/2004/10/25/247180.aspx
extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace base { namespace path {
	inline fs::path self()
	{
		return std::move(bee::path_helper::dll_path(reinterpret_cast<HMODULE>(&__ImageBase)).value());
	}
}}
