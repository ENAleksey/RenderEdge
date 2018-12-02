#include "Storm.h"
#include "fp_call.h"

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

	bool bValid = false;
	HMODULE hStormDll;

	bool IsValid()
	{
		return bValid;
	}

	uintptr_t GetProc(uint32_t ord)
	{
		return (uintptr_t)GetProcAddress(hStormDll, (const char*)ord);
	}

	bool load()
	{
		if (!hStormDll)
			return false;

		SFile_CloseArchive				= GetProc(252);		 if (!(SFile_CloseArchive))				return false;
		SFile_CloseFile					= GetProc(253);		 if (!(SFile_CloseFile))				return false;
		SFile_EnableDirectAccess		= GetProc(263);		 if (!(SFile_EnableDirectAccess))		return false;
		SFile_GetFileArchive			= GetProc(264);		 if (!(SFile_GetFileArchive))			return false;
		SFile_GetFileSize				= GetProc(265);		 if (!(SFile_GetFileSize))				return false;
		SFile_OpenArchive				= GetProc(266);		 if (!(SFile_OpenArchive))				return false;
		SFile_OpenFile					= GetProc(267);		 if (!(SFile_OpenFile))					return false;
		SFile_OpenFileEx				= GetProc(268);		 if (!(SFile_OpenFileEx))				return false;
		SFile_ReadFile					= GetProc(269);		 if (!(SFile_ReadFile))					return false;
		SFile_SetBasePath				= GetProc(270);		 if (!(SFile_SetBasePath))				return false;
		SFile_SetFilePointer			= GetProc(271);		 if (!(SFile_SetFilePointer))			return false;
		SFile_SetLocale					= GetProc(272);	     if (!(SFile_SetLocale))				return false;
		SFile_GetBasePath				= GetProc(273);		 if (!(SFile_GetBasePath))				return false;
		SFile_GetArchiveName			= GetProc(275);		 if (!(SFile_GetArchiveName))			return false;
		SFile_GetFileName				= GetProc(276);		 if (!(SFile_GetFileName))				return false;
		SFile_GetArchiveInfo			= GetProc(277);		 if (!(SFile_GetArchiveInfo))			return false;
		SFile_LoadFile					= GetProc(279);		 if (!(SFile_LoadFile))					return false;
		SFile_UnloadFile				= GetProc(280);		 if (!(SFile_UnloadFile))				return false;
		SFile_LoadFileEx				= GetProc(281);		 if (!(SFile_LoadFileEx))				return false;
		SFile_ReadFileEx				= GetProc(287);		 if (!(SFile_ReadFileEx))				return false;
		SFile_FileExists				= GetProc(288);		 if (!(SFile_FileExists))				return false;
		SFile_FileExistsEx				= GetProc(289);		 if (!(SFile_FileExistsEx))				return false;
		SFile_ReadFileEx2				= GetProc(291);		 if (!(SFile_ReadFileEx2))				return false;
		SFile_LoadFileEx2				= GetProc(292);		 if (!(SFile_LoadFileEx2))				return false;
		SFile_OpenFileAsArchive			= GetProc(293);		 if (!(SFile_OpenFileAsArchive))		return false;
		SFile_GetLocale					= GetProc(294);		 if (!(SFile_GetLocale))				return false;
		SFile_GetFileCompressedSize		= GetProc(296);		 if (!(SFile_GetFileCompressedSize))	return false;

		bValid = true;

		return true;
	}

	
	BOOL CloseArchive(HANDLE hArchive)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_CloseArchive, hArchive);
	}

	BOOL CloseFile(HANDLE hFile)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_CloseFile, hFile);
	}

	BOOL EnableDirectAccess(HANDLE hFile)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_EnableDirectAccess, hFile);
	}

	BOOL GetFileArchive(HANDLE hFile, HANDLE* hArchive)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetFileArchive, hFile, hArchive);
	}

	DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetFileSize, hFile, lpFileSizeHigh);
	}

	BOOL OpenArchive(const std::string& archiveName, DWORD dwPriority, DWORD dwFlags, HANDLE *pArchiveHandle)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_OpenArchive, archiveName.c_str(), dwPriority, dwFlags, pArchiveHandle);
	}

	BOOL OpenFile(const std::string& fileName, HANDLE *pFileHandle)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_OpenFile, fileName.c_str(), pFileHandle);
	}

	BOOL OpenFileEx(HANDLE hArchive, const std::string& fileName, DWORD searchScope, HANDLE *pFileHandle)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_OpenFileEx, hArchive, fileName.c_str(), searchScope, pFileHandle);
	}

	BOOL ReadFile(HANDLE hFile, void *pBuffer, DWORD nNumberOfBytesToRead, DWORD *pNumberOfBytesRead, LONG lpDistanceToMoveHigh)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_ReadFile, hFile, pBuffer, nNumberOfBytesToRead, pNumberOfBytesRead, lpDistanceToMoveHigh);
	}

	BOOL SetBasePath(const std::string& pathName)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_SetBasePath, pathName.c_str());
	}

	LONG SetFilePointer(HANDLE hFile, LONG filePos, LONG *filePosHigh, DWORD dwMethod)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_SetFilePointer, hFile, filePos, filePosHigh, dwMethod);
	}

	LCID SetLocale(LCID lcNewLocale)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_SetLocale, lcNewLocale);
	}

	BOOL GetBasePath(char *pBasePathBuffer, size_t bufferSize)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetBasePath, pBasePathBuffer, bufferSize);
	}

	BOOL GetArchiveName(HANDLE hArchive, char *pNameBuffer, size_t bufferSize)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetArchiveName, hArchive, pNameBuffer, bufferSize);
	}

	BOOL GetFileName(HANDLE hFile, char *pNameBuffer, size_t bufferSize)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetFileName, hFile, pNameBuffer, bufferSize);
	}

	BOOL GetArchiveInfo(HANDLE hArchive, int *a2, int *a3)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetArchiveInfo, hArchive, a2, a3);//
	}

	BOOL LoadFile(const std::string& filePath, void **ppBuffer, size_t *pSize, size_t extraSizeToAlocate, LPOVERLAPPED pOverlapped)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_LoadFile, filePath.c_str(), ppBuffer, pSize, extraSizeToAlocate, pOverlapped);
	}

	BOOL UnloadFile(void *pBuffer)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_UnloadFile, pBuffer);
	}

	BOOL LoadFileEx(HANDLE hArchive, const std::string& filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_LoadFileEx, hArchive, filePath.c_str(), ppBuffer, pBufferSize, extraSize, searchScope, pOverlapped);
	}

	BOOL FileExists(const std::string& filePath)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_FileExists, filePath.c_str());
	}

	BOOL FileExistsEx(HANDLE hArchive, const std::string& filePath, DWORD searchScope)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_FileExistsEx, hArchive, filePath.c_str(), searchScope);
	}

	BOOL LoadFileEx2(HANDLE hArchive, const std::string& filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped, int a8)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_LoadFileEx2, hArchive, filePath.c_str(), ppBuffer, pBufferSize, extraSize, searchScope, pOverlapped, a8);
	}

	LCID GetLocale()
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetLocale);
	}

	DWORD GetFileCompressedSize(HANDLE hFile, DWORD *pSizeHigh)
	{
		if (!IsValid()) return false;
		return std_call<BOOL>(SFile_GetFileCompressedSize, hFile, pSizeHigh);
	}


	bool Init()
	{
		hStormDll = GetModuleHandleW(L"Storm.dll");
		if (!hStormDll)
			return false;

		if (!load())
			return false;

		return true;
	}
}