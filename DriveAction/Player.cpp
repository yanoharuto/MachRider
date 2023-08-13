#include "Player.h"
#include "PlayerCar.h"
#include "SphereCollider.h"
#include "SoundPlayer.h"
#include "SoundListener.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "PlayerViewer.h"
#include "PlayerObserver.h"
/// <summary>
/// プレイヤーの車の管理
/// </summary>
Player::Player()
    :ActorController(ObjectInit::player)
{
    auto editData = FirstPositionGetter::GetInitData(Object::player);
    car = new PlayerCar(editData[0]);
    playerObserver = std::make_shared<PlayerObserver>(car);
    listener = new SoundListener(CreatePlayerObserver());
    //プレイヤー描画役
    playerViewer = new PlayerViewer();
}
/// <summary>
/// 車とLisnerのDelete
/// </summary>
Player::~Player()
{
    
    SAFE_DELETE(car);
    SAFE_DELETE(listener);
}
/// <summary>
/// 車の位置とかを渡す
/// </summary>
/// <returns></returns>
std::weak_ptr<PlayerObserver> Player::CreatePlayerObserver() const
{
    return playerObserver;
}
/// <summary>
/// 音を聞くために場所を更新
/// </summary>
void Player::Update()
{
    car->Update();
    listener->Update();
}
/// <summary>
/// 描画
/// </summary>
void Player::Draw() const
{
    playerViewer->Draw(car);
}
