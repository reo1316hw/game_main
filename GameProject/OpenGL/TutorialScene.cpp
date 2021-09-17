/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_NowScene 現在のシーン
*/
TutorialScene::TutorialScene(const Scene& _NowScene)
	: mTransitionFlag(false)
{
	//環境光
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);
	//ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(AmbientLight);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_NowScene);

	mOperationExplanationBoard = new OperationExplanationBoard(Vector3(0, 200, -96000), Vector3::sZERO, Tag::Other, Scene::tutorial);
	mVerticalMoveGroundExplanationBoard = new VerticalMoveGroundExplanationBoard(Vector3(0, 200,-92000), Vector3::sZERO, Tag::Other, Scene::tutorial);
	mGoalLine = new GoalLine(Vector3(800, 150, -75800), Vector3::sZERO, Tag::Other, Scene::tutorial);

	mSprite = new Sprite("Assets/forest.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenTutorialFile();

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::Other, Scene::tutorial, mPlayer);
	}
}

/*
@fn	デストラクタ
*/
TutorialScene::~TutorialScene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(tutorial);
	delete mSprite;
	delete mMapCreate;
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* TutorialScene::UpdateScene(const InputState& _State)
{
	//次のシーンに遷移するタイミング
	const int NextSceneTiming = 80;

	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			return new Stage01Scene(stage01);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			mTransitionFlag = true;
			return new ContinueScene(Continue, tutorial, mTransitionFlag);
		}
	}

	return this;
}