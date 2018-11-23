#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <memory>

#include <cstdint>
#include <strsafe.h>
#include "writer.h"
#include "Utils.h"

using std::string;

string g_WarcraftDir;
string g_CurrentDir;
const string g_DllName = "RenderEdge_loader.dll";


bool GetWarcraftPath()
{
	g_WarcraftDir = registry::GetString("Software\\RenderEdge", "War3InstallPath");
	if (!g_WarcraftDir.empty())
		if (utils::FileExists(g_WarcraftDir))
			return true;

	OPENFILENAMEA ofn;
	char szFile[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Warcraft III\0war3.exe\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;
	ofn.lpstrTitle = "Please select war3.exe";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn) == 0)
		return false;

	g_WarcraftDir = utils::ExtractFilePath(szFile);

	HKEY key;
	if (RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\RenderEdge", 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &key, nullptr) == 0)
		RegSetValueExA(key, "War3InstallPath", 0, REG_SZ, (LPBYTE)g_WarcraftDir.c_str(), g_WarcraftDir.size());
	RegCloseKey(key);

	return true;
}


void UpdateConfigs(HINSTANCE hInstance)
{
	char path[MAX_PATH];
	GetModuleFileNameA(hInstance, path, sizeof(path));
	g_CurrentDir = utils::ExtractFilePath(path);

	HKEY key;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\RenderEdge", 0, KEY_WRITE | KEY_QUERY_VALUE, &key) == 0)
	{
		RegSetValueExA(key, "InstallPath", 0, REG_SZ, (LPBYTE)g_CurrentDir.c_str(), g_CurrentDir.size());

		DWORD dwCount = 0;
		if (RegQueryValueExA(key, "Debug", nullptr, nullptr, nullptr, &dwCount) != 0)
		{
			DWORD dwDebug = 0;
			RegSetValueExA(key, "Debug", 0, REG_DWORD, (LPBYTE)&dwDebug, sizeof(DWORD));
		}

		dwCount = 0;
		if (RegQueryValueExA(key, "AllowLocalFiles", nullptr, nullptr, nullptr, &dwCount) != 0)
		{
			DWORD dwAllowLocalFiles = 0;
			RegSetValueExA(key, "AllowLocalFiles", 0, REG_DWORD, (LPBYTE)&dwAllowLocalFiles, sizeof(DWORD));
		}

		RegCloseKey(key);
	}
}

bool InjectDll(HANDLE process_handle, HANDLE thread_handle, string path)
{
	if (path.empty())
		return false;

	struct Code : public assembler::writer<128>
	{
		char dll_path[512];
	} code;

	CONTEXT cxt = { 0 };
	cxt.ContextFlags = CONTEXT_FULL;
	if (!GetThreadContext(thread_handle, &cxt))
		return false;

	uintptr_t code_base = (cxt.Esp - sizeof(code)) & ~0x1Fu;

	if (FAILED(StringCchCopyA(code.dll_path, _countof(code.dll_path), path.c_str())))
		return false;

	uintptr_t address_LoadLibraryA = (uintptr_t)GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA");
	if (!address_LoadLibraryA)
		return false;

	code.push(code_base + offsetof(Code, dll_path));
	code.call(address_LoadLibraryA, code_base + code.size());

	code.mov(assembler::eax, cxt.Eax);
	code.mov(assembler::ebx, cxt.Ebx);
	code.mov(assembler::ecx, cxt.Ecx);
	code.mov(assembler::edx, cxt.Edx);
	code.mov(assembler::esi, cxt.Esi);
	code.mov(assembler::edi, cxt.Edi);
	code.mov(assembler::ebp, cxt.Ebp);
	code.mov(assembler::esp, cxt.Esp);
	code.jmp(cxt.Eip, code_base + code.size());

	cxt.Esp = code_base - 4;
	cxt.Eip = code_base;

	DWORD nProtect = 0;
	if (!VirtualProtectEx(process_handle, (void*)code_base, sizeof Code, PAGE_EXECUTE_READWRITE, &nProtect))
		return false;

	DWORD nWritten = 0;
	if (!WriteProcessMemory(process_handle, (void*)code_base, &code, sizeof Code, &nWritten))
		return false;

	if (!FlushInstructionCache(process_handle, (void*)code_base, sizeof Code))
		return false;

	if (!SetThreadContext(thread_handle, &cxt))
		return false;

	return true;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!GetWarcraftPath())
	{
		Message("Failed to find Warcraft install path");
		return ERROR_FILE_NOT_FOUND;
	}
	string warcraftPath = g_WarcraftDir + "war3.exe";

	UpdateConfigs(hInstance);

	string dllPath = g_CurrentDir + g_DllName;
	if (!utils::FileExists(dllPath))
	{
		Message("Failed to find " + g_DllName);
		return ERROR_FILE_NOT_FOUND;
	}

	STARTUPINFOA si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	char cmdLine[512];
	ZeroMemory(&cmdLine, 512);
	strcpy_s(cmdLine, "war3.exe ");
	strcat_s(cmdLine, lpCmdLine);

	if (!CreateProcessA(warcraftPath.c_str(), cmdLine, nullptr, nullptr, false, NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED, nullptr, nullptr, &si, &pi))
	{
		Message("Failed to launch war3.exe");
		return ERROR_CREATE_FAILED;
	}

	if (!InjectDll(pi.hProcess, pi.hThread, dllPath))
	{
		Message("Failed to inject " + g_DllName);
		return ERROR_DLL_INIT_FAILED;
	}

	ResumeThread(pi.hThread);

	return ERROR_SUCCESS;
}