#include "ActorControllerManager.h"
#include "ActorController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "EnemyGenerator.h"
//actor管理クラスのリスト
std::list<ActorController*> ActorControllerManager::actorControllerList;
/// <summary>
/// actorの動きを制御している物を全部束ねて動かす
/// </summary>
ActorControllerManager::ActorControllerManager()
{
    actorControllerList.clear();
    enemyGenerator = new EnemyGenerator();
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
    //イテレーター
    auto objIte = actorControllerList.begin();
    //消去していいやつリスト
    std::list<ActorController*> brokenList;
    //更新する必要が無くなったら消去
    while (objIte != actorControllerList.end())
    {
        (*objIte)->Update();
        //もう存在していなかったら更新終了
        if (!(*objIte)->IsAlive()) 
        {
            brokenList.push_back((*objIte));

            objIte = actorControllerList.erase(objIte);//eraseは消したイテレーターの次の奴を返す
        }
        else
        {
            ++objIte;//消す条件に合わなかったら次に
        }
    }
    //消していいやつ消す
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    //さっきの処理でオブジェクトが増やしたアイテムを取ってくる
    damageObjGenerator->MoveControllerList(this);
    enemyGenerator->GetActorControllerVector(this);
}
/// <summary>
/// ゲーム開始前更新
/// </summary>
void ActorControllerManager::GameReserve()
{
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
