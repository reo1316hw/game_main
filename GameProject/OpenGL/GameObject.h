/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class Game;
class Vector3;
class Matrix4;
class Component;
class ColliderComponent;
class InvisibleMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;
struct InputState;

/*
@enum	GameObjectステート
@brief	ゲームオブジェクトの状態
*/
enum State
{
	//アクティブ
	Active,
	//更新が停止している
	Paused,
	//オブジェクトの更新が終了(外部からのみActiveに変更可能)
	Dead,
};

/*
@enum	GameObjectタグ
@brief	衝突相手を判別するために使用
*/
enum Tag
{
	Other = 0,
	Camera = 1,
	player = 2,
	ground = 3,
	glass = 4,
	block = 5,
	verticalMoveGround = 6,
	jump = 7,
	lateralMoveGround = 8,
	upBlock = 9,
	upBlock_02 = 10,
	verticalBlock = 11,
	aerialBlock = 12,
	rightBlock = 13,
	leftBlock = 14,
	rightGround = 15,
	rightOneMoveBlock = 16,
	leftGround = 17,
	leftOneMoveBlock = 18,
	downBlock = 19,
	goalBlock = 20,
	respawn01 = 21,
	respawn02 = 22,
	respawn03 = 23,
	checkpoint = 24,
	Swith = 25
};

/*
@enum	ゲームオブジェクトの更新を停止するイベント名
*/
enum PauzingEvent
{
	//ボスの特殊演出
	SummonMageEvent,
	//ポーズ画面中
	PausingEvent,
	//プレイヤーが撃破されてしまった際の演出
	DeadPlayerEvent,
	//ゲームオーバー時の演出 DeadPlayerEventと関連
	GameOverEvent,
	//ゲームオブジェクトの更新が行われている。
	NoneEvent
};

class GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_sceneTag シーンのタグ
	@param	_objectTag ゲームオブジェクトのタグ
	@param	_reUseGameObject
	*/
	GameObject(SceneBase::Scene _sceneTag, const Tag& _objectTag , bool _reUseGameObject = false);

	/*
	@fn	デストラクタ
	*/
	virtual ~GameObject();

	/*
	@fn		フレーム毎の処理
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime);

	/*
	@fn		アタッチされてるコンポーネントのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@fn		ゲームオブジェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn		ゲームオブジェクトが静止中に更新されるアップデート関数
	@brief	pauzingUpdateがtrueのときだけ呼ばれる更新関数
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn		入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
	@param	_keyState 各入力機器の入力状態
	@brief	キーボード、マウス、コントローラー
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn		入力を引数で受け取る更新関数
	@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	@param	_keyState 各入力機器の入力状態
	@brief	キーボード、マウス、コントローラー
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@fn		コンポーネントを追加する
	@param	_component 追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* _component);

	/*
	@fn		コンポーネントを削除する
	@param	_component 削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn			現在の仕様上行うことができない処理を外部から強引に行うための関数
	@exsample	ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
	*/
	void ExceptionUpdate();

	/*
	@fn	Transformのワールド変換
	*/
	void ComputeWorldTransform();

	/*
	@fn		矩形と矩形の押し戻し
	@param	_myAABB	基準にするオブジェクトの矩形当たり判定
	@param	_pairAABB ヒットするオブジェクトの矩形当たり判定
	@param	_pairTag ヒットするオブジェクトのタグ
	*/
	virtual void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag);

	/*
	@fn		前方ベクトルの向きに回転する
	@param	_forward 向かせたい前方方向ベクトル
	*/
	void RotateToNewForward(const Vector3& _forward);

	/*
	@fn 静的なmainCameraを生成する
	*/
	static void CreateMainCamera();

