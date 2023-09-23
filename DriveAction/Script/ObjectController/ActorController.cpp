#include "ActorController.h"
#include "Actor.h"
#include "DrawModel.h"
#include "Utility.h"
#include "CameraObserver.h"
/// <summary>
/// 描画役とオブジェクトのデリート
/// </summary>
ActorController::~ActorController()
{
    DeleteActorListAndDrawModel();
}
/// <summary>
/// ゲーム開始準備処理
/// </summary>
void ActorController::PrepareGame()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->PrepareGame();
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
void ActorController::Draw(std::weak_ptr<CameraObserver> cameraObserever) const
{
    if (drawModel != nullptr)
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            if(cameraObserever.lock()->IsLookingCamera(*ite))//カメラの範囲内なら
            {
                //Drawerに渡して描画してもらう
                drawModel->Draw((*ite));
            }
        }
    }
}
/// <summary>
/// 描画役とActorListの解放
/// </summary>
void ActorController::DeleteActorListAndDrawModel()
{
    if (!actorList.empty())
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            SAFE_DELETE(*ite);
        }
        actorList.clear();
    }
    SAFE_DELETE(drawModel);
}