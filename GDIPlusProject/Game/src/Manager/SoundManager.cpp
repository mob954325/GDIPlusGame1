#include "Manager/SoundManager.h"

SoundManager g_SoundManager;

void SoundManager::Initialize()
{
	// FMOD �ý��� �ʱ�ȭ
	if (FMOD::System_Create(&system) != FMOD_OK) {
		std::cerr << "FMOD �ý��� ���� ����!" << std::endl;
		return;
	}
	system->init(512, FMOD_INIT_NORMAL, nullptr);
}

void SoundManager::Update()
{
	// ���� ������ ���� �������� �ý��� ������Ʈ ȣ��
	system->update();

	// �ʿ� �� ä�� ���¸� Ȯ���ϰ�, ȿ������ ���� �Ŀ� ���� �۾��� �� �� �ֽ��ϴ�.
	bool isEffectPlaying = false;
	if (effectChannel) {
		effectChannel->isPlaying(&isEffectPlaying);
		if (!isEffectPlaying) {
			//std::cout << "ȿ������ ����Ǿ����ϴ�." << std::endl;
		}
	}
}

void SoundManager::PlayEffectSound(const char* fileName)
{
	FMOD::Sound* effect = nullptr;
	if (system->createSound(fileName, FMOD_DEFAULT, nullptr, &effect) != FMOD_OK) {
		std::cerr << "ȿ���� �ε� ����!" << std::endl;
		return;
	}

	// ȿ������ ���ο� ä�ο��� ��� (���� ���� ä�ΰ� �и�)
	FMOD::Channel* newEffectChannel = nullptr;
	system->playSound(effect, nullptr, false, &effectChannel);
}

void SoundManager::PlayMainMusic(const char* fileName)
{
	FMOD::Sound* music = nullptr;
	if (system->createSound(fileName, FMOD_LOOP_NORMAL, nullptr, &music) != FMOD_OK) {
		std::cerr << "���� ���� �ε� ����!" << std::endl;
		return;
	}

	// ���� ������ ����ϰ�, ä���� mainMusicChannel�� ����
	system->playSound(music, nullptr, false, &mainMusicChannel);
}

void SoundManager::Release()
{
	sound->release();
	system->close();
	system->release();
}
