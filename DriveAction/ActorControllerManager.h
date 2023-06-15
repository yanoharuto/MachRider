#pragma once
#include <list>
class ActorController;
class DamageObjectGenerator;
class ActorControllerManager final
{
public:
    ActorControllerManager();
    ~ActorControllerManager();
    void Update();
    void GameReserve();
    void Draw()const;
    void AddActorController(ActorController* actorController);
private:
    static std::list<ActorController*> actorControllerList;
    DamageObjectGenerator* damageObjGenerator;
};

