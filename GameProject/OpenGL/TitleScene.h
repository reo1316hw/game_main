/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class TitleScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	TitleScene(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~TitleScene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:
};

