#pragma once
#include "DxLib.h"
#include "Object.h"

enum class HitSituation
{
    NotHit,
    Enter,
    Stay,
    Exist
};
/// <summary>
/// 当たり判定の結果 渡す情報
/// </summary>
struct ConflictExamineResultInfo
{
    HitSituation hit = HitSituation::NotHit;//当たり判定で当たったか
    Object::Object::ObjectTag tag = Object::ObjectTag::obstacle;//オブジェクトのタグ
    VECTOR bounceVec = {};
    VECTOR pos = {};
    float radius = 0;//半径
    float bouncePower = 0;//吹っ飛び力
    /// <summary>
    /// tagや半径　吹っ飛び力を設定
    /// </summary>
    /// <param name="hit">当たり判定で当たったか</param>
    /// <param name="obj">作りたい情報のオブジェクト</param>
    void SetObjInfo(Object* const obj)
    {
        tag = obj->GetTag();
        radius = obj->GetRadius();
        bouncePower = obj->GetBouncePower();
    }
};
