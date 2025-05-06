#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <codecvt>

#include "json.hpp"

using json = nlohmann::json;

class JsonManager
{
public:
	std::vector<int> GetIntagerData(const wchar_t* path, std::vector<std::wstring> dataNames);
	std::vector<int> GetIntagerData(std::wstring path, std::vector<std::wstring> dataNames);
};

extern JsonManager g_JsonManager;
