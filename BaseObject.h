#pragma once

#include "Library.h"

class BaseObject
{
public:
	virtual void			Update() = 0;

protected:
	std::wstring			mName;
	int						mId;
};