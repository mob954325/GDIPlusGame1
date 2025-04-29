#pragma once
#include "GDIEngineLib/inc/Utility/GameObject.h"
#include "GDIEngineLib/inc//Utility/Vector2.h"
#include "Component/Collider.h"

class MainCamera : public GameObject
{
public:
	MainCamera() { Initialize(); }
	void Initialize() override;
	void UpdateImpl() override;
	void SetCameraTarget(GameObject* object);

	void OnColliderEnterImpl(GameObject* other) override;
	void OnColliderStayImpl(GameObject* other) override;
	void OnColliderExitImpl(GameObject* other) override;

	Vector2 moveVec = Vector2();
	Vector2 InvertCameraMoveVector();
	bool isMoved = false;
private:
	void UpdatePositionByTarget();

	Collider* collider;
	GameObject* target; // 카메라가 보는 타켓 오브젝트
	float speed = 20.0f;
};

