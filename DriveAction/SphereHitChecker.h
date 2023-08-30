#pragma once
#include "Object.h"
struct HitCheckInfo;
struct CollisionResultInfo;
class Actor;
/// <summary>
/// 球同士の当たり判定をやります
/// </summary>
class SphereHitChecker
{
public:
    /// <summary>
    /// 球同士の当たり判定を行う
    /// </summary>
    /// <param name="obj">当たり判定の持ち主</param>
    SphereHitChecker(Actor* const obj);
    ~SphereHitChecker();
    /// <summary>
/// 当たっているか調べ吹っ飛ぶ方向とかを返す
/// </summary>
/// <param name="hitCheckInfo"></param>
/// <returns></returns>
    virtual CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo);

    /// <summary>
    /// 当たり判定で衝突しているか調べるのに必要な情報を渡す
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;

    /// <summary>
    /// trueなら当たり判定無し
    /// </summary>
    /// <returns></returns>
    bool IsDead();
protected:
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objA">調べたいオブジェクトA<</param>
    /// <param name="objB">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(Object* const objA, Object* const objB);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objA">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(Object* const objA, const HitCheckInfo objBInfo);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(const HitCheckInfo objAInfo, const HitCheckInfo objBInfo);

protected:
    /// <summary>
    /// 当たったかどうか調べるときの共通処理
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheckProcess(HitCheckInfo objAInfo, HitCheckInfo objBInfo);

    //当たり判定の持ち主
    Actor* object = nullptr;
};