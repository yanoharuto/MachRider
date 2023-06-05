#include <iostream>
#include <fstream>
#include "Player.h"
#include "Utility.h"
#include "Rule.h"
#include "UserInput.h"
#include "ObjectSubject.h"
#include "PlayerCar.h"
#include "SphereCollider.h"
#include "Object.h"
#include "ConflictManager.h"
Player::Player(VECTOR firstPos)
    :Racer()
{
    car = new PlayerCar(firstPos);

    collider = new SphereCollider(car);
    collider->SetCoolTimer(Object::ObjectTag::damageObject, setDamageCoolTime);
    subject = new ObjectSubject(car,collider);
}

Player::~Player()
{
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
    SAFE_DELETE(subject);
    SAFE_DELETE(car);
}

void Player::Update()
{
    car->Update();
}

ObjectSubject* Player::GetSubject()
{
    return subject;
}
