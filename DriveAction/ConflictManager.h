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
    ~ConflictManager();
    /// <summary>
    /// 当たり判定追加
    /// </summary>
    /// <param name="hitChecker"></param>
    static void AddHitChecker(SphereHitChecker* hitChecker);
    /// <summary>
    /// 当たり判定消去
    /// </summary>
    /// <param name="hitChecker"></param>
    static void EraceHitChecker(SphereHitChecker* hitChecker);
    /// <summary>
    /// 衝突処理を呼びたいやつを追加
    /// </summary>
    /// <param name="conflictProccesor">呼びたいやつ</param>
    /// <param name="hitChecker">呼びたいやつの当たり判定</param>
    static void AddConflictProcessor(ConflictProcessor* conflictProccesor,SphereHitChecker* hitChecker);

    /// <summary>
    /// 衝突処理を呼ばなくていいようにする
    /// </summary>
    /// <param name="conflictProccesor">呼ばなくていいように</param>
    static void EraceConflictProccesor(ConflictProcessor* conflictProccesor, SphereHitChecker* hitChecker);
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
    ConflictExamineResultInfo GetConflictResultInfo(ConflictProcessor* conflictProccesor, SphereHitChecker* hitChecker);
    /// <summary>
    /// 何か衝突している物がないか調べる
    /// </summary>
    void Update();
private:
    //当たった結果を反映させるクラスのマップ
    static std::unordered_map<ConflictProcessor*, SphereHitChecker*> processorKeyMap;
    
    static std::unordered_map<SphereHitChecker*, ConflictProcessor*> hitCheckerKeyMap;
    //当たっているか調べるクラスのリスト
    static std::list<SphereHitChecker*> hitCheckList;
};