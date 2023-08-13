﻿#include "SphereHitChecker.h"
#include "Actor.h"
#include "HitCheckExamineObjectInfo.h"
#include "DxLib.h"
/// <summary>
/// 当たり判定の持ち主をください
/// </summary>
/// <param name="obj"></param>
SphereHitChecker::SphereHitChecker(Actor* const obj)
{
    object = obj;
}

SphereHitChecker::~SphereHitChecker()
{
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objA">調べたいオブジェクトA</param>
/// <param name="objB">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheck(Object* const objA, Object* const objB)
{
    HitCheckExamineObjectInfo aInfo;
    aInfo.SetExamineInfo(objA);
    HitCheckExamineObjectInfo bInfo;
    bInfo.SetExamineInfo(objB);
    return HitCheckProcess(aInfo, bInfo);
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objA">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheck(Object* const objA, const HitCheckExamineObjectInfo objBInfo)
{
    HitCheckExamineObjectInfo aInfo;
    aInfo.SetExamineInfo(objA);
    return HitCheckProcess(aInfo, objBInfo);
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objAInfo">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheck(const HitCheckExamineObjectInfo objAInfo, const HitCheckExamineObjectInfo objBInfo)
{
    return HitCheckProcess(objAInfo, objBInfo);
}
/// <summary>
/// 当たり判定で衝突しているか調べるのに必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo SphereHitChecker::GetHitExamineCheckInfo() const
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// 今もう動いていない状態か
/// </summary>
/// <returns></returns>
bool SphereHitChecker::IsDead()
{
    return (object->GetObjectState() == Object::dead || object->GetObjectState() == Object::activeEnd);
}
/// <summary>
/// 当たったかどうか調べるときの共通処理
/// </summary>
/// <param name="objAInfo">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheckProcess(HitCheckExamineObjectInfo objAInfo, HitCheckExamineObjectInfo objBInfo)
{
    //引数同士の距離
    VECTOR distance = VSub(objAInfo.pos, objBInfo.pos);
    //引数同士の半径の合計
    float range = objAInfo.radius + objBInfo.radius;
    //半径の合計より小さかったら当たった
    if (range > VSize(distance))
    {
        return true;
    }
    return false;
}