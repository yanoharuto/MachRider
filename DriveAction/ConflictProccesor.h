#pragma once
#include <list>
#include <unordered_map>
#include "Timer.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
/// <summary>
/// 当たり判定を行う
/// </summary>
class  ConflictProccesor abstract
{
public:
    /// <summary>
    /// 衝突後の処理をしなくていいならデフォルトコンストラクタ
    /// </summary>
    ConflictProccesor() {};
    /// <summary>
    /// 衝突後の処理をするならこっち
    /// </summary>
    /// <param name="obj"></param>
    ConflictProccesor(Actor* obj);

    virtual ~ConflictProccesor();
    /// <summary>
    /// 当たり判定を行う
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    virtual ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) = 0;
    /// <summary>
    /// 当たり判定で必要な情報を渡す
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitExamineCheckInfo();
    /// <summary>
    /// 当たり判定の処理を呼び出す
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo);
    /// <summary>
    /// 当たり判定で特定のものにクールタイムが発生する場合タイマーをセット出来る
    /// </summary>
    /// <param name="tag">特定の者のタグ</param>
    /// <param name="timer">クールタイム計測用のタイマー</param>
    void SetCoolTimer(Object::ObjectTag tag,float setCoolTime);
    /// <summary>
    /// 引数のタグのオブジェクトに何回ぶつかったか返す
    /// </summary>
    /// <param name="objTag"></param>
    /// <returns></returns>
    int GetTagHitCount(Object::ObjectTag objTag);
protected:
    /// <summary>
    /// 引数のオブジェクトの当たった回数を増やす
    /// </summary>
    /// <param name="objTag"></param>
    void IncrementHitCount(Object::ObjectTag objTag);
    //当たり判定の持ち主
    Actor* object = nullptr;
    //クールタイマー
    std::unordered_map<Object::ObjectTag, Timer*> coolTimer;
    //ぶつかったタグの当たった回数を記録
    std::unordered_map<Object::ObjectTag, int> hitCountMap;
};