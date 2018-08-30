//+-----------------------------------------------------------------------------
//| Inclusion guard
//+-----------------------------------------------------------------------------
#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>
#include <map>
#include <vector>
#include <string.h>
#include <windows.h>

#define INVALID_INDEX -1


template <class TYPE>
struct CONTAINER_NODE
{
	CONTAINER_NODE()
	{
		Name = "";
	}

	TYPE Data;
	std::string Name;
};


//+-----------------------------------------------------------------------------
//| Container class
//+-----------------------------------------------------------------------------
template <class TYPE>
class CONTAINER
{
	public:
		CONTAINER();
		CONTAINER(CONST CONTAINER<TYPE>& CopyObject);
		~CONTAINER();

		VOID Clear();

		VOID Reserve(INT Size);

		BOOL Add(CONST std::string& Name, CONST TYPE& NewObject);
		BOOL Remove(INT Index);
		BOOL Remove(CONST std::string& Name);
		BOOL Rename(INT Index, CONST std::string& NewName);
		BOOL Rename(CONST std::string& Name, CONST std::string& NewName);
		BOOL Replace(INT Index, CONST TYPE& NewObject);
		BOOL Replace(CONST std::string& Name, CONST TYPE& NewObject);

		CONST CONTAINER<TYPE>& operator =(CONST CONTAINER<TYPE>& CopyObject);

		TYPE& operator [](INT Index) CONST;
		TYPE& operator [](CONST std::string& Name) CONST;

		TYPE* Get(INT Index) CONST;
		TYPE* Get(CONST std::string& Name) CONST;

		INT GetSize() CONST;
		INT GetTotalSize() CONST;
		INT GetLastAddedIndex() CONST;
		std::string GetName(INT Index) CONST;
		INT GetIndex(CONST std::string& Name) CONST;

		BOOL ValidIndex(INT Index) CONST;

	protected:
		VOID Copy(CONST CONTAINER<TYPE>& CopyObject);

		INT GetFreeIndex();

		std::vector<CONTAINER_NODE<TYPE>*> DataList;
		std::map<std::string, INT> DataMap;
		std::list<INT> FreeIndexList;

		INT Size;
		INT LastAddedIndex;
};


//+-----------------------------------------------------------------------------
//| Constructor
//+-----------------------------------------------------------------------------
template <class TYPE>
CONTAINER<TYPE>::CONTAINER()
{
	Size = 0;
	LastAddedIndex = INVALID_INDEX;
}


//+-----------------------------------------------------------------------------
//| Copy constructor
//+-----------------------------------------------------------------------------
template <class TYPE>
CONTAINER<TYPE>::CONTAINER(CONST CONTAINER<TYPE>& CopyObject)
{
	Copy(CopyObject);
}


//+-----------------------------------------------------------------------------
//| Destructor
//+-----------------------------------------------------------------------------
template <class TYPE>
CONTAINER<TYPE>::~CONTAINER()
{
	Clear();
}


//+-----------------------------------------------------------------------------
//| Clears the container
//+-----------------------------------------------------------------------------
template <class TYPE>
VOID CONTAINER<TYPE>::Clear()
{
	INT i;

	for(i = 0; i < static_cast<INT>(DataList.size()); i++)
	{
		delete DataList[i];
	}

	DataList.clear();
	DataMap.clear();
	FreeIndexList.clear();

	Size = 0;
	LastAddedIndex = INVALID_INDEX;
}


//+-----------------------------------------------------------------------------
//| Reserves space in the container
//+-----------------------------------------------------------------------------
template <class TYPE>
VOID CONTAINER<TYPE>::Reserve(INT Size)
{
	DataList.reserve(Size);
}


