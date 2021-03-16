#pragma once
#include "GameObject.h"

//class InvisibleMeshComponent;

class Glass : public GameObject
{
public:
	Glass(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~Glass() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	//InvisibleMeshComponent* invisibleMeshComponent;

	int count;

	// 落ちるスピード
	const float DOWN_SPEED = 100.0f;

	void OnCollision(const GameObject& _hitObject)override;
};