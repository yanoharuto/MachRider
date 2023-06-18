#include "ConflictManager.h"

std::list<ConflictProccesor*> ConflictManager::conflictObjList;
ConflictManager::ConflictManager()
{
    conflictObjList.clear();
}

ConflictManager::~ConflictManager()
{
    conflictObjList.clear();
}
/// <summary>
/// 当たり判定を追加
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::AddConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    conflictObjList.push_back(conflictProccesor);
}
/// <summary>
///　当たり判定をしなくていいようにする
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::EraceConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    auto procceesor = std::find(conflictObjList.begin(), conflictObjList.end(), conflictProccesor);
    if (procceesor != conflictObjList.end())
    {
        conflictObjList.erase(procceesor);
    }
}
/// <summary>
/// デバッグ用の球当たり判定を見せる
/// </summary>
void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
       HitCheckExamineObjectInfo info = (*objIte)->GetHitExamineCheckInfo();
        DrawSphere3D(info.pos, info.radius, 4, GetColor(200, 200, 200), GetColor(200, 200, 200), false);
    }
}

/// <summary>
/// 引数のオブジェクトとぶつかっているか調べる
/// </summary>
/// <param name="examineObjInfo"></param>
/// <returns></returns>
std::list<ConflictExamineResultInfo> ConflictManager::GetConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    std::list<ConflictExamineResultInfo> nowHitList;
    ConflictExamineResultInfo examineResultInfo = {};
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        //引数のオブジェクトそのものと当たってたらスルー 動いていなくても
        if (conflictProccesor != (*objIte)||(*objIte)->IsObjectAlive())
        {
            //当たっているか調べる
            examineResultInfo = (*objIte)->HitCheck(conflictProccesor->GetHitExamineCheckInfo());
            //ぶつかっているなら
            if (examineResultInfo.hit != HitSituation::NotHit)
            {
                //当たった情報を追加
                nowHitList.push_back(examineResultInfo);
            }
        }
    }
    return nowHitList;
}
/// <summary>
/// 当たり判定をする
/// </summary>
void ConflictManager::Update()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        
        (*objIte)->ConflictProccess(GetConflictObjInfo((*objIte)));
    }
}
