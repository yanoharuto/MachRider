#include "ActorControllerManager.h"
#include "ActorController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "CollectController.h"
#include "EnemyGenerator.h"
//actor管理クラスのリスト
std::list<ActorController*> ActorControllerManager::actorControllerList;
/// <summary>
/// actorの動きを制御している物を全部束ねて動かす
/// </summary>
ActorControllerManager::ActorControllerManager()
{
    actorControllerList.clear();
    enemyGenerator = new EnemyGenerator(this);
    damageObjGenerator = new DamageObjectGenerator(this);
    enemyGenerator->GenerateEnemys(0);
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
    int nowGetCollectNum = CollectController::GetTotalCollectNum() - CollectController::GetRemainingCollectNum();
    if (nowGetCollectNum != collectNum)
    {
        collectNum = nowGetCollectNum;
        enemyGenerator->GenerateEnemys(collectNum);
    }
}
