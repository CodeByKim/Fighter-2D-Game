#include "Framework.h"

Framework& Framework::GetInstance()
{
	static Framework instance;
	return instance;
}

Framework::Framework()
{

}