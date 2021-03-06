/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 右移動ブロックの座標
@param	_size 右移動ブロックのサイズ
@param	_objectTag 右移動ブロックのタグ
@param	_sceneTag シーンのタグ
*/
RightBlock::RightBlock(const Vector3& _pos, const Vector3& _size, const float _addPosX, const std::string _gpmeshName, const Tag& _objectTag, const ColliderTag& _colliderTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mElapseTime(0.0f)
	, mDifferencePos(0.0f)
	, mStart(0.0f)
	, mShakeFlag(false)
	, mInversionPos(Vector3::Zero)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mInitPos = Vector3(_pos.x, _pos.y, _pos.z);
	mEndPos = Vector3(_pos.x + _addPosX, _pos.y, _pos.z);
	mInversionPos = Vector3(_pos.x + 60, _pos.y, _pos.z);

	//生成したRightBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmMesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, _colliderTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;
}

/*
@fn		右移動ブロックのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void RightBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();
	//////////////////////////////////////
	//予知動作処理

	if (playerPos.z >= mPosition.z - 2040.0f)
	{
		mShakeFlag = true;
	}

	if (mShakeFlag)
	{
		if (mPosition.x >= mInversionPos.x)
		{
			mReversFlag = true;
		}
		else if (mPosition.x <= mInitPos.x)
		{
			mReversFlag = false;
		}

		if (mReversFlag == true)
		{
			/*Vector3 movePos = Vector3(mPosition + Vector3(50, 0, 0));
			mPosition = Vector3::Lerp(mPosition,movePos,0.1f);*/

			mVelocity.x = -RIGHT_SPEED;
		}
		else if (mReversFlag == false)
		{
			/*Vector3 movePos2 = Vector3(mPosition + Vector3(-50, 0, 0));
			mPosition = Vector3::Lerp(mPosition, movePos2, 0.1f);*/

			mVelocity.x = RIGHT_SPEED;
		}
	}
	/////////////////////////////////////////

	if (playerPos.z >= mPosition.z - 1800.0f)
	{
		mShakeFlag = false;
		mElapseTime += _deltaTime;
		mDifferencePos = mEndPos.x - mInitPos.x;
		mVelocity.x = Quartic::EaseIn(mElapseTime, mStart , mDifferencePos, TOTAL_TIME) * 0.02f;
		//mVelocity.x = RIGHT_SPEED;
	}

	if (mInitPos.x < mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPosition.x >= mEndPos.x)
	{
		mVelocity.x = 0;
	}

	if (Player::GetDeathFlag())
	{
		mElapseTime = 0.0f;
		mVelocity.x = 0;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			mElapseTime = 0.0f;
			mVelocity.x = 0;
			mPosition.x = mInitPos.x;
			mOriginalPosFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}