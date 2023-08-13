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
/// <summary>
/// 空飛んでるやつの情報所得
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
FlyShipInit::InitFlyShipParamator FlyShipController::GetInitData(ObjectInit::InitObjKind kind)
{
    //modelの当たり判定とか取ってくる
    FlyShipInit::InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip用のデータをロード
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(kind));
    auto addData = addDataLoader->GetLoadCharData();
    //移動速度
    param.moveSpeed = static_cast<float>(atof(addData[moveSpeed]));
    //生存時間
    param.setAliveTime = static_cast<float>(atof(addData[aliveTime]));
    //クールタイム
    param.setCoolTime = static_cast<float>(atof(addData[coolTime]));
    //１グループ何体か
    param.unitNum = static_cast<float>(atof(addData[unitNum]));
    //個体間距離
    param.unitBetween = static_cast<float>(atof(addData[unitBetween]));
    return param;
}
