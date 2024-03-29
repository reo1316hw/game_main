/*
@file  FPS.h
@brief フレームにかかった時間を計測し上限を設けるクラス
*/

/*
@brief プリプロセッサ
*/
#pragma once

class FPS
{
public:

	/*
	@fn	コンストラクタ
	*/
	FPS();

	/*
	@fn	デストラクタ
	*/
	~FPS();

	/*
	@fn	フレーム毎の処理
	*/
	void Update();

private:

	/*
	@fn	FPSが設定値より大きくならないための制御
	*/
	void Wait();

	//フレームレートの最高値
	const Uint32 MSetFps;				
	//１フレームにかける時間
	const Uint32 MOneFrameTickCount;		
	//フレームのカウンター
	Uint32 mFpsCount;					
	//FPSの計算を始めた時の時間
	Uint32 mFrameStartTickTime;			
	//計算したフレームレート
	Uint32 mFps;							
	//前のフレームのかかった時間
	int mBeforetickCount;				
	//現在のフレームのかかった時間
	float mDeltaTime;					

public://ゲッターセッター

	/*
	@return 現在のフレームにかかった時間(float型)
	*/
	float GetDeltaTime() { return mDeltaTime; }
};

