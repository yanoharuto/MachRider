#pragma once
#include "DxLib.h"
#include "Object.h"
struct ArgumentConflictResultInfo
{
    Object::ObjectTag tag = Object::ObjectTag::obstacle;//オブジェクトのタグ
    VECTOR pos = {};
    VECTOR bounceVec = {};
    float radius = 0;//半径
    /// <summary>
    /// 引数のオブジェクトから情報を作成
    /// </summary>
    /// <param name="hit">当たり判定で当たったか</param>
    /// <param name="obj">作りたい情報のオブジェクト</param>
    void SetObjInfo(Object* const obj)
    {
        tag = obj->GetTag();
        radius = obj->GetRadius();
    }
};