#include "storm.h"
#include "fp_call.h"
#include <stdio.h>
#include "Utils.h"

namespace Storm {

	uintptr_t SFile_CloseArchive;
	uintptr_t SFile_CloseFile;
	uintptr_t SFile_EnableDirectAccess;
	uintptr_t SFile_GetFileArchive;
	uintptr_t SFile_GetFileSize;
	uintptr_t SFile_OpenArchive;
	uintptr_t SFile_OpenFile;
	uintptr_t SFile_OpenFileEx;
	uintptr_t SFile_ReadFile;
	uintptr_t SFile_SetBasePath;
	uintptr_t SFile_SetFilePointer;
	uintptr_t SFile_SetLocale;
	uintptr_t SFile_GetBasePath;
	uintptr_t SFile_GetArchiveName;
	uintptr_t SFile_GetFileName;
	uintptr_t SFile_GetArchiveInfo;
	uintptr_t SFile_LoadFile;
	uintptr_t SFile_UnloadFile;
	uintptr_t SFile_LoadFileEx;
	uintptr_t SFile_ReadFileEx;
	uintptr_t SFile_FileExists;
	uintptr_t SFile_FileExistsEx;
	uintptr_t SFile_ReadFileEx2;
	uintptr_t SFile_LoadFileEx2;
	uintptr_t SFile_OpenFileAsArchive;
	uintptr_t SFile_GetLocale;
	uintptr_t SFile_GetFileCompressedSize;
	uintptr_t SFile_MemAlloc;

	bool isValide = false;
	HMODULE g_storm_dll;

	bool valid()
	{
		return isValide;
	}

	uintptr_t get_proc(uint32_t ord)
	{
		uintptr_t ptr = (uintptr_t)::GetProcAddress(g_storm_dll, (const char*)ord);
		if (!ptr)
			Message("Couldn't find " + std::to_string(ord) + "Storm.dll");
		return ptr;
	}

