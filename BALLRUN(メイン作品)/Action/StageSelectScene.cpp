#include "StageSelectScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"

StageSelectScene::StageSelectScene(const Scene& _scene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);

	mNextSceneCount = 0;
}

StageSelectScene::~StageSelectScene()
{
}

SceneBase* StageSelectScene::update()
{
	mNextSceneCount++;

	if (mNextSceneCount >= 100)
	{
		return new Stage01Scene(stage01);
	}

	return this;
}
