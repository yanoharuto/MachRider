#include "ActorControllerManager.h"
#include "ActorController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "CollectController.h"
#include "EnemyGenerator.h"
#include "CircleFlyShipController.h"
#include "UpDownFlyShipController.h"
#include "MoveSawController.h"
#include "BomberFlyShipController.h"
#include "SawController.h"

//actor管理クラスのリスト
std::list<ActorController*> ActorControllerManager::actorControllerList;
/// <summary>
/// actorの動きを制御している物を全部束ねて動かす
/// </summary>
ActorControllerManager::ActorControllerManager()
{
    actorControllerList.clear();
    enemyGenerator = new EnemyGenerator();
    damageObjGenerator = new DamageObjectGenerator(this);
    AddActorController(new SawController());
    AddActorController(new MoveSawController());
    AddActorController(new CircleFlyShipController());
    AddActorController(new BomberFlyShipController());
    AddActorController(new UpDownFlyShipController());
    for (auto ctrItr = actorControllerList.begin(); ctrItr != actorControllerList.end(); ctrItr++)
    {
        enemyGenerator->GenerateEnemys(0,*ctrItr);
    }
}

ActorControllerManager::~ActorControllerManager()
{
    for (auto ite = actorControllerList.begin(); ite != actorControllerList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    actorControllerList.clear();
}
/// <summary>
/// 更新
/// </summary>
void ActorControllerManager::Update()
{
    //敵生成処理
    GenerateEnemyProcess();
    //更新する
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->Update();
    }
}
/// <summary>
/// ゲーム開始前更新
/// </summary>
void ActorControllerManager::GameReserve()
{
    //敵生成処理
    GenerateEnemyProcess();
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->GameReserve();
    }
}
/// <summary>
/// 各アクターの描画
/// </summary>
void ActorControllerManager::Draw()const
{
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}
/// <summary>
/// actor管理クラスを追加
/// </summary>
/// <param name="actorController"></param>
void ActorControllerManager::AddActorController(ActorController* actorController)
{
    if (actorController != nullptr)
    {
        actorControllerList.push_back(actorController);
    }
}

/// <summary>
///　敵生成処理
/// </summary>
void ActorControllerManager::GenerateEnemyProcess()
{
    //収集アイテムを取られた数
    int nowGetCollectNum = CollectController::GetTotalCollectNum() - CollectController::GetRemainingCollectNum();
    //取られた数が更新されたら
    if (nowGetCollectNum != collectNum)
    {
        //敵生成クラスに追加する必要がある事を教える
        for (auto ctrItr = actorControllerList.begin(); ctrItr != actorControllerList.end(); ctrItr++)
        {
            collectNum = nowGetCollectNum;
            enemyGenerator->GenerateEnemys(collectNum,*ctrItr);
        }
    }
}
