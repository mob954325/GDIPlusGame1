#pragma once
#include <iostream>
#include <Windows.h>

class WinApp
{
public:
	WinApp();
	virtual ~WinApp();
	static WinApp* m_pInstance;

private:
	HINSTANCE		m_hInstance;
	int				m_Width = 1024;
	int				m_Height = 768;
	std::wstring	m_WindowName = L"GDIEngineWindowClass";
	std::wstring	m_TitleName = L"Default Title Name";
	std::string		m_ModulePath;
	std::string		m_WorkingPath;
	HWND			m_hWnd;
public:
	virtual void Initialize();
	virtual void Shutdown();
	virtual void MessageProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Run();
	void InitConsole();
	void ShutdownConsole();
private:
	void Update();
	void Render();

};