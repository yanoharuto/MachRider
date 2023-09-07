#include "PlayerCarController.h"
#include "PlayerCar.h"
#include "SphereHitChecker.h"
#include "SoundPlayer.h"
#include "SoundListener.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "PlayerDrawModel.h"
#include "PlayerObserver.h"
/// <summary>
/// プレイヤーの車の初期化
/// </summary>
PlayerCarController::PlayerCarController()
    :ActorController(ObjectInit::player)
{
    //初期位置
    std::vector<PlacementData> editData = FirstPositionGetter::GetPlaceData(Object::player);
    //車の開放
    car = new PlayerCar(editData[0]);
    playerObserver = std::make_shared<PlayerObserver>(car);
    //プレイヤーの位置から音を集めるリスナーの設定
    listener = new SoundListener(CreatePlayerObserver());
    //プレイヤー描画役
    playerDrawer = new PlayerDrawModel();
}
/// <summary>
/// 車とLisnerのDelete
/// </summary>
PlayerCarController::~PlayerCarController()
{
    SAFE_DELETE(car);
    SAFE_DELETE(listener);
}
/// <summary>
/// 車の位置とかを渡す
/// </summary>
/// <returns></returns>
std::shared_ptr<PlayerObserver> PlayerCarController::CreatePlayerObserver() const
{
    return playerObserver;
}
/// <summary>
/// 音を聞くために場所を更新
/// </summary>
void PlayerCarController::Update()
{
    car->Update();
    listener->Update();
}
/// <summary>
/// 描画
/// </summary>
void PlayerCarController::Draw() const
{
    playerDrawer->Draw(car);
}
