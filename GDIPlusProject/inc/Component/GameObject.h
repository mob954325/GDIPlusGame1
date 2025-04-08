﻿#pragma once
#include "Component/SpriteRenderer.h"
#include "Component/Transform.h"

#include <string.h>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void SetDefault();
	void SetName(wchar_t* targetName);
	void GetName(wchar_t** bufferPtr);
public:
	wchar_t* name;
	Transform transform;
};

