#include "MoveSawController.h"
#include "MoveSaw.h"
#include "DrawModel.h"
#include "Utility.h"
/// <summary>
/// 移動する回転のこぎりの管理者
/// </summary>
MoveSawController::MoveSawController()
    :AddableObjectController(ObjectInit::moveSaw)
{
    drawModel = new DrawModel(controllObjKind);
}
/// <summary>
/// 更新。　破壊されたら破棄
/// </summary>
void MoveSawController::Update()
{
    //破棄するリスト
    std::list<std::list<Actor*>::iterator> brokenList;
    //更新
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::dead)//爆破終了後は破棄
        {
            brokenList.push_back(ite);
            SAFE_DELETE(*ite);
        }
    }
    //actorListから削除
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}
/// <summary>
/// 移動する回転のこぎりの追加
/// </summary>
/// <param name="editData">位置や向き</param>
void MoveSawController::AddObject(PlacementData editData)
{
    actorList.push_back(new MoveSaw(editData));
}