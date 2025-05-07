#pragma once
#include <iostream>
#include <Windows.h>

#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "fmod_vc.lib") // 종속성 링크

class SoundManager
{
public:
	void Initialize();
	void Update();
	void PlayEffectSound(const char* fileName);
	void PlayMainMusic(const char* fileName);
	void Release();


protected:
	FMOD::System* system = nullptr;
	FMOD::Sound* sound = nullptr;
	FMOD::Sound* effect = nullptr;
	FMOD::Sound* music = nullptr;
	FMOD::Channel* mainMusicChannel = nullptr;
	FMOD::Channel* effectChannel = nullptr;
};

extern SoundManager g_SoundManager;