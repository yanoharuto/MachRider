#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// 当たり判定で使う引数にして渡したい情報
/// </summary>
struct HitCheckInfo
{
    VECTOR pos = {};//ポジション
    VECTOR velocity = {};//移動量
    float radius = 0;//半径
    Object::ObjectTag tag;
    void SetExamineInfo(Object* obj)
    {
        tag = obj->GetTag();
        pos = obj->GetPos();
        radius = obj->GetRadius();
    }
};