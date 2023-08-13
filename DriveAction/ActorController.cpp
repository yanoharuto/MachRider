#include "ActorController.h"
#include "Actor.h"
#include "ModelViewer.h"
#include "Utility.h"
/// <summary>
/// デリート
/// </summary>
ActorController::~ActorController()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    actorList.clear();
    SAFE_DELETE(viewer);
}
/// <summary>
/// ゲーム開始準備処理
/// </summary>
void ActorController::GameReserve()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->GameReserve();
    }
}

/// <summary>
/// 更新
/// </summary>
void ActorController::Update()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        //各actorの更新
        (*ite)->Update();
    }
}

/// <summary>
/// 描画処理
/// </summary>
void ActorController::Draw() const
{
    if (viewer != nullptr)
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            //Viewerに渡して描画してもらう
            viewer->Draw((*ite));
        }
    }
}
/// <summary>
/// 役割を終えてたらfalse
/// </summary>
/// <returns></returns>
bool ActorController::IsAlive() const
{
    //中身がなかったら死んでる
    if (actorList.empty())return false;
    //死んでないならtrueを返す
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        if ((*ite)->GetObjectState() != Object::ObjectState::dead)return true;
    }
    return false;
}
