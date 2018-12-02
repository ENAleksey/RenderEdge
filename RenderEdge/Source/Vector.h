#pragma once
//#pragma warning(disable : 4700)

template <class T> class Vector
{
public:
    Vector()
    {
        _Data = NULL;
        _Length = 0;
        _Capacity = 0;
    }

    explicit Vector(unsigned int Size)
    {
        _Data = new T[Size];
        _Length = Size;
        _Capacity = Size;
    }

    ~Vector()
    {
        if(_Data != NULL)
        {
            delete[] _Data;
        }
    }
    
    //
    // Memory
    //
    void FreeMemory()
    {
        if(_Data != NULL)
        {
            delete[] _Data;
            _Data = NULL;
        }
        _Length = 0;
        _Capacity = 0;
    }

    void DeleteMemory()
    {
        if(_Data != NULL)
        {
            for(UINT Index = 0; Index < _Length; Index++)
            {
                delete _Data[Index];
            }
            delete[] _Data;
            _Data = NULL;
        }
        _Length = 0;
        _Capacity = 0;
    }

    //
    // Windows has claimed the nice name "ZeroMemory" for its own uses
    //
    void ZeroMem()
    {
        if(_Length > 0)
        {
            memset(_Data, 0, _Length * sizeof(T));
        }
    }

    void Allocate(unsigned int Size)
    {
        if(Size == 0)
        {
            FreeMemory();
        }
        else
        {
            if(_Data != NULL)
            {
                delete[] _Data;
            }
            _Data = new T[Size];
            _Length = Size;
            _Capacity = Size;
        }
    }

    __forceinline T& operator [] (unsigned int k)
    {
        return _Data[k];
    }
    __forceinline T& operator [] (int k) 
    {
        return _Data[k];
    }
    __forceinline const T& operator [] (unsigned int k) const
    {
        return _Data[k];
    }
    __forceinline const T& operator [] (int k) const
    {
        return _Data[k];
    }
    __forceinline unsigned int Length() const
    {
        return _Length;
    }
    __forceinline T* CArray()
    {
        return _Data;
    }
    __forceinline const T* CArray() const
    {
        return _Data;
    }
    __forceinline T& RandomElement()
    {
        return _Data[rand() % _Length];
    }
    __forceinline const T& RandomElement() const
    {
        return _Data[rand() % _Length];
    }
    __forceinline T& Last()
    {
        return _Data[_Length - 1];
    }
    __forceinline const T& Last() const
    {
        return _Data[_Length - 1];
    }
    __forceinline T& First()
    {
        return _Data[0];
    }
    __forceinline const T& First() const
    {
        return _Data[0];
    }
    __forceinline T* Begin()
    {
        return _Data;
    }
    __forceinline const T* Begin() const
    {
        return _Data;
    }
    __forceinline T* End()
    {
        return _Data + _Length;
    }
    __forceinline const T* End() const
    {
        return _Data + _Length;
    }

protected:
    T *_Data;
    unsigned int _Length;
    unsigned int _Capacity;
};

//#pragma warning(default : 4700)