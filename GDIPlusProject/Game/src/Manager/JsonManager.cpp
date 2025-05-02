#include "Manager/JsonManager.h"

JsonManager g_JsonManager;

std::vector<int> JsonManager::GetIntagerData(const wchar_t* path, std::vector<std::wstring> keys)
{
	std::ifstream file(path, std::ios::in);

	if (!file.is_open())
	{
		printf("No json found at %ws", path);
		return {};
	}

	json j;
	file >> j;
	json* current = &j;

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	// 매개 변수로 전달받은 데이터 찾기
	for (const auto& key : keys)
	{
		std::string utf8Key = converter.to_bytes(key);

		// json 배열이면
		if (current->is_array())
		{
			bool found = false;

			for (auto& item : *current)
			{
				if (item.contains(utf8Key))
				{
					current = &item[utf8Key];
					found = true;
					break;
				}
			}

			if (!found)
			{
				wprintf(L"Key %s not found in any array element.\n", key.c_str());
				return {};
			}
		}
		else if (current->contains(utf8Key))
		{
			current = &(*current)[utf8Key];
		}
		else
		{
			wprintf(L"Key %s not found.\n", key.c_str());
			return {};
		}
	}

	// 컨테이너로 해당 데이터 복사
	std::vector<int> dataContainer;
	if (current->is_number_integer())
	{
		dataContainer.push_back(current->get<int>());
	}
	else if (current->is_array())
	{
		const auto& data = *current;
		dataContainer.insert(dataContainer.end(), data.begin(), data.end());
	}
	else
	{
		printf("Target is neither integer nor array of integers.\n");
	}

	return dataContainer;
}