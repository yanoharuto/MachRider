#include "ActorController.h"
#include "Actor.h"
#include "Utility.h"
ActorController::ActorController()
{
}

ActorController::ActorController(Actor* actor)
{
    actorList.push_back(actor);
}

ActorController::~ActorController()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    actorList.clear();
}

void ActorController::Update()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
    }
}

void ActorController::GameReserve()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->GameReserve();
    }
}

void ActorController::Draw() const
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Draw();
    }
}

bool ActorController::IsAlive() const
{
    //Ž€‚ñ‚Å‚È‚¢‚È‚çtrue‚ð•Ô‚·
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        if ((*ite)->GetObjectState() != Object::ObjectState::dead)return true;
    }
    return false;
}
