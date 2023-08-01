#include "FlyShipController.h"
#include "CSVFileLoader.h"

/// <summary>
/// 初期化するために必要なデータを所得
/// </summary>
/// <param name="kind">初期化したいFlyShipの種類</param>
/// <returns></returns>
using namespace FlyShipInit;
FlyShipController::FlyShipController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
    param = GetInitData(kind);
}
FlyShipInit::InitFlyShipParamator FlyShipController::GetInitData(ObjectInit::InitObjKind kind)
{
    //modelの当たり判定とか取ってくる
    FlyShipInit::InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip用のデータをロード
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetActorParamator(kind).addData);
    auto addData = addDataLoader->GetLoadCharData();
    param.moveSpeed = static_cast<float>(atof(addData[moveSpeed]));
    param.setAliveTime = static_cast<float>(atof(addData[aliveTime]));
    param.setCoolTime = static_cast<float>(atof(addData[coolTime]));
    param.unitNum = static_cast<float>(atof(addData[unitNum]));
    param.unitBetween = static_cast<float>(atof(addData[unitBetween]));
    return param;
}
