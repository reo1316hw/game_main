#pragma once
#include "GameObject.h"

class UpBlock_02 : public GameObject
{
public:
	UpBlock_02(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~UpBlock_02() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	//�@�ړ���
	Vector3 tmpPos;

	const float UP_SPEED = 10;
};