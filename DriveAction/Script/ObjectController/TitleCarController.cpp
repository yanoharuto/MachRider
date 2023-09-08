#include "TitleCarController.h"
#include "TitleCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "DrawModel.h"
/// <summary>
/// タイトルで走らせる車
/// </summary>
/// <param name="setPos">初期位置</param>
/// <param name="setDir">初期向き</param>
/// <param name="initTimer">定期的に初期位置に戻すためのタイマー</param>
TitlteCarController::TitlteCarController(VECTOR setPos, VECTOR setDir, std::shared_ptr<Timer> initTimer)
    :ActorController(ObjectInit::player)
{
    titleCar = new TitleCar(setPos, setDir,initTimer);
    observer = std::make_shared<ObjectObserver>(titleCar);
    drawModel = new DrawModel(ObjectInit::player);
}
/// <summary>
/// 走っている車と描画役の開放
/// </summary>
TitlteCarController::~TitlteCarController()
{
    SAFE_DELETE(titleCar);
    observer.reset();
    SAFE_DELETE(drawModel);
}
/// <summary>
/// 車の移動
/// </summary>
void TitlteCarController::Update()
{
    titleCar->Update();
}
/// <summary>
/// 描画
/// </summary>
void TitlteCarController::Draw() const
{
    drawModel->Draw(titleCar);
}
/// <summary>
/// 車の位置などをカメラなどに渡せるようにする
/// </summary>
/// <returns>車情報伝達役</returns>
std::shared_ptr<ObjectObserver> TitlteCarController::CreateCarObserver()
{
    return observer;
}
