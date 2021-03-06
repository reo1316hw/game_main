/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "GameObject.h"
#include "ParticleEffectBase.h"

class SandEffectManager;
class ClearEffectManager;
class DeathEffectManager;
class CheckpointEffectManager;
class SphereCollider;
class LateralMoveGround;

/*
@enum	プレイヤーのリスポーンステート
@brief	どのリスポーン地点で復活するか
*/
enum class RespawnState
{
	respawnNone = 0,
	respawnComplete01 = 1,
	respawnComplete02 = 2,
	respawnComplete03 = 3
};

class Player:public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos プレイヤーの座標
	@param	_size プレイヤーのサイズ
	@param	_objectTag プレイヤーのタグ
	@param	_sceneTag シーンのタグ
	*/
	Player(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Player() {};

	/*
	@fn		プレイヤーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		入力を引数で受け取る更新関数
	@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	@param	_keyState 各入力機器の入力状態
	@brief	キーボード、マウス、コントローラー
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:

	//プレイヤーの球当たり判定を生成
	SphereCollider*		mSelfSphereCollider;
	//プレイヤーの球当たり判定の大きさ
	Sphere				mPlayerSphere;
	//プレイヤーの砂ぼこりエフェクト
	SandEffectManager*  mSandEffectManager;
	//プレイヤーのクリアエフェクト
	ClearEffectManager* mClearEffectManager;
	//プレイヤーのデスエフェクト
	DeathEffectManager* mDeathEffectManager;
	//プレイヤーのチェックポイントエフェクト
	CheckpointEffectManager* mCheckpointEffectManager;
	//横移動床のポインタ
	LateralMoveGround*	mLateral;
	//リスポーンステートの値を格納する変数
	RespawnState		mRespawnState;

	//横移動床にあたった時の速度
	Vector3				mLateralMoveVelocity;

	static Vector3 mSendPos;

	static bool mSendClearFlag;

	static bool mSendDeathFlag;

	static bool mSendRespawnFlag;

	static bool mSendCheckpointFlag;

	static int  mSendLife;

	//死んだか
	bool		mDeathFlag;
	//ダメージを受けたか
	bool		mDamageFlag;
	//リスポーン後の待機フラグ
	bool		mStopFlag;
	//クリアしたか
	bool		mClearFlag;
	//ジャンプするか
	bool		mJumpFlag;
	//スケールを変えるか
	bool		mScaleFlag;
	//ボタンが入力されたか
	bool		mButtonFlag;
	//接地したか
	bool		mGroundFlag;
	//当たり判定を行うか
	bool		mCollisionFlag;
	//チェックポイント通過したか
	bool		mCheckpointFlag;

	//プレイヤーが点滅するためのカウント
	int			mVisibleFrameCount;
	//現在のシーンはどれか
	int			mScene;
	//体力	
	int			mLife;
	//チェックポイントエフェクトを生存時間
	int			mCheckpointEffectCount;

	//角度
	float		mAngle;

	//重力
	const float GRAVITY_ACCEL = 2.0f;
	//ジャンプ力
	const float JUMP_SPEED = 40.0f;
	//チュートリアル時のジャンプ力
	const float TUTORIAL_JUMP_SPEED = 48.0f;
	//等速速度
	const float PLAYER_CONSTANT_SPEED = 20.0f;
	//加速度
	const float PLAYER_SPEED_UP = 10.0f;
	//減速度
	const float PLAYER_SPEED_DOWN = 4.0f;
	//最大速度
	const float PLAYER_MAX_SPEED = 25.0f;
	//チュートリアル時の移動速度
	const float TUTORIAL_MOVE_SPEED = 13.0f;
	//体力
	const int   PLAYER_LIFE = 3;
	
	/*
	@fn		プレイヤーがヒットした時の処理
	@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _hitObject)override;

public://ゲッターセッター

	static Vector3 GetPos() { return mSendPos; };
	static bool GetClearFlag() { return mSendClearFlag; };
	static bool GetDeathFlag() { return mSendDeathFlag; };
	static bool GetRespawnFlag() { return mSendRespawnFlag; };
	static bool GetCheckpointFlag() { return mSendCheckpointFlag; };
	static int GetLife() { return mSendLife; };

};

