/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

class VerticalMoveGround : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 縦移動床の座標
	@param	_size 縦移動床のサイズ
	@param	_objectTag 縦移動床のタグ
	@param	_sceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~VerticalMoveGround() {};

	/*
	@fn		縦移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//縦移動床の前に移動する速度
	const float FORWARD_SPEED = 10.0f;

	// プレイヤーのポインタ
	Player* mPlayer;

	/*
	@fn		縦移動床がヒットした時の処理
	@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _hitObject)override;
};
