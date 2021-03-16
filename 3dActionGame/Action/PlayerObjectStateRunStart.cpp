#include "PlayerObjectStateRunStart.h"
#include "SkeletalMeshComponent.h"
#include "game.h"
#include "Animation.h"
#include "InputSystem.h"
//#include "AudioManager.h"
//#include "SwordEffectActor.h"

PlayerObjectStateRunStart::PlayerObjectStateRunStart()
	: mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mIsIdle(false)
	, mIsAttack(false)
	, charaSpeed(0.0f)
	, dirVec(Vector3::Zero)
	, forwardVec(Vector3::Zero)
	, rightVec(Vector3::Zero)
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateRunStart\n");
}

PlayerObjectStateRunStart::~PlayerObjectStateRunStart()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateRunStart\n");
}

PlayerState PlayerObjectStateRunStart::Update(PlayerObject* _owner, float _deltaTime)
{
	mElapseTime += _deltaTime;

	// アニメーションが終了したらcStopTime硬直後、RUN状態へ
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		if (mElapseTime > mTotalAnimTime)
		{
			return PlayerState::PLAYER_STATE_SPRINT_LOOP;
		}
		else
		{
			return PlayerState::PLAYER_STATE_RUN_START;
		}
	}


	//// ジャンプ開始・ジャンプループ/終了アニメ
	//const Animation* runStart = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_START);
	//const Animation* runLoop = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_LOOP);

	//// 現在再生中のアニメを取得
	//SkeletalMeshComponent* skeltalMesh = _owner->GetSkeletalMeshComp();
	//const Animation* nowAnim = skeltalMesh->GetNowPlayingAnimation();

	MoveCalc(_owner, _deltaTime);

	//// 開始アニメ終了ならジャンプループアニメに移行
	//if (nowAnim == runStart && skeltalMesh->IsPlaying())
	//{
	//	//skeltalMesh->PlayAnimation(runLoop);
	//	return PlayerState::PLAYER_STATE_RUN_LOOP;
	//}

	return PlayerState::PLAYER_STATE_RUN_START;
}

void PlayerObjectStateRunStart::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
	//値が更新され続けるのを防ぐために初期化
	dirVec = Vector3::Zero;

	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		dirVec += forwardVec;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		dirVec -= forwardVec;
	}

	//コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		dirVec -= rightVec;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		dirVec += rightVec;
	}
}

void PlayerObjectStateRunStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// RUN_STARTのアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_RUN_START),1.2f);

	// アニメーション再生時間取得(アニメーションの総時間矯正)
	mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_START)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;
	charaSpeed = 0.0f;
}

void PlayerObjectStateRunStart::Exit(PlayerObject* _owner, float _deltaTime)
{

}

void PlayerObjectStateRunStart::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	// 移動速度
	const float PLAYER_SPEED = 100.0f;

	// カメラからみた前進方向を取得
	Vector3 targetPos = _owner->GetTargetPos();
	Vector3 viewPos = _owner->GetViewPos();
	forwardVec = targetPos - viewPos;
	forwardVec.z = 0.0f; // 高さ方向を無視

	// カメラ前方ベクトルと右方向ベクトル算出
	forwardVec = Vector3::Normalize(forwardVec);
	rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);
	//jumpVec = Vector3::Cross(Vector3::UnitY, forwardVec);

	//// 右方向ベクトルからカメラ回転角を算出
	//float forwardAngle = 0.0f;
	//float angleSign;
	//Vector3 tmpVec;
	//forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, rightVec));

	//// 右回転か左回転か？
	//tmpVec = Vector3::Cross(Vector3::UnitX, rightVec);
	//angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	//forwardAngle *= angleSign

	// 入力キーの総和
	if (dirVec.LengthSq() > 0.5f)
	{
		// 方向キー入力
		charaForwardVec = dirVec;

		// 進行方向に向けて回転
		charaForwardVec.Normalize();
		_owner->RotateToNewForward(charaForwardVec);

		// 現在のスピードを保存
		charaSpeed += PLAYER_SPEED * _deltaTime;
	}

	if (charaSpeed >= 12.0f)
	{
		charaSpeed = 12.0f;
	}

	// 移動処理
	Vector3 position = _owner->GetPosition();
	position += charaSpeed * charaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(position);
}
