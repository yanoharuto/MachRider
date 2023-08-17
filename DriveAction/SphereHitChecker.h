#pragma once
#include "Object.h"
struct HitCheckExamineObjectInfo;
struct ConflictExamineResultInfo;
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
    bool HitCheck(Object* const objA, const HitCheckExamineObjectInfo objBInfo);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(const HitCheckExamineObjectInfo objAInfo, const HitCheckExamineObjectInfo objBInfo);

    /// <summary>
    /// 当たり判定を行う
    /// </summary>
    /// <param name="hitCheckInfo">その結果当たったか位置がずれるか</param>
    /// <returns></returns>
    virtual ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) = 0;

    /// <summary>
    /// 当たり判定で衝突しているか調べるのに必要な情報を渡す
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitExamineCheckInfo()const;

    /// <summary>
    /// trueなら当たり判定無し
    /// </summary>
    /// <returns></returns>
    bool IsDead();
protected:
    /// <summary>
    /// 当たったかどうか調べるときの共通処理
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheckProcess(HitCheckExamineObjectInfo objAInfo, HitCheckExamineObjectInfo objBInfo);

    //当たり判定の持ち主
    Actor* object = nullptr;
};

