#include "EnemyGenerator.h"
#include "Utility.h"
#include "InitActor.h"
#include "InitObjKind.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "ActorController.h"
/// <summary>
/// 敵機位置についての初期化する
/// </summary>
EnemyGenerator::EnemyGenerator()
{
    editDataVec = FirstPositionGetter::GetInitData(Object::damageObject);
}
/// <summary>
/// エネミーを生成
/// </summary>
/// <param name="collectNum">今プレイヤーは何個目の収集アイテムを取ったか</param>
void EnemyGenerator::GenerateEnemys(int collectNum, ActorController* const addObjController)
{
    addObjController->AddObject(GetNowEnemyEditData(collectNum));
}
/// <summary>
/// エネミーの配置情報を所得
/// </summary>
/// <param name="kind">どの種類か</param>
/// <param name="collectNum">何番目の収集アイテムの時か</param>
/// <returns>kindのエネミーの配置情報</returns>
std::vector<EditArrangementData> EnemyGenerator::GetNowEnemyEditData(int collectNum)
{
    std::vector<EditArrangementData> editData;
    for (int i = 0; i < editDataVec.size(); i++)
    {
        ObjectInit::InitObjKind dataKind = static_cast<ObjectInit::InitObjKind>(editDataVec[i].objKind);
        //プレイヤーが収集アイテムを取ってきたらそのタイミングで敵を増やす
        if (editDataVec[i].missionNum == collectNum)
        {
            editData.push_back(editDataVec[i]);
        }
    }
    return editData;
}