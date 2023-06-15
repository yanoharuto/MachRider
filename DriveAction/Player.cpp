#include "Player.h"
#include "ObjectSubject.h"
#include "PlayerCar.h"
#include "SphereCollider.h"
#include "ObjectObserver.h"
Player::Player(VECTOR firstPos,VECTOR direction)
{
    actorList.push_back( new PlayerCar(firstPos,direction));

    collider = new SphereCollider(*actorList.begin());
    collider->SetCoolTimer(Object::ObjectTag::damageObject, setDamageCoolTime);
    subject = new ObjectSubject(*actorList.begin(), collider);
}

std::shared_ptr<ObjectObserver> Player::CreatePlayerObserver() const
{
    return std::make_shared<ObjectObserver>(subject);
}

void Player::GameReserve()
{
    (*actorList.begin())->GameReserve();
}
