#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

namespace Storm
{
	bool Init();

	BOOL CloseArchive(HANDLE hArchive);
	BOOL CloseFile(HANDLE hFile);
	BOOL EnableDirectAccess(HANDLE hFile);
	BOOL GetFileArchive(HANDLE hFile, HANDLE* hArchive);
	DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
	BOOL OpenArchive(const std::string& archiveName, DWORD dwPriority, DWORD dwFlags, HANDLE *pArchiveHandle);
	BOOL OpenFile(const std::string& fileName, HANDLE *pFileHandle);
	BOOL OpenFileEx(HANDLE hArchive, const std::string& fileName, DWORD searchScope, HANDLE *pFileHandle);
	BOOL ReadFile(HANDLE hFile, void *pBuffer, DWORD nNumberOfBytesToRead, DWORD *pNumberOfBytesRead, LONG lpDistanceToMoveHigh);
	BOOL SetBasePath(const std::string& pathName);
	LONG SetFilePointer(HANDLE hFile, LONG filePos, LONG *filePosHigh, DWORD dwMethod);
	LCID SetLocale(LCID lcNewLocale);
	BOOL GetBasePath(char *pBasePathBuffer, size_t bufferSize);
	BOOL GetArchiveName(HANDLE hArchive, char *pNameBuffer, size_t bufferSize);
	BOOL GetFileName(HANDLE hFile, char *pNameBuffer, size_t bufferSize);
	BOOL GetArchiveInfo(HANDLE hArchive, int *a2, int *a3);
	BOOL LoadFile(const std::string& filePath, void **ppBuffer, size_t *pSize, size_t extraSizeToAlocate, LPOVERLAPPED pOverlapped);
	BOOL UnloadFile(void *pBuffer);
	BOOL LoadFileEx(HANDLE hArchive, const std::string& filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped);
	BOOL FileExists(const std::string& filePath);
	BOOL FileExistsEx(HANDLE hArchive, const std::string& filePath, DWORD searchScope);
	BOOL LoadFileEx2(HANDLE hArchive, const std::string& filePath, char **ppBuffer, size_t *pBufferSize, size_t extraSize, DWORD searchScope, LPOVERLAPPED pOverlapped, int a8);
	LCID GetLocale();
	DWORD GetFileCompressedSize(HANDLE hFile, DWORD *pSizeHigh);
}
