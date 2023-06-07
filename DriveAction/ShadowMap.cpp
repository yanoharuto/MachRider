#include "ShadowMap.h"
#include "ObjectObserver.h"

#include "ObjectSubject.h"
#include "RacerManager.h"

ShadowMap::ShadowMap(RacerManager* racerManager)
{
    //かげの向き
    SetShadowMapLightDirection(shadowMap, VGet(0.1f, -1, 0));
    SetShadowMapDrawArea(shadowMap, DrawAreaMinPos, DrawAreaMaxPos);
    playerObserber = new ObjectObserver(racerManager->GetPlayerSubject(0));;
}

ShadowMap::~ShadowMap()
{
    DeleteShadowMap(shadowMap);
}
/// <summary>
/// 影の描画範囲の変更
/// </summary>
/// <param name="objInfo">引数の座標を中心にする</param>
void ShadowMap::SetShadowMapErea()
{
    VECTOR minPos = VAdd(playerObserber->GetSubjectPos(), DrawAreaMinPos);
    VECTOR maxPos = VAdd(playerObserber->GetSubjectPos(), DrawAreaMaxPos);
    SetShadowMapDrawArea(shadowMap, minPos, maxPos);
}
/// <summary>
/// これから描画する影の準備
/// </summary>
void ShadowMap::SetUP()
{
    ShadowMap_DrawSetup(shadowMap);
}
/// <summary>
/// 影を描画するの終了
/// </summary>
void ShadowMap::DrawEnd()
{
    //シャドウマップへの描画を終了
    ShadowMap_DrawEnd();
    SetUseShadowMap(0, shadowMap);
}
/// <summary>
/// 書き込んだシャドウマップを使う
/// </summary>
void ShadowMap::Use()
{
    SetUseShadowMap(0, -1);
}
