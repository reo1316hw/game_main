/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class Block : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 障害物の座標
	@param	_size 障害物のサイズ
	@param	_objectTag 障害物のタグ
	@param	_sceneTag シーンのタグ
	*/
	Block(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Block() {};

private:
};