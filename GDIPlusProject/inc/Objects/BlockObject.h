#pragma once
#include "Objects/GameObject.h"
#include "Component/SpriteCollider.h"

// TODO
// 블록 오브젝트 만들기
// 맵 생성시 콜라이더 바운드 설정을 하고
// 플레이어가 닿는 위치 -> 아래 위 왼쪽 오른쪽을 감지해서
// 감지별로 다르게 설정하기
// 위 -> isground 활성화
// 아래 -> isground 비활성화

class BlockObject : public GameObject
{
public:
	SpriteCollider* collider;

	void Initialize() override;
	void Update() override;
	void Render(Gdiplus::Graphics* graphics) override;

	// Event
	void OnColliderOverlap(GameObject* other) override;
	void OnColliderExit(GameObject* other) override;

	void SpawnBlock(RECT bound, Vector2 position);
};