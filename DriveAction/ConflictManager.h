#pragma once
#include <list>
#include <unordered_map>
class ConflictProcessor;
class SphereHitChecker;
struct ConflictExamineResultInfo;
/// <summary>
/// 当たり判定を纏めてするための奴
/// </summary>
class ConflictManager
{
public:
    /// <summary>
    /// 当たり判定を纏めてするための奴
    /// </summary>
    ConflictManager();
    /// <summary>
    /// 当たり判定登録Map全消し
    /// </summary>
    ~ConflictManager();
    /// <summary>
    /// 当たり判定追加
    /// </summary>
    /// <param name="hitChecker"></param>
    static void AddHitChecker(SphereHitChecker* const hitChecker);
    /// <summary>
    /// 当たり判定消去
    /// </summary>
    /// <param name="hitChecker"></param>
    static void EraceHitChecker(SphereHitChecker* const hitChecker);
    /// <summary>
    /// 衝突処理を呼ぶConflictProcessorを追加
    /// </summary>
    /// <param name="conflictProccesor">衝突処理を呼ぶConflictProcessorを追加</param>
    /// <param name="hitChecker">conflictProcessorの当たり判定</param>
    static void AddConflictProcessor(ConflictProcessor* const conflictProccesor,SphereHitChecker* const hitChecker);
    /// <summary>
    /// 衝突処理実行役を削除
    /// </summary>
    /// <param name="conflictProccesor">消したい衝突処理実行役</param>
    /// /// <param name="hitChecker">当たり判定も消す</param>
    static void EraceConflictProccesor(ConflictProcessor* const conflictProccesor, SphereHitChecker* const hitChecker);
    /// <summary>
    /// デバッグ用球を出す
    /// </summary>
    void DrawCollisionSphere();
    /// <summary>
    /// 引数のオブジェクト同士がぶつかっているか調べその結果を返す
    /// </summary>
    /// <param name="conflictProccesor">衝突処理実行役</param>
    /// <param name="hitChecker">当たり判定</param>
    /// <returns>衝突結果</returns>
    ConflictExamineResultInfo GetConflictResultInfo(ConflictProcessor* const conflictProccesor, SphereHitChecker* const hitChecker);
    /// <summary>
    /// 何か衝突している物がないか調べる
    /// </summary>
    void Update();
private:
    //当たった結果を反映させるクラスのマップ
    static std::unordered_map<ConflictProcessor*, SphereHitChecker*> processorKeyMap;
    //conflictProcessor持ちの当たり判定か調べるためのマップ
    static std::unordered_map<SphereHitChecker*, ConflictProcessor*> hitCheckerKeyMap;
    //当たっているか調べるクラスのリスト
    static std::list<SphereHitChecker*> hitCheckList;
};