#include "Player.h"
#include "ObjectSubject.h"
#include "PlayerCar.h"
#include "SphereCollider.h"
#include "ObjectObserver.h"
#include "SoundPlayer.h"
#include "SoundListener.h"
#include "Utility.h"
Player::Player(VECTOR firstPos,VECTOR direction)
{
    actorList.push_back(new PlayerCar(firstPos,direction));

    collider = new SphereCollider(*actorList.begin());
    collider->SetCoolTimer(Object::ObjectTag::damageObject, setDamageCoolTime);
    observer = std::make_shared<ObjectObserver>(new ObjectSubject(*actorList.begin(), collider));
    listener = new SoundListener(CreatePlayerObserver());
}

Player::~Player()
{
    observer.reset();
    SAFE_DELETE(collider);
    SAFE_DELETE(listener);
}
/// <summary>
/// �Ԃ̈ʒu�Ƃ���n��
/// </summary>
/// <returns></returns>
std::weak_ptr<ObjectObserver> Player::CreatePlayerObserver() const
{
    return observer;
}
/// <summary>
/// ���𕷂����߂ɏꏊ���X�V
/// </summary>
void Player::Update()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
    }
    listener->Update();
}