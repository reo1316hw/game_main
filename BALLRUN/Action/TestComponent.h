#pragma once
#include "Component.h"

//左に移動し続けるGameObjectの補助クラス
class TestComponent :
	public Component
{
public:
	TestComponent(GameObject* _owner, int _updateOrder = 100);
	~TestComponent();

	void Update(float _deltaTime)override;
};

