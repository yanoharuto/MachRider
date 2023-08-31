#include "ActorControllerManager.h"
#include "AddableObjectController.h"
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
/// <summary>
/// 敵などをNewして配置する
/// </summary>
ActorControllerManager::ActorControllerManager()
{
    //敵生成クラス
    enemyGenerator = new EnemyGenerator();
    //ダメージ判定ありオブジェクト生成クラス
    damageObjGenerator = new DamageObjectGenerator(this);
    //各敵管理クラス
    addableActorControllerList.push_back(new SawController());
    addableActorControllerList.push_back(new MoveSawController());
    addableActorControllerList.push_back(new CircleFlyShipController());
    addableActorControllerList.push_back(new BomberFlyShipController());
    addableActorControllerList.push_back(new UpDownFlyShipController());
    //オブジェクトを生成
    for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
    {
        enemyGenerator->GenerateEnemys(0,*ctrItr);
    }
}
/// <summary>
/// 敵の管理クラスやステージのオブジェクトなどをすべて解放
/// </summary>
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
void ActorControllerManager::AddActorController(ActorController* actorController)
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
void ActorControllerManager::PrepareGame(std::list<controllerClass*> controllerList)
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
void ActorControllerManager::Update(std::list<controllerClass*> controllerList)
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
void ActorControllerManager::Draw(std::list<controllerClass*> controllerList)const
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
    int nowGetCollectNum = CollectController::GetTotalCollectNum() - CollectController::GetRemainingCollectNum();
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