#include "ConflictManager.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ConflictProcessor.h"
#include "SphereHitChecker.h"
#include "Utility.h"
//当たった結果を反映させるクラスのマップ
std::unordered_map<ConflictProcessor*,SphereHitChecker*> ConflictManager::processorKeyMap;
//conflictProcessor持ちの当たり判定か調べるためのマップ
std::unordered_map<SphereHitChecker*, ConflictProcessor*> ConflictManager::hitCheckerKeyMap;
//当たっているか調べるクラスのリスト
std::list<SphereHitChecker*> ConflictManager::hitCheckList;
/// <summary>
/// 当たり判定を纏めて行うための奴
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
/// <param name="conflictProcessor">追加したい衝突処理実行役</param>
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
/// <param name="conflictProcessor">消したい衝突処理実行役</param>
/// /// <param name="hitChecker">当たり判定も消す</param>
void ConflictManager::EraceConflictProcessor(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
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
       HitCheckInfo info = (*objIte)->GetHitExamineCheckInfo();
       DrawSphere3D(info.pos, info.radius, 4, GetColor(Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE), GetColor(Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE), false);
    }
}
/// <summary>
/// 引数のオブジェクト同士がぶつかっているか調べその結果を返す
/// </summary>
/// <param name="conflictProcessor">衝突処理実行役</param>
/// <param name="hitChecker">当たり判定</param>
/// <returns>衝突結果</returns>
CollisionResultInfo ConflictManager::GetConflictResultInfo(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
{
    HitCheckInfo examineInfo = conflictProcessor->GetHitExamineCheckInfo();
    //引数のオブジェクトそのものと当たってたらスルー もう動いてなくてもぶつかっているか調べない
    if (hitChecker != processorKeyMap[conflictProcessor] && !hitChecker->IsDead())
    {
        //当たっているか調べる
        CollisionResultInfo examineResultInfo = hitChecker->HitCheck(examineInfo);

        //当たった情報を渡す
        return examineResultInfo;
    }
    return CollisionResultInfo{};
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
            CollisionResultInfo resultInfo = GetConflictResultInfo((*processorItr).first, *hitCheckItr);
            //衝突処理実行役同士の衝突なら
            if (hitCheckerKeyMap.contains(*hitCheckItr))
            {
                //こっちにも当たり判定処理実行
                hitCheckerKeyMap[*hitCheckItr]->OnConflict(GetConflictResultInfo(hitCheckerKeyMap[*hitCheckItr], processorKeyMap[(*processorItr).first]));
            }
            //衝突処理実行
            (*processorItr).first->OnConflict(resultInfo);
        }
    }
}
