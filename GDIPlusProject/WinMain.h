#pragma once
#include "resource.h"

#include <windows.h>
#include <stdio.h>

// Manager =======================================

#include "Manager/GDIPlusManager.h"
#include "./inc/Scenes/MenuScene.h"

// Libraries ====================================
#include "./inc/GameTime.h"
#pragma comment(lib, "./lib/GameTime.lib")

#include "./inc/Renderer.h"
#pragma comment(lib, "./lib/Renderer.lib")

#include "./inc/Input.h"
#pragma comment(lib, "./lib/Input.lib")

enum Scene
{
	MENU = 0,
	PLAY,
	END,
	SCENECOUNT
};