#pragma once

#include <Windows.h>
#include <d3d9.h>
#include "Vector.h"

struct BufferLockData
{
	UINT OffsetToLock;
	UINT SizeToLock;
	DWORD Flags;
	HANDLE Handle;
	VOID* pRAMBuffer;
	VOID* pVideoBuffer;
	bool Create;
};
extern BufferLockData War3VBufferData;
extern BufferLockData War3IBufferData;

class VBuffer
{
public:
    VBuffer(HANDLE _Handle)
    {
        Handle = _Handle;
    }

    void Update(BufferLockData &Data, D3DVERTEXBUFFER_DESC &_Desc);

    D3DVERTEXBUFFER_DESC Desc;  //DirectX description of buffer
    Vector<BYTE> Buffer;        //Raw data of buffer
    HANDLE Handle;              //DirectX handle to the object
};

//
// Software version of a DirectX index buffer
//
class IBuffer
{
public:
    IBuffer(HANDLE _Handle)
    {
        Handle = _Handle;
    }
    __forceinline DWORD GetIndex(UINT Index) const
    {
        if(Desc.Format == D3DFMT_INDEX16)
        {
            return ((WORD *)Buffer.CArray())[Index];
        }
        else
        {
            return ((DWORD *)Buffer.CArray())[Index];
        }
    }
    __forceinline DWORD Length() const
    {
        if(Desc.Format == D3DFMT_INDEX16)
        {
            return Buffer.Length() / sizeof(WORD);
        }
        else
        {
            return Buffer.Length() / sizeof(DWORD);
        }
    }

    void Update(BufferLockData &Data, D3DINDEXBUFFER_DESC &_Desc);

    D3DINDEXBUFFER_DESC Desc;   //DirectX description of buffer
    Vector<BYTE> Buffer;        //Raw data of buffer
    HANDLE Handle;              //DirectX handle to the object
};

extern VBuffer* War3VBuffer;
extern IBuffer* War3IBuffer;