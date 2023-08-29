#include "Player.h"
#include "PlayerCar.h"
#include "SphereCollider.h"
#include "SoundPlayer.h"
#include "SoundListener.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "PlayerDrawModel.h"
#include "PlayerObserver.h"
/// <summary>
/// �v���C���[�̎Ԃ̊Ǘ�
/// </summary>
Player::Player()
    :ActorController(ObjectInit::player)
{
    auto editData = FirstPositionGetter::GetInitData(Object::player);
    car = new PlayerCar(editData[0]);
    playerObserver = std::make_shared<PlayerObserver>(car);
    listener = new SoundListener(CreatePlayerObserver());
    //�v���C���[�`���
    playerDrawer = new PlayerDrawModel();
}
/// <summary>
/// �Ԃ�Lisner��Delete
/// </summary>
Player::~Player()
{
    
    SAFE_DELETE(car);
    SAFE_DELETE(listener);
}
/// <summary>
/// �Ԃ̈ʒu�Ƃ���n��
/// </summary>
/// <returns></returns>
std::weak_ptr<PlayerObserver> Player::CreatePlayerObserver() const
{
    return playerObserver;
}
/// <summary>
/// ���𕷂����߂ɏꏊ���X�V
/// </summary>
void Player::Update()
{
    car->Update();
    listener->Update();
}
/// <summary>
/// �`��
/// </summary>
void Player::Draw() const
{
    playerDrawer->Draw(car);
}
