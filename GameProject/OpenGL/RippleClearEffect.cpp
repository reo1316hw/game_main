/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 波紋のクリアエフェクトの生成場所
@param	_Vel 波紋のクリアエフェクトの速度
@param  _Color 波紋のクリアエフェクトのカラー値
@param  _Scale スケール値
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
RippleClearEffect::RippleClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Vector3 _Color, const float _Scale, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 30, "Assets/Ripple.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = _Scale;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(_Color);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
	mSpeed = 1.0f;
}

/*
@fn		クリアエフェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void RippleClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (mLifeCount > 0)
	{
		if (mLifeCount <= 15)
		{
			mScale -= 64.0f;
			mVelocity *= mSpeed * -1.0f;
			mPosition += mVelocity;
		}
		else
		{
			mScale += 64.0f;
			mVelocity *= mSpeed;
			mPosition += mVelocity;
		}

		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}

	
}
