#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <SDKDDKVer.h>
#include <windows.h>
#include <memory.h>
#include <iostream>

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <chrono>
#include <timeapi.h>
#include <filesystem>

struct Position2D
{
	int x;
	int y;
};