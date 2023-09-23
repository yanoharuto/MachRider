#include "FlyShipController.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 初期化するために必要なデータを所得
/// </summary>
/// <param name="kind">初期化したいFlyShipの種類</param>
FlyShipController::FlyShipController(ObjectInit::InitObjKind kind, std::shared_ptr<DamageObjectGenerator> damageObjGenerator)
    :AddableObjectController(kind)
{
    param = GetInitData(kind);
    damageObjectGenerator = damageObjGenerator;
}
/// <summary>
/// actorListとDrawModelとdamageObjectGeneratorの解放
/// </summary>
FlyShipController::~FlyShipController()
{
    DeleteActorListAndDrawModel();
    damageObjectGenerator.reset();
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
    auto addData = addDataLoader->GeFileStringData();
    using enum FlyShipParamator;
    //移動速度
    param.moveSpeed = STR_TO_F(addData[CAST_I(moveSpeed)]);
    //生存時間
    param.setAliveTime = STR_TO_F(addData[CAST_I(aliveTime)]);
    //クールタイム
    param.setCoolTime = STR_TO_F(addData[CAST_I(coolTime)]);
    //１グループ何体か
    param.unitNum = STR_TO_I(addData[CAST_I(unitNum)]);
    //個体間距離
    param.unitBetween = STR_TO_F(addData[CAST_I(unitBetween)]);
    return param;
}