#include "pch.h"

/*
@fn	コンストラクタ
*/
MainCameraObject::MainCameraObject() 
	: GameObject(SceneBase::other,Tag::Camera,true)
{
	SetPosition(Vector3(0,0,-110000));
	mTag = Tag::Camera;
}

/*
@fn	デストラクタ
*/
MainCameraObject::~MainCameraObject()
{
}

/*
@fn		このクラスはポーズ中に別クラスから更新関数を呼ばれることがある
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	mPosition = mOffsetPos + mLerpObject;

	SetPosition(mPosition);
	Matrix4 view = Matrix4::CreateLookAt(mPosition, mLerpObject, Vector3::UnitY);
	RENDERER->SetViewMatrix(view);
}

/*
@param _offset　見たい座標との差
@param _parentPos　見る座標
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	mHasParentObject = true;
	mOffsetPos = _offset;
	mLerpObject = _parentPos;
}