	bool load()
	{
		if (!g_storm_dll) return false;

		SFile_CloseArchive            = get_proc(252);		 if (!(SFile_CloseArchive))		       return false;
		SFile_CloseFile               = get_proc(253);		 if (!(SFile_CloseFile))		       return false;
		SFile_EnableDirectAccess      = get_proc(263);		 if (!(SFile_EnableDirectAccess))	   return false;
		SFile_GetFileArchive          = get_proc(264);		 if (!(SFile_GetFileArchive))		   return false;
		SFile_GetFileSize             = get_proc(265);		 if (!(SFile_GetFileSize))			   return false;
		SFile_OpenArchive             = get_proc(266);		 if (!(SFile_OpenArchive))			   return false;
		SFile_OpenFile                = get_proc(267);		 if (!(SFile_OpenFile))			       return false;
		SFile_OpenFileEx              = get_proc(268);		 if (!(SFile_OpenFileEx))			   return false;
		SFile_ReadFile                = get_proc(269);		 if (!(SFile_ReadFile))				   return false;
		SFile_SetBasePath             = get_proc(270);		 if (!(SFile_SetBasePath))			   return false;
		SFile_SetFilePointer          = get_proc(271);		 if (!(SFile_SetFilePointer))		   return false;
		SFile_SetLocale               = get_proc(272);	     if (!(SFile_SetLocale))			   return false;
		SFile_GetBasePath             = get_proc(273);		 if (!(SFile_GetBasePath))			   return false;
		SFile_GetArchiveName          = get_proc(275);		 if (!(SFile_GetArchiveName))	       return false;
		SFile_GetFileName             = get_proc(276);		 if (!(SFile_GetFileName))			   return false;
		SFile_GetArchiveInfo          = get_proc(277);		 if (!(SFile_GetArchiveInfo))		   return false;
		SFile_LoadFile                = get_proc(279);		 if (!(SFile_LoadFile))				   return false;
		SFile_UnloadFile              = get_proc(280);		 if (!(SFile_UnloadFile))			   return false;
		SFile_LoadFileEx              = get_proc(281);		 if (!(SFile_LoadFileEx))			   return false;
		SFile_ReadFileEx              = get_proc(287);		 if (!(SFile_ReadFileEx))			   return false;
		SFile_FileExists              = get_proc(288);		 if (!(SFile_FileExists))              return false;
		SFile_FileExistsEx            = get_proc(289);		 if (!(SFile_FileExistsEx))            return false;
		SFile_ReadFileEx2             = get_proc(291);		 if (!(SFile_ReadFileEx2))             return false;
		SFile_LoadFileEx2             = get_proc(292);		 if (!(SFile_LoadFileEx2))             return false;
		SFile_OpenFileAsArchive       = get_proc(293);		 if (!(SFile_OpenFileAsArchive))       return false;
		SFile_GetLocale               = get_proc(294);		 if (!(SFile_GetLocale))               return false;
		SFile_GetFileCompressedSize   = get_proc(296);		 if (!(SFile_GetFileCompressedSize))   return false;
		SFile_MemAlloc                = get_proc(401);		 if (!(SFile_MemAlloc))                return false;

		return true;
	}

	
	BOOL CloseArchive(HANDLE hArchive)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_CloseArchive, hArchive);
	}

	BOOL CloseFile(HANDLE hFile)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_CloseFile, hFile);
	}

	BOOL EnableDirectAccess(HANDLE hFile)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_EnableDirectAccess, hFile);
	}

	BOOL GetFileArchive(HANDLE hFile, HANDLE hArchive)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetFileArchive, hFile, hArchive);
	}

	DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetFileSize, hFile, lpFileSizeHigh);
	}

	BOOL OpenArchive(const char *archiveName, DWORD dwPriority, DWORD dwFlags, HANDLE *pArchiveHandle)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_OpenArchive, archiveName, dwPriority, dwFlags, pArchiveHandle);
	}

	BOOL OpenFile(const char *fileName, HANDLE *pFileHandle)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_OpenFile, fileName, pFileHandle);
	}

	BOOL OpenFileEx(HANDLE hArchive, const char *fileName, DWORD searchScope, HANDLE *pFileHandle)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_OpenFileEx, hArchive, fileName, searchScope, pFileHandle);
	}

	BOOL ReadFile(HANDLE hFile, void *pBuffer, DWORD nNumberOfBytesToRead, DWORD *pNumberOfBytesRead, LONG lpDistanceToMoveHigh)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_ReadFile, hFile, pBuffer, nNumberOfBytesToRead, pNumberOfBytesRead, lpDistanceToMoveHigh);
	}

	BOOL SetBasePath(const char *pathName)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_SetBasePath, pathName);
	}

	LONG SetFilePointer(HANDLE hFile, LONG filePos, LONG *filePosHigh, DWORD dwMethod)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_SetFilePointer, hFile, filePos, filePosHigh, dwMethod);
	}

	LCID SetLocale(LCID lcNewLocale)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_SetLocale, lcNewLocale);
	}

	BOOL GetBasePath(char *pBasePathBuffer, size_t bufferSize)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetBasePath, pBasePathBuffer, bufferSize);
	}

	BOOL GetArchiveName(HANDLE hArchive, char *pNameBuffer, size_t bufferSize)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetArchiveName, hArchive, pNameBuffer, bufferSize);
	}

	BOOL GetFileName(HANDLE hFile, char *pNameBuffer, size_t bufferSize)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetFileName, hFile, pNameBuffer, bufferSize);
	}

	BOOL GetArchiveInfo(HANDLE hArchive, int32 *a2, int32 *a3)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetArchiveInfo, hArchive, a2, a3);
	}

	BOOL LoadFile(const char *filePath, void **ppBuffer, size_t *pSize, size_t extraSizeToAlocate, LPOVERLAPPED pOverlapped)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_LoadFile, filePath, ppBuffer, pSize, extraSizeToAlocate, pOverlapped);
	}

	BOOL UnloadFile(void *pBuffer)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_UnloadFile, pBuffer);
	}

	BOOL LoadFileEx(HANDLE hArchive, const char *filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_LoadFileEx, hArchive, filePath, ppBuffer, pBufferSize, extraSize, searchScope, pOverlapped);
	}

	BOOL FileExists(const char *filePath)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_FileExists, filePath);
	}

	BOOL FileExistsEx(HANDLE hArchive, const char *filePath, DWORD searchScope)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_FileExistsEx, hArchive, filePath, searchScope);
	}

	BOOL LoadFileEx2(HANDLE hArchive, const char *filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped, int32 a8)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_LoadFileEx2, hArchive, filePath, ppBuffer, pBufferSize, extraSize, searchScope, pOverlapped, a8);
	}

	LCID GetLocale()
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetLocale);
	}

	DWORD GetFileCompressedSize(HANDLE hFile, DWORD *pSizeHigh)
	{
		if (!valid()) return false;
		return std_call<BOOL>(SFile_GetFileCompressedSize, hFile, pSizeHigh);
	}

	int32 MemAlloc(int32 a1, int32 a2, int32 a3, int32 a4)
	{
		if (!valid()) return false;
		return std_call<int32>(SFile_MemAlloc, a1, a2, a3, a4);
	}


	bool InitStormAPI()
	{
		g_storm_dll = GetModuleHandleA("Storm.dll");

		if (load())
		{
			isValide = true;
			return true;
		}
		return false;
	}
}