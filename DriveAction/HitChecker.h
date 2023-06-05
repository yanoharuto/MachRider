#pragma once
struct HitCheckExamineObjectInfo;
class Object;
/// <summary>
/// 球同士の当たり判定をやります
/// </summary>
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objA">調べたいオブジェクトA<</param>
    /// <param name="objB">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    static bool HitCheck(Object* const objA, Object* const objB);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objA">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    static bool HitCheck(Object* const objA, const HitCheckExamineObjectInfo objBInfo);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    static bool HitCheck(const HitCheckExamineObjectInfo objAInfo, const HitCheckExamineObjectInfo objBInfo);
private:
    /// <summary>
    /// 当たったかどうか調べるときの共通処理
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    static bool HitCheckProcess(HitCheckExamineObjectInfo objAInfo, HitCheckExamineObjectInfo objBInfo);
};

