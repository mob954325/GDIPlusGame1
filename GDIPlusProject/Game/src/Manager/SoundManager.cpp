#include "Manager/SoundManager.h"

SoundManager g_SoundManager;

void SoundManager::Initialize()
{
	// FMOD 시스템 초기화
	if (FMOD::System_Create(&system) != FMOD_OK) {
		std::cerr << "FMOD 시스템 생성 실패!" << std::endl;
		return;
	}
	system->init(512, FMOD_INIT_NORMAL, nullptr);
}

void SoundManager::Update()
{
	// 게임 루프나 메인 루프에서 시스템 업데이트 호출
	system->update();

	// 필요 시 채널 상태를 확인하고, 효과음이 끝난 후에 다음 작업을 할 수 있습니다.
	bool isEffectPlaying = false;
	if (effectChannel) {
		effectChannel->isPlaying(&isEffectPlaying);
		if (!isEffectPlaying) {
			//std::cout << "효과음이 종료되었습니다." << std::endl;
		}
	}
}

void SoundManager::PlayEffectSound(const char* fileName)
{
	if (effect) 
	{
		effect->release();  // 이전 사운드를 메모리에서 해제
		effect = nullptr;
	}

	if (system->createSound(fileName, FMOD_DEFAULT, nullptr, &effect) != FMOD_OK) {
		std::cerr << "효과음 로드 실패!" << std::endl;
		return;
	}

	system->playSound(effect, nullptr, false, &effectChannel);
}

void SoundManager::PlayMainMusic(const char* fileName)
{
	music = nullptr;
	if (system->createSound(fileName, FMOD_LOOP_NORMAL, nullptr, &music) != FMOD_OK) {
		std::cerr << "메인 음악 로드 실패!" << std::endl;
		return;
	}

	// 메인 음악을 재생하고, 채널을 mainMusicChannel에 저장
	system->playSound(music, nullptr, false, &mainMusicChannel);
}

void SoundManager::Release()
{
	if (effect)
	{
		effect->release();
		effect = nullptr;
	}
	sound->release();
	music->release();
	system->close();
	system->release();
}
