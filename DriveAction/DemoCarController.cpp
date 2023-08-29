#include "DemoCarController.h"
#include "DemoCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "DrawModel.h"
/// <summary>
/// タイトルで走らせる
/// </summary>
DemoCarController::DemoCarController(VECTOR setPos, VECTOR setDir)
    :ActorController(ObjectInit::player)
{
    demoCar = new DemoCar(setPos, setDir);
    observer = std::make_shared<ObjectObserver>(demoCar);
    drawModel = new DrawModel(ObjectInit::player);
}

DemoCarController::~DemoCarController()
{
    SAFE_DELETE(demoCar);
    observer.reset();
    SAFE_DELETE(drawModel);
}
/// <summary>
/// 車の移動
/// </summary>
void DemoCarController::Update()
{
    demoCar->Update();
}
/// <summary>
/// 今動いているかどうか
/// </summary>
/// <returns></returns>
bool DemoCarController::IsAlive() const
{
    return demoCar->GetObjectState() != Object::dead;
}

/// <summary>
/// 描画
/// </summary>
void DemoCarController::Draw() const
{
    drawModel->Draw(demoCar);
}
/// <summary>
/// 位置の初期化
/// </summary>
void DemoCarController::InitPosition()
{
    demoCar->InitPosition();
}
/// <summary>
/// 車の位置などをカメラなどに渡せるようにする
/// </summary>
/// <returns></returns>
std::shared_ptr<ObjectObserver> DemoCarController::CreateCarObserver()
{
    return observer;
}
