#pragma once
#include <unordered_map>
#include <list>
struct CollisionResultInfo;
struct HitCheckInfo;
class Actor;
class SphereHitChecker;
/// <summary>
/// 衝突処理実行役
/// </summary>
class  ConflictProcessor
{
public:
    /// <summary>
    /// 衝突処理実行役
    /// </summary>
    /// <param name="obj">実行したい衝突処理があるオブジェクト</param>
    ConflictProcessor(Actor* const obj);
    /// <summary>
    /// 特になし
    /// </summary>
    virtual ~ConflictProcessor() {};
    /// <summary>
    /// 当たり判定の処理を呼び出す
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void OnConflict(CollisionResultInfo resultInfo);

    /// <summary>
    /// 当たり判定で衝突しているか調べるのに必要な情報を渡す
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;
protected:
    /// <summary>
    /// 当たり判定の持ち主
    /// </summary>
    Actor* object = nullptr;
};