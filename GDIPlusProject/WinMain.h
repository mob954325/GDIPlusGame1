#pragma once
#include "resource.h"
#include <windows.h>
#include <stdio.h>

// Manager =======================================
#include "Manager/GDIPlusManager.h"
#include "Scenes/MenuScene.h"
#include "DebugUtility.h"
#include "Manager/UtilityManager.h"

enum Scene
{
	MENU = 0,
	PLAY,
	END,
	SCENECOUNT
};