/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class GameClear : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	GameClear(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~GameClear();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

};

