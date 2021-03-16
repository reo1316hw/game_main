#pragma once
#include "SceneBase.h"
#include "SpriteComponent.h"
#include "Shader.h"

class TitleScene : public SceneBase
{
public:
	TitleScene(const Scene& _scene);
	~TitleScene();

	SceneBase* update() override;
	void       draw() override;
private:
	//Texture* mEmissiveTexture;
	Sprite* sprite;
	// 入力管理クラス
	InputSystem* inputSystem;

	int count;
};

