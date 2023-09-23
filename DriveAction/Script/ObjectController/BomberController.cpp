#include "BomberController.h"
#include "Bomber.h"
#include "ObjectObserver.h"
#include "DrawModel.h"
#include "Utility.h"
/// <summary>
/// 爆弾制御係
/// </summary>
/// <param name="sub"></param>
BomberController::BomberController()
    :DamageObjectController(ObjectInit::InitObjKind::bomber)
{
    drawModel = new DrawModel(ObjectInit::InitObjKind::bomber);
}
/// <summary>
/// 爆弾を更新できるようにする
/// </summary>
/// <param name="sub">爆弾を投下したオブジェクト</param>
void BomberController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new Bomber(std::move(sub)));
}
/// <summary>
/// 爆弾を落下させる
/// </summary>
void BomberController::Update()
{
    if(!actorList.empty())
    {
        //破棄するリスト
        std::list<std::list<Actor*>::iterator> brokenList;
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            (*ite)->Update();
            //更新
            if ((*ite)->GetObjectState() == Object::ObjectState::dead)//爆破終了後は破棄
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
}