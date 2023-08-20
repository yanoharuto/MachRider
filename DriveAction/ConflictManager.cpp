#include "ConflictManager.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ConflictProcessor.h"
#include "SphereHitChecker.h"
//当たった結果を反映させるクラスのマップ
std::unordered_map<ConflictProcessor*,SphereHitChecker*> ConflictManager::processorKeyMap;
//conflictProcessor持ちの当たり判定か調べるためのマップ
std::unordered_map<SphereHitChecker*, ConflictProcessor*> ConflictManager::hitCheckerKeyMap;
//当たっているか調べるクラスのリスト
std::list<SphereHitChecker*> ConflictManager::hitCheckList;
/// <summary>
/// 当たり判定を纏めてするための奴
/// </summary>
ConflictManager::ConflictManager()
{
    processorKeyMap.clear();
    hitCheckerKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// 当たり判定登録Map全消し
/// </summary>
ConflictManager::~ConflictManager()
{
    processorKeyMap.clear();
    hitCheckerKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// 当たり判定追加
/// </summary>
/// <param name="hitChecker"></param>
void ConflictManager::AddHitChecker(SphereHitChecker* const hitChecker)
{
    hitCheckList.push_back(hitChecker);
}
/// <summary>
/// 当たり判定消去
/// </summary>
/// <param name="hitChecker"></param>
void ConflictManager::EraceHitChecker(SphereHitChecker* const hitChecker)
{
    if(!hitCheckList.empty())
    {
        //消したい当たり判定があるなら
        auto procceesor = std::find(hitCheckList.begin(), hitCheckList.end(), hitChecker);
        if (procceesor != hitCheckList.end())
        {
            hitCheckList.erase(procceesor);
        }
    }
}

/// <summary>
/// 衝突処理実行役を追加
/// </summary>
/// <param name="conflictProccesor">追加したい衝突処理実行役</param>
/// <param name="hitChecker">呼びたいやつの当たり判定</param>
void ConflictManager::AddConflictProcessor(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
{
    processorKeyMap.insert(std::make_pair(conflictProcessor, hitChecker));
    hitCheckerKeyMap.insert(std::make_pair(hitChecker, conflictProcessor));
    AddHitChecker(hitChecker);
}

/// <summary>
/// 衝突処理実行役を削除
/// </summary>
/// <param name="conflictProccesor">消したい衝突処理実行役</param>
/// /// <param name="hitChecker">当たり判定も消す</param>
void ConflictManager::EraceConflictProccesor(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
{
    if (!processorKeyMap.empty())
    {
        //衝突処理実行役をmapから削除
        for (auto mapItr = processorKeyMap.begin(); mapItr != processorKeyMap.end(); mapItr++)
        {
            if ((*mapItr).first == conflictProcessor)
            {
                processorKeyMap.erase(mapItr);
                break;
            }
        }
        //当たり判定がKeyのmapから削除
        for (auto mapItr = hitCheckerKeyMap.begin(); mapItr != hitCheckerKeyMap.end(); mapItr++)
        {
            if ((*mapItr).first == hitChecker)
            {
                hitCheckerKeyMap.erase(mapItr);
                break;
            }
        }
        //当たり判定削除
        EraceHitChecker(hitChecker);
    }
}
/// <summary>
/// デバッグ用の球当たり判定を見せる
/// </summary>
void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = hitCheckList.begin(); objIte != hitCheckList.end(); objIte++)
    {
       HitCheckExamineObjectInfo info = (*objIte)->GetHitExamineCheckInfo();
        DrawSphere3D(info.pos, info.radius, 4, GetColor(200, 200, 200), GetColor(200, 200, 200), false);
    }
}
/// <summary>
/// 引数のオブジェクト同士がぶつかっているか調べその結果を返す
/// </summary>
/// <param name="conflictProccesor">衝突処理実行役</param>
/// <param name="hitChecker">当たり判定</param>
/// <returns>衝突結果</returns>
ConflictExamineResultInfo ConflictManager::GetConflictResultInfo(ConflictProcessor* const conflictProccesor, SphereHitChecker* const hitChecker)
{
    HitCheckExamineObjectInfo examineInfo = conflictProccesor->GetHitExamineCheckInfo();
    //引数のオブジェクトそのものと当たってたらスルー もう動いてなくてもぶつかっているか調べない
    if (hitChecker != processorKeyMap[conflictProccesor] && !hitChecker->IsDead())
    {
        //当たっているか調べる
        ConflictExamineResultInfo examineResultInfo = hitChecker->HitCheck(examineInfo);

        //当たった情報を渡す
        return examineResultInfo;
    }
    return ConflictExamineResultInfo{};
}

/// <summary>
/// 当たり判定をする
/// </summary>
void ConflictManager::Update()
{
    //衝突処理実行役
    for (auto processorItr = processorKeyMap.begin(); processorItr != processorKeyMap.end(); processorItr++)
    {
        //当たり判定調査役
        for (auto hitCheckItr = hitCheckList.begin(); hitCheckItr != hitCheckList.end(); hitCheckItr++)
        {
            //当たり判定結果
            ConflictExamineResultInfo resultInfo = GetConflictResultInfo((*processorItr).first, *hitCheckItr);
            //衝突処理実行役同士の衝突なら
            if (hitCheckerKeyMap.contains(*hitCheckItr))
            {
                //こっちにも当たり判定処理実行
                hitCheckerKeyMap[*hitCheckItr]->ConflictProcess(GetConflictResultInfo(hitCheckerKeyMap[*hitCheckItr], processorKeyMap[(*processorItr).first]));
            }
            //衝突処理実行
            (*processorItr).first->ConflictProcess(resultInfo);
        }
    }
}
