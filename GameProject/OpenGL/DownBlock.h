/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

class DownBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 落下ブロックの座標
	@param	_size 落下ブロックのサイズ
	@param	_objectTag 落下ブロックのタグ
	@param	_sceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	DownBlock(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~DownBlock() {};

	/*
	@fn		落下ブロックのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 落下ブロックの落ちる速度
	const float DOWN_SPEED = 25.0f;

	// プレイヤーのポインタ
	Player* mPlayer;
};