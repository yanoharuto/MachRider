#include "EditorEffect.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "EditObjectData.h"
#include "StageDataEditor.h"
/// <summary>
/// エフェクト読み込み
/// </summary>
EditorEffect::EditorEffect()
{
    using enum EffectKind;
    //選択エフェクト
    if (posEffect == -1)
    {
        EffectManager::LoadEffect(collectAura);
        EffectManager::LoadEffect(comPath);
        posEffect = EffectManager::GetPlayEffect3D(collectAura);
        dirEffect = EffectManager::GetPlayEffect3D(comPath);
        SetScalePlayingEffekseer3DEffect(dirEffect, dirEffectSize, dirEffectSize, dirEffectSize);
    }
}
/// <summary>
/// エフェクト終了
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
/// エフェクトの向きと位置の変更
/// </summary>
/// <param name="editObjPlaceData">今編集しているEditor</param>
void EditorEffect::Update(PlacementData const editObjPlaceData)
{
    //編集物の向き
    VECTOR dir = VGet(editObjPlaceData.dirX,0,editObjPlaceData.dirZ);
    //選択した物の方向が分かるエフェクトを回転する
    float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), dir);
    if (VCross(VGet(1, 0, 0), dir).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, -degree * RAGE, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, degree * RAGE, 0);
    }
    //編集物の位置
    VECTOR pos = VGet(editObjPlaceData.posX, 0, editObjPlaceData.posZ);
    //編集物の位置が分かりやすくなるエフェクトの位置変更
    SetPosPlayingEffekseer3DEffect(posEffect, pos.x, 0, pos.z);
    SetPosPlayingEffekseer3DEffect(dirEffect, pos.x, 0, pos.z);
    Effekseer_Sync3DSetting();
    //エフェクト更新
    UpdateEffekseer3D();
}