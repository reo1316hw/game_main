#include "PlayerObjectStateAttack01.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "InputSystem.h"
//#include "AudioManager.h"
//#include "SwordEffectActor.h"

PlayerObjectStateAttack01::PlayerObjectStateAttack01()
	: mIsNextCombo(false)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateAttack01\n");
}

PlayerObjectStateAttack01::~PlayerObjectStateAttack01()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateAttack01\n");
}

PlayerState PlayerObjectStateAttack01::Update(PlayerObject* _owner, float _deltaTime)
{
	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		//_owner->RemoveAttackHitBox();
		if (mIsNextCombo)
		{
			return PlayerState::PLAYER_STATE_ATTACK2;
		}

		return PlayerState::PLAYER_STATE_SWORD_IDLE;
	}

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _deltaTime;
	const float PLAYER_ATTACK_SPEED = 50.0f;

	// �o�ߊ��������ƂɈړ�����
	Vector3 pos,forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = 0.0f - PLAYER_ATTACK_SPEED * _deltaTime;
	pos += Quintic::EaseIn(mElapseTime, PLAYER_ATTACK_SPEED * _deltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	return PlayerState::PLAYER_STATE_ATTACK1;
}

void PlayerObjectStateAttack01::Inipt(PlayerObject* _owner, const InputState& _keyState)
{

	// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed)
	{
		mIsNextCombo = true;
	}
	
}

void PlayerObjectStateAttack01::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ATTACK1�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_ATTACK1),1.5f);
	mIsNextCombo = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_ATTACK1)->GetDuration();
	mElapseTime = 0.0f;

	/*owner->SetAttackHitBox(1.5f);*/

	//// effect����
	//SwordEffectActor* effect = new SwordEffectActor(owner);
	//Vector3 localPos, localAngle;
	//localPos = Vector3(50, 0, 100);
	//localAngle = Vector3(Math::ToRadians(30.0f), 0, Math::ToRadians(-30.0f));
	//effect->SetLocalPos(localPos);
	//effect->SetLocalRotation(localAngle);
	//effect->SetEffectTime(mTotalAnimTime);
}

void PlayerObjectStateAttack01::Exit(PlayerObject* _owner, float _deltaTime)
{
	//_owner->RemoveAttackHitBox();
}