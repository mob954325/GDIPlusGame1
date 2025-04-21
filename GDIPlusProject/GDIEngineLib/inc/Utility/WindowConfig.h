#pragma once
class WindowConfig
{
public:
	WindowConfig() = default;
	~WindowConfig() = default;
	int windowWidth = 0;
	int windowHeight = 0;
};

extern WindowConfig g_WindowConfig;