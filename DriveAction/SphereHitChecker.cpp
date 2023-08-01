#include "SphereHitChecker.h"
#include "Actor.h"
#include "HitCheckExamineObjectInfo.h"
#include "DxLib.h"
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
HitCheckExamineObjectInfo SphereHitChecker::GetHitExamineCheckInfo() const
{

    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
bool SphereHitChecker::IsDead()
{
    return object->GetObjectState() == (Object::dead || Object::activeEnd);
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