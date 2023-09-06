#include "FlyShipController.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 初期化するために必要なデータを所得
/// </summary>
/// <param name="kind">初期化したいFlyShipの種類</param>
FlyShipController::FlyShipController(ObjectInit::InitObjKind kind)
    :AddableObjectController(kind)
{
    param = GetInitData(kind);
}
/// <summary>
/// 空飛んでるやつの情報所得
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
InitFlyShipParamator FlyShipController::GetInitData(ObjectInit::InitObjKind kind)
{
    //modelの当たり判定とか取ってくる
    InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip用のデータをロード
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(kind));
    auto addData = addDataLoader->GetLoadStringData();
    //移動速度
    param.moveSpeed = SAFE_STR_TO_F(addData[moveSpeed]);
    //生存時間
    param.setAliveTime = SAFE_STR_TO_F(addData[aliveTime]);
    //クールタイム
    param.setCoolTime = SAFE_STR_TO_F(addData[coolTime]);
    //１グループ何体か
    param.unitNum = SAFE_STR_TO_I(addData[unitNum]);
    //個体間距離
    param.unitBetween = SAFE_STR_TO_F(addData[unitBetween]);
    return param;
}
