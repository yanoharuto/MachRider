#include "SawController.h"
#include "DrawModel.h"
#include "Saw.h"
#include "Utility.h"
/// <summary>
/// プレイヤーをはじき飛ばす丸鋸
/// </summary>
SawController::SawController()
    :AddableObjectController(ObjectInit::saw)
{
    drawModel = new DrawModel(controllObjKind);
}
/// <summary>
/// 丸鋸を追加
/// </summary>
/// <param name="editData">追加する位置などの情報</param>
void SawController::AddObject(PlacementData editData)
{
    actorList.push_back(new Saw(editData));
}
/// <summary>
/// 回転させる　破壊されたら破棄
/// </summary>
void SawController::Update()
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
