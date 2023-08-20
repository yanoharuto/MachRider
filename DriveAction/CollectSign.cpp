#include "CollectSign.h"
#include "UIManager.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"

/// <summary>
/// ���W�A�C�e���̕������L���G�t�F�N�g���o��
/// </summary>
CollectSign::CollectSign(std::weak_ptr<PlayerObserver> player)
{
    playerObserver = player;
    EffectManager::LoadEffect(compass);
}
/// <summary>
/// �G�t�F�N�g�I��
/// </summary>
CollectSign::~CollectSign()
{
    StopEffekseer3DEffect(signEffect);
}
/// <summary>
/// �G�t�F�N�g�̈ʒu�ƌ�����ݒ�
/// </summary>
void CollectSign::Update()
{
    //�����W�A�C�e���������Ă��邩
    if (CollectController::IsActiveCollect())
    {
        //�G�t�F�N�g���~�܂��Ă��������x�Đ�
        if (IsEffekseer3DEffectPlaying(signEffect) == -1)
        {
            signEffect = EffectManager::GetPlayEffect3D(EffectInit::compass);
        }
        //�G�t�F�N�g�̓v���C���[�̑����ɕ\��
        VECTOR pos = playerObserver.lock()->GetSubjectPos();
        pos.y += addYPos;
        SetPosPlayingEffekseer3DEffect(signEffect, pos.x, pos.y, pos.z);
        //���������W�A�C�e���̕����ɐݒ�
        float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), CollectController::GetBetween(pos));
        if (VCross(VGet(1, 0, 0), CollectController::GetBetween(pos)).y < 0)
        {
            SetRotationPlayingEffekseer3DEffect(signEffect, 0, -degree * RAGE, 0);
        }
        else
        {
            SetRotationPlayingEffekseer3DEffect(signEffect, 0, degree * RAGE, 0);
        }
    }
    else
    {
        //�����ĂȂ��Ԃ͒�~
        StopEffekseer3DEffect(signEffect);
    }
}