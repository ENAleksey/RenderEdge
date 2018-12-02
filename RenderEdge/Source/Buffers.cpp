#include "Buffers.h"

BufferLockData War3VBufferData;
BufferLockData War3IBufferData;

void VBuffer::Update(BufferLockData &Data, D3DVERTEXBUFFER_DESC &_Desc)
{
    Desc = _Desc;
    if(Buffer.Length() != Desc.Size)
    {
        Buffer.Allocate(Desc.Size);
        Buffer.ZeroMem();
    }

    Data.pRAMBuffer = (VOID*)(Buffer.CArray() + Data.OffsetToLock);
}

void IBuffer::Update(BufferLockData &Data, D3DINDEXBUFFER_DESC &_Desc)
{
    Desc = _Desc;
    if(Buffer.Length() != Desc.Size)
    {
        Buffer.Allocate(Desc.Size);
        Buffer.ZeroMem();
    }

    Data.pRAMBuffer = (VOID*)(Buffer.CArray() + Data.OffsetToLock);
}

VBuffer* War3VBuffer;
IBuffer* War3IBuffer;