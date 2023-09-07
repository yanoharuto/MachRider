#include "TitleCarController.h"
#include "TitleCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "DrawModel.h"
/// <summary>
/// タイトルで走らせる
/// </summary>
TitlteCarController::TitlteCarController(VECTOR setPos, VECTOR setDir)
    :ActorController(ObjectInit::player)
{
    titleCar = new TitleCar(setPos, setDir);
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
/// 位置の初期化
/// </summary>
void TitlteCarController::InitPosition()
{
    titleCar->InitPosition();
}
/// <summary>
/// 車の位置などをカメラなどに渡せるようにする
/// </summary>
/// <returns></returns>
std::shared_ptr<ObjectObserver> TitlteCarController::CreateCarObserver()
{
    return observer;
}
