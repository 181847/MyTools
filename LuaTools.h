#pragma once
#include "DLLTools.h"

// this head file contain some tools for writing c module for lua

// LuaPointerContainer is a struct that store the pointer which is created in 
// the C/C++ enviroment, and the pointer do not need C/C++ to free or delete,
// because the inner function 'cleaner' will be called when the struct is delete by the 
// lua, and the 'cleaner' is defined as deleting the pointer itself.
// However, the cleaner is public, and can be replaced by the lambda,
// you can modify it whatever you want.
template<typename T>
struct LuaPointerContainer
{
	T * pointer;
	// using the cleaner to free the memeroy in the pointer.
	std::function<void(void)> cleaner;
	LuaPointerContainer()
	{
		cleaner = [&this]() {
			delete this->pointer;
			DEBUG_MESSAGE("Mesh Data has been cleaned.");
		};
	}
	~LuaPointerContainer()
	{
		cleaner(pointer);
	}

	// reload '->'
	T* operator->() const
	{
		return pointer;
	}

	void setPointer(T * p)
	{
		pointer = p;
	}
};
