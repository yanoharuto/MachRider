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
/// 敵コントローラーに位置情報を教えて追加する
/// </summary>
/// <param name="collectNum">プレイヤーが収集したアイテム数</param>
/// <param name="addObjController">敵コントローラー</param>
void EnemyGenerator::GenerateEnemys(int collectNum, ActorController* const addObjController)
{
    addObjController->AddObject(GetNowEnemyEditData(collectNum));
}
/// <summary>
/// エネミーの配置情報を渡す
/// </summary>
/// <param name="collectNum">今の収集アイテムの所得数</param>
/// <returns>エネミーの配置情報</returns>
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