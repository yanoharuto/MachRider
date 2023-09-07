#include "ActorControllerManager.h"
#include "AddableObjectController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "CollectController.h"
#include "CollectItemObserver.h"
#include "EnemyGenerator.h"
#include "CircleFlyShipController.h"
#include "UpDownFlyShipController.h"
#include "MoveSawController.h"
#include "BomberFlyShipController.h"
#include "SawController.h"
#include "RotatingLaserController.h"
#include "BomberController.h"
#include "StageObjectController.h"
/// <summary>
/// ゲーム中に使うオブジェクトの管理クラスの確保
/// </summary>
/// <param name="collectItemObserver">収集アイテムが取られたりしたら教えてもらう</param>
ActorControllerManager::ActorControllerManager(std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    collectObserver = collectItemObserver;
    //ステージの生成
    actorControllerList.push_back(std::make_shared<StageObjectController>());
    //レーザー管理クラス
    std::shared_ptr<RotatingLaserController> laserController = std::make_shared<RotatingLaserController>();
    //爆弾管理クラス
    std::shared_ptr<BomberController> bombController = std::make_shared<BomberController>();
    //ダメージ判定ありオブジェクト生成クラス
    damageObjGenerator = std::make_shared<DamageObjectGenerator>(laserController, bombController);
    actorControllerList.push_back(laserController);
    actorControllerList.push_back(bombController);
    //各敵管理クラス
    addableActorControllerList.push_back(std::make_shared<SawController>());
    addableActorControllerList.push_back(std::make_shared<MoveSawController>());
    addableActorControllerList.push_back(std::make_shared<CircleFlyShipController>(damageObjGenerator));
    addableActorControllerList.push_back(std::make_shared<BomberFlyShipController>(damageObjGenerator));
    addableActorControllerList.push_back(std::make_shared<UpDownFlyShipController>(damageObjGenerator));
    //敵生成クラス
    enemyGenerator = new EnemyGenerator();
    //オブジェクトを生成
    for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
    {
        enemyGenerator->GenerateEnemys(0, *ctrItr);
    }
}
/// <summary>
/// 管理クラスやステージのオブジェクトなどをすべて解放
/// </summary>
ActorControllerManager::~ActorControllerManager()
{
    for (auto ite = actorControllerList.begin(); ite != actorControllerList.end(); ite++)
    {
        (*ite).reset();
    }
    for (auto ite = addableActorControllerList.begin(); ite != addableActorControllerList.end(); ite++)
    {
        (*ite).reset();
    }
    damageObjGenerator.reset();
    SAFE_DELETE(enemyGenerator);
}
/// <summary>
/// 更新
/// </summary>
void ActorControllerManager::Update()
{
    //敵生成処理
    GenerateEnemyProcess();
    Update(actorControllerList);
    Update(addableActorControllerList);
}
/// <summary>
/// ゲーム開始前更新
/// </summary>
void ActorControllerManager::PrepareGame()
{
    //敵生成処理
    GenerateEnemyProcess();
    PrepareGame(actorControllerList);
    PrepareGame(addableActorControllerList);
}
/// <summary>
/// 各アクターの描画
/// </summary>
void ActorControllerManager::Draw()const
{
    Draw(actorControllerList);
    Draw(addableActorControllerList);
}
/// <summary>
/// actor管理クラスを追加
/// </summary>
/// <param name="actorController"></param>
void ActorControllerManager::AddActorController(std::shared_ptr<ActorController> actorController)
{
    if (actorController != nullptr)
    {
        actorControllerList.push_back(actorController);
    }
}
/// <summary>
/// 2つのActor管理クラスどちらでも使えるゲーム開始前更新
/// </summary>
/// <typeparam name="controllerClass">Actor管理クラス</typeparam>
/// <param name="controllerList">controllerClassを纏めたリスト</param>
template<typename controllerClass>
void ActorControllerManager::PrepareGame(std::list<std::shared_ptr<controllerClass>> controllerList)
{
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->PrepareGame();
    }
}
/// <summary>
/// 2つのActor管理クラスどちらでも使える更新
/// </summary>
/// <typeparam name="controllerClass">Actor管理クラス</typeparam>
/// <param name="controllerList">controllerClassを纏めたリスト</param>
template<typename controllerClass>
void ActorControllerManager::Update(std::list<std::shared_ptr<controllerClass>> controllerList)
{
    //更新する
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->Update();
    }
}
/// <summary>
/// 2つのActor管理クラスどちらでも使える描画
/// </summary>
/// <typeparam name="controllerClass">Actor管理クラス</typeparam>
/// <param name="controllerList">controllerClassを纏めたリスト</param>
template<typename controllerClass>
void ActorControllerManager::Draw(std::list<std::shared_ptr<controllerClass>> controllerList)const
{
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}
/// <summary>
///　敵生成処理
/// </summary>
void ActorControllerManager::GenerateEnemyProcess()
{
    //収集アイテムを取られた数
    int nowGetCollectNum = collectObserver->GetCollectCount();
    //取られた数が更新されたら
    if (nowGetCollectNum != collectNum)
    {
        //敵生成クラスに追加する必要がある事を教える
        for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
        {
            collectNum = nowGetCollectNum;
            enemyGenerator->GenerateEnemys(collectNum,*ctrItr);
        }
    }
}