//+-----------------------------------------------------------------------------
//| Adds an object to the container
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::Add(CONST std::string& Name, CONST TYPE& NewObject)
{
	INT Index;

	if(GetIndex(Name) != INVALID_INDEX) return FALSE;

	Index = GetFreeIndex();
	LastAddedIndex = Index;

	DataList[Index] = new CONTAINER_NODE<TYPE>();
	if(DataList[Index] == NULL) return FALSE;

	DataList[Index]->Data = NewObject;
	DataList[Index]->Name = Name;
	DataMap.insert(std::make_pair(Name, Index));

	Size++;

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Removes an object from the container
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::Remove(INT Index)
{
	std::map<std::string, INT>::iterator i;

	if(!ValidIndex(Index)) return FALSE;

	i = DataMap.find(DataList[Index]->Name);
	if(i != DataMap.end()) DataMap.erase(i);

	delete DataList[Index];
	DataList[Index] = NULL;

	FreeIndexList.push_back(Index);

	Size--;

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Removes an object from the container
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::Remove(CONST std::string& Name)
{
	return Remove(GetIndex(Name));
}


//+-----------------------------------------------------------------------------
//| Renames an object in the container
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::Rename(INT Index, CONST std::string& NewName)
{
	std::map<std::string, INT>::iterator i;

	if(!ValidIndex(Index)) return FALSE;

	if(DataList[Index]->Name == NewName) return TRUE;

	i = DataMap.find(NewName);
	if(i != DataMap.end()) return FALSE;

	i = DataMap.find(DataList[Index]->Name);
	if(i != DataMap.end()) DataMap.erase(i);

	DataMap.insert(std::make_pair(NewName, Index));
	DataList[Index]->Name = NewName;

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Renames an object in the container
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::Rename(CONST std::string& Name, CONST std::string& NewName)
{
	return Rename(GetIndex(Name), NewName);
}


//+-----------------------------------------------------------------------------
//| Replaces an object in the container
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::Replace(INT Index, CONST TYPE& NewObject)
{
	if(!ValidIndex(Index)) return FALSE;

	DataList[Index]->Data = NewObject;

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Replaces an object in the container
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::Replace(CONST std::string& Name, CONST TYPE& NewObject)
{
	return Replace(GetIndex(Name), NewObject);
}


//+-----------------------------------------------------------------------------
//| Copies another container
//+-----------------------------------------------------------------------------
template <class TYPE>
CONST CONTAINER<TYPE>& CONTAINER<TYPE>::operator =(CONST CONTAINER<TYPE>& CopyObject)
{
	Copy(CopyObject);

	return (*this);
}


//+-----------------------------------------------------------------------------
//| Returns an object from the container
//+-----------------------------------------------------------------------------
template <class TYPE>
TYPE& CONTAINER<TYPE>::operator [](INT Index) CONST
{
	return DataList[Index]->Data;
}


//+-----------------------------------------------------------------------------
//| Returns an object from the container
//+-----------------------------------------------------------------------------
template <class TYPE>
TYPE& CONTAINER<TYPE>::operator [](CONST std::string& Name) CONST
{
	return operator [](GetIndex(Name));
}


//+-----------------------------------------------------------------------------
//| Returns an object from the container
//+-----------------------------------------------------------------------------
template <class TYPE>
TYPE* CONTAINER<TYPE>::Get(INT Index) CONST
{
	if(!ValidIndex(Index)) return NULL;

	return &(DataList[Index]->Data);
}


//+-----------------------------------------------------------------------------
//| Returns an object from the container
//+-----------------------------------------------------------------------------
template <class TYPE>
TYPE* CONTAINER<TYPE>::Get(CONST std::string& Name) CONST
{
	return operator [](GetIndex(Name));
}


//+-----------------------------------------------------------------------------
//| Returns the nr of objects in the container
//+-----------------------------------------------------------------------------
template <class TYPE>
INT CONTAINER<TYPE>::GetSize() CONST
{
	return Size;
}


//+-----------------------------------------------------------------------------
//| Returns the total size of the container
//+-----------------------------------------------------------------------------
template <class TYPE>
INT CONTAINER<TYPE>::GetTotalSize() CONST
{
	return static_cast<INT>(DataList.size());
}


//+-----------------------------------------------------------------------------
//| Returns the index of the last added object
//+-----------------------------------------------------------------------------
template <class TYPE>
INT CONTAINER<TYPE>::GetLastAddedIndex() CONST
{
	return LastAddedIndex;
}


//+-----------------------------------------------------------------------------
//| Returns the name of a specific object
//+-----------------------------------------------------------------------------
template <class TYPE>
std::string CONTAINER<TYPE>::GetName(INT Index) CONST
{
	if(!ValidIndex(Index)) return "";

	return DataList[Index]->Name;
}


//+-----------------------------------------------------------------------------
//| Returns the index of a specific object
//+-----------------------------------------------------------------------------
template <class TYPE>
INT CONTAINER<TYPE>::GetIndex(CONST std::string& Name) CONST
{
	std::map<std::string, INT>::const_iterator i;

	i = DataMap.find(Name);
	if(i == DataMap.end()) return INVALID_INDEX;

	return i->second;
}


//+-----------------------------------------------------------------------------
//| Checks if an index is valid
//+-----------------------------------------------------------------------------
template <class TYPE>
BOOL CONTAINER<TYPE>::ValidIndex(INT Index) CONST
{
	if(Index < 0) return FALSE;
	if(Index >= static_cast<INT>(DataList.size())) return FALSE;
	if(DataList[Index] == NULL) return FALSE;

	return TRUE;
}


//+-----------------------------------------------------------------------------
//| Copies another container
//+-----------------------------------------------------------------------------
template <class TYPE>
VOID CONTAINER<TYPE>::Copy(CONST CONTAINER<TYPE>& CopyObject)
{
	INT i;
	INT ListSize;

	ListSize = static_cast<INT>(CopyObject.DataList.size());
	DataList.resize(ListSize, NULL);

	for(i = 0; i < ListSize; i++)
	{
		if(CopyObject.DataList[i] != NULL)
		{
			DataList[i] = new CONTAINER_NODE<TYPE>(*(CopyObject.DataList[i]));
		}
	}

	DataMap = CopyObject.DataMap;
	FreeIndexList = CopyObject.FreeIndexList;

	Size = CopyObject.Size;
	LastAddedIndex = CopyObject.LastAddedIndex;
}


//+-----------------------------------------------------------------------------
//| Creates a new free index for an object
//+-----------------------------------------------------------------------------
template <class TYPE>
INT CONTAINER<TYPE>::GetFreeIndex()
{
	INT FreeIndex;

	if(FreeIndexList.size() > 0)
	{
		FreeIndex = FreeIndexList.back();
		FreeIndexList.pop_back();
	}
	else
	{
		FreeIndex = static_cast<INT>(DataList.size());
		DataList.push_back(NULL);
	}

	return FreeIndex;
}


//+-----------------------------------------------------------------------------
//| End of inclusion guard
//+-----------------------------------------------------------------------------
#endif
