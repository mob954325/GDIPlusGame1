#pragma once
#include "GDIEngineLib/inc/App/WinApp.h"

class GameApp :
	public WinApp
{
public:
	GameApp() = default;
	~GameApp() = default;

	virtual void Initialize() override;
	virtual void Shutdown() override;

};