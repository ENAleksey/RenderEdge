#pragma once

#include <Windows.h>
#include "int_t.h"

namespace Storm
{

	bool InitStormAPI();

	BOOL CloseArchive(HANDLE hArchive);
	BOOL CloseFile(HANDLE hFile);
	BOOL EnableDirectAccess(HANDLE hFile);
	BOOL GetFileArchive(HANDLE hFile, HANDLE hArchive);
	DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
	BOOL OpenArchive(const char *archiveName, DWORD dwPriority, DWORD dwFlags, HANDLE *pArchiveHandle);
	BOOL OpenFile(const char *fileName, HANDLE *pFileHandle);
	BOOL OpenFileEx(HANDLE hArchive, const char *fileName, DWORD searchScope, HANDLE *pFileHandle);
	BOOL ReadFile(HANDLE hFile, void *pBuffer, DWORD nNumberOfBytesToRead, DWORD *pNumberOfBytesRead, LONG lpDistanceToMoveHigh);
	BOOL SetBasePath(const char *pathName);
	LONG SetFilePointer(HANDLE hFile, LONG filePos, LONG *filePosHigh, DWORD dwMethod);
	LCID SetLocale(LCID lcNewLocale);
	BOOL GetBasePath(char *pBasePathBuffer, size_t bufferSize);
	BOOL GetArchiveName(HANDLE hArchive, char *pNameBuffer, size_t bufferSize);
	BOOL GetFileName(HANDLE hFile, char *pNameBuffer, size_t bufferSize);
	BOOL GetArchiveInfo(HANDLE hArchive, int32 *a2, int32 *a3);
	BOOL LoadFile(const char *filePath, void **ppBuffer, size_t *pSize, size_t extraSizeToAlocate, LPOVERLAPPED pOverlapped);
	BOOL UnloadFile(void *pBuffer);
	BOOL LoadFileEx(HANDLE hArchive, const char *filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped);
	BOOL FileExists(const char *filePath);
	BOOL FileExistsEx(HANDLE hArchive, const char *filePath, DWORD searchScope);
	BOOL LoadFileEx2(HANDLE hArchive, const char *filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped, int32 a8);
	LCID GetLocale();
	int32 MemAlloc(int32 a1, int32 a2, int32 a3, int32 a4);
}