protected:
	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }

	/*
	@fn		ゲームオブジェクトがヒットした時の処理
	@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	virtual void OnCollision(const GameObject& _hitObject) {}

	//メインカメラ　生成はGameObjectManager生成時に行われる
	static class MainCameraObject* mMainCamera;
	//ゲームオブジェクトの更新を止めるイベント状態
	static PauzingEvent mPauzingEvent;
	//衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerEnter(ColliderComponent* _colliderPair) {};
	//衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerStay(ColliderComponent* _colliderPair) {};

	//オブジェクトのAABB
	AABB mAabb;
	//ゲームオブジェクトの状態
	State mState;
	//ゲームオブジェクトのタグ
	Tag mTag;
	//ゲームオブジェクトのID、カウント用
	static int mGameObjectId;
	//このゲームオブジェクトのID
	int mMyObjectId;

	//ゲームオブジェクトのメッシュ
	MeshComponent* mMeshComponent;
	//ゲームオブジェクトの矩形当たり判定
	BoxCollider* mBoxcollider;
	//当たり判定をmeshにするためのインスタンス
	Mesh* mMesh;

	//Transform
	Vector3 mPosition;
	Vector3 mVelocity;
	Vector3 mScale;
	//移動先
	Vector3 mEndPos;
	//初期座標
	Vector3	mInitPos;
	//オブジェクトのクォータニオン
	Quaternion  mRotation;
	//オブジェクトのワールド行列
	Matrix4	mWorldTransform;
	//移動速度
	float mMoveSpeed;
	//重力
	float mGravity;
	//ワールド変換の処理を行う必要性があるか
	bool mRecomputeWorldTransform;
	// 当たったかどうか
	bool mHitFlag;
	// リスポーンしたか
	bool mRespawnFlag;
	// 初期位置に戻すか
	bool mOriginalPosFlag;
	
	//シーンのタグ
	SceneBase::Scene mSceneTag;
	//アタッチされているコンポーネント
	std::vector<class Component*>mComponents;

private:

	//シーンを跨ぐ際に解放されるオブジェクトかどうか、カメラなどが対象になる
	bool mReUseObject;

public://ゲッターセッター

	/*
	@return	オブジェクトのポジション(Vector3型)
	*/
	const Vector3& GetPosition() const { return mPosition; }

	/*
	@return	オブジェクトの速度(Vector3型)
	*/
	const Vector3& GetVelocity() const { return mVelocity; }

	/*
	@return	ワールド変換の処理を行う必要性があるかのフラグ(bool型)
	*/
	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/*
	@return	オブジェクトのスケール(float型)
	*/
	float GetScale() const { return mScale.x; }

	/*
	@return	オブジェクトのクォータニオン(Quaternion型)
	*/
	const Quaternion& GetRotation() const { return mRotation; }

	/*
	@return	オブジェクトの状態(enum型 State)
	*/
	State GetState() const { return mState; }

	/*
	@return	オブジェクトのワールド行列(Matrix4型)
	*/
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/*
	@return	オブジェクトの前方を表すベクトル(Vector3型)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }

	/*
	@return	オブジェクトの右を表すベクトル(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	/*
	@return	オブジェクトの上を表すベクトル(Vector3型)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, mRotation); };

	/*
	@return	オブジェクトのタグ(enum型 Tag)
	*/
	Tag GetTag() const { return mTag; };

	/*
	@return	オブジェクトのid(int型)
	*/
	int GetObjectId() { return mMyObjectId; };

	/*
	@return	解放されるオブジェクト(bool型)
	*/
	bool GetReUseGameObject() { return mReUseObject; };

	/*
	@return	シーンのタグ
	*/
	SceneBase::Scene GetScene() { return mSceneTag; };

	/*
	@return	オブジェクトのAABB
	*/
	AABB GetObjectAABB() { return mAabb; };

	/*
	@param	_scale オブジェクトのスケール
	*/
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	/*
	@param	_qotation オブジェクトのクォータニオン
	*/
	virtual void SetRotation(const Quaternion& _qotation) { mRotation = _qotation;  mRecomputeWorldTransform = true; }

	/*
	@param	_state オブジェクトの状態
	*/
	virtual void SetState(State _state) { mState = _state; }

	/*
	@param	_pos オブジェクトのポジション
	*/
	virtual void SetPosition(const Vector3& _pos) { mPosition = _pos; mRecomputeWorldTransform = true; }

};

