#include "ActorControllerManager.h"
#include "ActorController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
std::list<ActorController*> ActorControllerManager::actorControllerList;
ActorControllerManager::ActorControllerManager()
{
    actorControllerList.clear();
}

ActorControllerManager::~ActorControllerManager()
{
    for (auto ite = actorControllerList.begin(); ite != actorControllerList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    actorControllerList.clear();
}

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
    damageObjGenerator->GetObjectList(this);
}

void ActorControllerManager::GameReserve()
{
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->GameReserve();
    }
}

void ActorControllerManager::Draw()const
{
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}

void ActorControllerManager::AddActorController(ActorController* actorController)
{
    if (actorController != nullptr)
    {
        actorControllerList.push_back(actorController);
    }
}
