/*
@brief	インクルード
*/
#include "pch.h"

//自身のインスタンスの初期化
GameObjectManager* GameObjectManager::mManager = nullptr;

/*
@fn インスタンスを生成
*/
void GameObjectManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		mManager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

/*
@fn インスタンスを削除
*/
void GameObjectManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		delete mManager;
		mManager = nullptr;
	}
}

/*
@brief  ゲームオブジェクトのアップデート処理
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{

	mUpdatingGameObject = true;

	// カメラを更新する
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// チュートリアルを更新する
	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->Update(_deltaTime);
	}

	// ステージ１を更新する
	for (auto stage01Object : mStage01Objects)
	{
		stage01Object->Update(_deltaTime);
	}

	// ステージ２を更新する
	for (auto stage02Object : mStage02Objects)
	{
		stage02Object->Update(_deltaTime);
	}

	mUpdatingGameObject = false;

	//待機中のオブジェクトを更新中オブジェクトに追加
	for (auto pending : mPendingGameObjects)
	{
		pending->ComputeWorldTransform();
		if (pending->GetScene() == SceneBase::Scene::tutorial)
		{
			mTutorialObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::stage01)
		{
			mStage01Objects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::stage02)
		{
			mStage02Objects.emplace_back(pending);
		}
	}
	mPendingGameObjects.clear();
}
/*
@brief  ゲームオブジェクトの入力処理
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	mUpdatingGameObject = true;

	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->ProcessInput(_state);
	}

	for (auto stage01Object : mStage01Objects)
	{
		stage01Object->ProcessInput(_state);
	}

	for (auto stage02Object : mStage02Objects)
	{
		stage02Object->ProcessInput(_state);
	}

	mUpdatingGameObject = false;
}

/*
@brief  ゲームオブジェクトの追加
@param	追加するGameObjectクラスのポインタ
*/
void GameObjectManager::AddGameObject(GameObject* _object)
{
	if (mUpdatingGameObject)
	{
		mPendingGameObjects.emplace_back(_object);
	}
	else
	{
		switch (_object->GetTag())
		{
		case Camera:
			mCameraObjects.emplace_back(_object);
			break;
		}

		switch (_object->GetScene())
		{
		case SceneBase::tutorial:
			mTutorialObjects.emplace_back(_object);
			break;
		case SceneBase::stage01:
			mStage01Objects.emplace_back(_object);
			break;
		case SceneBase::stage02:
			mStage02Objects.emplace_back(_object);
			break;
		}
	}
}

/*
@brief  ゲームオブジェクトの削除
@param	削除するGameObjectクラスのポインタ
*/
void GameObjectManager::RemoveGameObject(GameObject * _object)
{
	auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), _object);
	if (iter != mPendingGameObjects.end())
	{
		std::iter_swap(iter, mPendingGameObjects.end() - 1);
		mPendingGameObjects.pop_back();
	}

	iter = std::find(mTutorialObjects.begin(), mTutorialObjects.end(), _object);
	if (iter != mTutorialObjects.end())
	{
		std::iter_swap(iter, mTutorialObjects.end() - 1);
		mTutorialObjects.pop_back();
	}

	iter = std::find(mStage01Objects.begin(), mStage01Objects.end(), _object);
	if (iter != mStage01Objects.end())
	{
		std::iter_swap(iter, mStage01Objects.end() - 1);
		mStage01Objects.pop_back();
	}

	iter = std::find(mStage02Objects.begin(), mStage02Objects.end(), _object);
	if (iter != mStage02Objects.end())
	{
		std::iter_swap(iter, mStage02Objects.end() - 1);
		mStage02Objects.pop_back();
	}


}

void GameObjectManager::RemoveGameObjects(SceneBase::Scene _scene)
{
	switch (_scene)
	{
	case SceneBase::tutorial:

		while (!mTutorialObjects.empty())
		{
			delete mTutorialObjects.back();
		}
		break;

	case SceneBase::stage01:

		while (!mStage01Objects.empty())
		{
			delete mStage01Objects.back();
		}
		break;

	case SceneBase::stage02:
		while (!mStage02Objects.empty())
		{
			delete mStage02Objects.back();
		}
		break;
	}
}

/*
@brief 使用したすべてのゲームオブジェクトを解放する
@detail シーン遷移の際に使用される。GameObject内の再利用フラグが建っているオブジェクトは解放しない
*/
//void GameObjectManager::RemoveAllUsedGameObject()
//{
//	std::vector<GameObject*> reUseObjects;
//
//	while (!gameObjects.empty())
//	{
//		GameObject* obj = gameObjects.back();
//		if (obj->GetReUseGameObject())
//		{
//			reUseObjects.push_back(obj);
//			gameObjects.pop_back();
//			continue;
//		}
//		delete obj;
//	}
//
//	while (!cameraObjects.empty())
//	{
//		GameObject* obj = cameraObjects.back();
//		if (obj->GetReUseGameObject())
//		{
//			reUseObjects.push_back(obj);
//			cameraObjects.pop_back();
//			continue;
//		}
//		delete obj;
//	}
//}

//GameObject * GameObjectManager::FindGameObject(Tag _tag)
//{
//	for (auto itr : gameObjects)
//	{
//		if (itr->GetTag() == _tag)
//		{
//			return itr;
//		}
//	}
//
//	return nullptr;
//}

//std::vector<GameObject*> GameObjectManager::FindGameObjects(Tag _tag)
//{
//	std::vector<GameObject*> ret;
//	for (auto itr : gameObjects)
//	{
//		if (itr->GetTag() == _tag)
//		{
//			ret.push_back(itr);
//		}
//	}
//	return ret;
//}


GameObjectManager::GameObjectManager()
	: mUpdatingGameObject(false)
{
}


GameObjectManager::~GameObjectManager()
{
	/*while (!gameObjects.empty())
	{
		delete gameObjects.back();
	}*/
}