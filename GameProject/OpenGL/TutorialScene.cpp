/*
@brief	�C���N���[�h
*/
#include "pch.h"

bool	TutorialScene::mSendContinueTutorialFlag = false;

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
TutorialScene::TutorialScene(const Scene& _nowScene)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mOperationExplanationBoard = new OperationExplanationBoard(Vector3(0, 200, -96000), Vector3::Zero, Tag::Other, Scene::tutorial);
	mVerticalMoveGroundExplanationBoard = new VerticalMoveGroundExplanationBoard(Vector3(0, 200,-92000), Vector3::Zero, Tag::Other, Scene::tutorial);
	mGoalLine = new GoalLine(Vector3(800, 150, -75800), Vector3::Zero, Tag::Other, Scene::tutorial);

	mSprite = new Sprite("Assets/forest.png");

	mMapCreate = new MapCreate();
	if (!mMapCreate->OpenFile())
	{
		mMapCreate->CreateGround();
		mMapCreate->CreateGlass();
		mMapCreate->CreateBlock();
		mMapCreate->CreateVerticalMoveGround();
		mMapCreate->CreateJump();
		mMapCreate->CreateLateralMoveGround();
		mPlayer = mMapCreate->CreatePlayer();
		mMapCreate->CreateUpBlock();
		mMapCreate->CreateRightGround();
		mMapCreate->CreateLeftGround();
		mMapCreate->CreateGoal();
	}

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::Other, Scene::tutorial);
	}

	PHYSICS->SortPhysicsData(mPlayer);

	mSendContinueTutorialFlag = false;
}

/*
@fn	�f�X�g���N�^
*/
TutorialScene::~TutorialScene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(tutorial);
	delete mSprite;
	delete mMapCreate;
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* TutorialScene::update(const InputState& _state)
{
	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			return new Stage01Scene(stage01);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mContinueTutorialFlag = true;
			mSendContinueTutorialFlag = mContinueTutorialFlag;
			
			return new ContinueScene(Continue);
		}
	}

	return this;
}