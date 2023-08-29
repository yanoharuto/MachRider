#include "SphereHitChecker.h"
#include "Actor.h"
#include "HitCheckExamineObjectInfo.h"
#include "DxLib.h"
/// <summary>
/// 球形当たり判定
/// </summary>
/// <param name="obj">当たり判定の持ち主をください</param>
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
    //１引数の当たり判定情報
    HitCheckInfo aInfo;
    aInfo.SetExamineInfo(objA);
    //2引数の当たり判定情報
    HitCheckInfo bInfo;
    bInfo.SetExamineInfo(objB);
    //当たり判定調査
    return HitCheckProcess(aInfo, bInfo);
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objA">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheck(Object* const objA, const HitCheckInfo objBInfo)
{
    HitCheckInfo aInfo;
    aInfo.SetExamineInfo(objA);
    //当たり判定調査
    return HitCheckProcess(aInfo, objBInfo);
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objAInfo">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheck(const HitCheckInfo objAInfo, const HitCheckInfo objBInfo)
{
    return HitCheckProcess(objAInfo, objBInfo);
}
/// <summary>
/// 当たり判定で衝突しているか調べるのに必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckInfo SphereHitChecker::GetHitExamineCheckInfo() const
{
    HitCheckInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// 今もう動いていない状態か
/// </summary>
/// <returns>動いていないならTrue</returns>
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
bool SphereHitChecker::HitCheckProcess(HitCheckInfo objAInfo, HitCheckInfo objBInfo)
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