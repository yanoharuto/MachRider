#include "ShadowMap.h"
#include "ObjectObserver.h"


ShadowMap::ShadowMap(std::weak_ptr <ObjectObserver> player)
{
    //かげの向き
    SetShadowMapLightDirection(shadowMap, VGet(0.1f, -1, 0));
    SetShadowMapDrawArea(shadowMap, DrawAreaMinPos, DrawAreaMaxPos);
    playerObserber = player;
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
    VECTOR targetPos = playerObserber.lock()->GetSubjectPos();
    VECTOR minPos = VAdd(targetPos, DrawAreaMinPos);
    VECTOR maxPos = VAdd(targetPos, DrawAreaMaxPos);
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
