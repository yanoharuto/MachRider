#include "CollectCompass.h"
#include "UIManager.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
/// <summary>
/// �G�t�F�N�g�̓ǂ݂���
/// </summary>
/// <param name="player">�v���C���[�̈ʒu�Ȃǂ�Ⴄ���Ƃ��o����I�u�U�[�o�[</param>
CollectCompass::CollectCompass(std::weak_ptr<PlayerObserver> player)
{
    playerObserver = player;
    EffectManager::LoadEffect(compass);
}
/// <summary>
/// �G�t�F�N�g�I��
/// </summary>
CollectCompass::~CollectCompass()
{
    StopEffekseer3DEffect(compassEffect);
}
/// <summary>
/// �G�t�F�N�g�̈ʒu�ƌ�����ݒ�
/// </summary>
void CollectCompass::Update()
{
    //�����W�A�C�e���������Ă��邩
    if (CollectController::IsActiveCollect())
    {
        //�G�t�F�N�g���~�܂��Ă��������x�Đ�
        if (IsEffekseer3DEffectPlaying(compassEffect) == -1)
        {
            compassEffect = EffectManager::GetPlayEffect3D(EffectInit::compass);
        }
        //�G�t�F�N�g�̓v���C���[�̑����ɕ\��
        VECTOR pos = playerObserver.lock()->GetSubjectPos();
        pos.y += addYPos;
        SetPosPlayingEffekseer3DEffect(compassEffect, pos.x, pos.y, pos.z);
        //���������W�A�C�e���̕����ɐݒ�
        float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), CollectController::GetCollectItemBetween(pos));
        if (VCross(VGet(1, 0, 0), CollectController::GetCollectItemBetween(pos)).y < 0)
        {
            SetRotationPlayingEffekseer3DEffect(compassEffect, 0, -degree * RAGE, 0);
        }
        else
        {
            SetRotationPlayingEffekseer3DEffect(compassEffect, 0, degree * RAGE, 0);
        }
    }
    else
    {
        //�����ĂȂ��Ԃ͒�~
        StopEffekseer3DEffect(compassEffect);
    }
}