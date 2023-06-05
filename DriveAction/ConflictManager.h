#pragma once
#include <list>
#include <unordered_map>
#include "ConflictProccesor.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
/// <summary>
/// 当たり判定を纏めてするための奴
/// </summary>
class ConflictManager
{
public:
    ConflictManager();
    ~ConflictManager();
    /// <summary>
    /// ぶつかってるか調べたいやつを追加する
    /// </summary>
    /// <param name="obj"></param>
    static void AddConflictObjInfo(ConflictProccesor* conflictProccesor);
    /// <summary>
    /// 当たり判定を消去する
    /// </summary>
    /// <param name="conflictProccesor"></param>
    static void EraceConflictObjInfo(ConflictProccesor* conflictProccesor);
    /// <summary>
    /// デバッグ用球を出す
    /// </summary>
    void DrawCollisionSphere();
    /// <summary>
    /// 引数のオブジェクトとぶつかっているか調べる
    /// </summary>
    /// <param name="examineObjInfo"></param>
    /// <returns></returns>
    std::list<ConflictExamineResultInfo> GetConflictObjInfo(ConflictProccesor* conflictProccesor);
    void Update();
private:

    static std::list<ConflictProccesor*> conflictObjList;
};