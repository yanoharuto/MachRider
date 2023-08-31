#include "EditorEffect.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "EditObjectData.h"
#include "StageDataEditor.h"
/// <summary>
/// �G�t�F�N�g�ǂݍ���
/// </summary>
EditorEffect::EditorEffect()
{
    //�I���G�t�F�N�g
    if (posEffect == -1)
    {
        EffectManager::LoadEffect(collectAura);
        EffectManager::LoadEffect(compass);
        posEffect = EffectManager::GetPlayEffect3D(collectAura);
        dirEffect = EffectManager::GetPlayEffect3D(compass);
        SetScalePlayingEffekseer3DEffect(dirEffect, dirEffectSize, dirEffectSize, dirEffectSize);
    }
}
/// <summary>
/// �G�t�F�N�g�I��
/// </summary>
EditorEffect::~EditorEffect()
{
    if (posEffect != -1)
    {
        StopEffekseer3DEffect(posEffect);
        StopEffekseer3DEffect(dirEffect);
        posEffect = -1;
    }
}
/// <summary>
/// �G�t�F�N�g�̌����ƈʒu�̕ύX
/// </summary>
/// <param name="editor">���ҏW���Ă���Editor</param>
void EditorEffect::Update(StageDataEditor* const editor)
{
    //�ҏW���̌���
    VECTOR dir = editor->GetEditObjDir();
    //�I���������̕�����������G�t�F�N�g����]����
    float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), dir);
    if (VCross(VGet(1, 0, 0), dir).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, -degree * RAGE, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, degree * RAGE, 0);
    }
    //�ҏW���̈ʒu
    VECTOR pos = editor->GetEditObjPos();
    //�ҏW���̈ʒu��������₷���Ȃ�G�t�F�N�g�̈ʒu�ύX
    SetPosPlayingEffekseer3DEffect(posEffect, pos.x, 0, pos.z);
    SetPosPlayingEffekseer3DEffect(dirEffect, pos.x, 0, pos.z);
}