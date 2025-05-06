#pragma once
#include <iostream>
#include <Windows.h>

#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "fmod_vc.lib") // ���Ӽ� ��ũ

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
	FMOD::Channel* mainMusicChannel = nullptr;
	FMOD::Channel* effectChannel = nullptr;
};

extern SoundManager g_SoundManager;