#pragma once

#include "Library.h"

class Framework
{
public:
	static Framework& GetInstance();
private:
	Framework();
};