/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 1マス右移動床の座標
@param	_size 1マス右移動床のサイズ
@param	_objectTag 1マス右移動床のタグ
@param	_sceneTag シーンのタグ
*/
RightGround::RightGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mInitPos = Vector3(_pos.x, _pos.y, _pos.z);
	mEndPos = Vector3(_pos.x + 200, _pos.y, _pos.z);

	//生成したRightOneBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::rightGroundTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;
}

/*
@fn		1マス右移動床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void RightGround::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

	if (playerPos.z >= mPosition.z - 600.0f)
	{
		mVelocity.x = RIGHT_SPEED;
	}

	if (mPosition.x >= mEndPos.x)
	{
		mVelocity.x = 0;
	}

	if (mInitPos.x < mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (Player::GetDeathFlag())
	{
		mVelocity.x = 0;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			mVelocity.x = 0;
			mPosition.x = mInitPos.x;
			mOriginalPosFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}
