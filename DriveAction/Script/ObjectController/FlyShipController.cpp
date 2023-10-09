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
    param.actorParam = InitActor::GetActorParamator(kind);
    ObjectInit::AddDataObject addKind = AddDataObject::circleFlyShip;
    switch (kind)//欲しい追加データの種類
    {
    case InitObjKind::upDownLaserShip:
        addKind = AddDataObject::upDownFlyShip;
        break;
    case InitObjKind::bomberShip:
        addKind = AddDataObject::bomberShip;
        break;
    case InitObjKind::circleLaserShip:
        addKind = AddDataObject::circleFlyShip;
        break;
    default:
        break;
    }
    GetInitAddData(addKind);//追加データ所得
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
void FlyShipController::GetInitAddData(ObjectInit::AddDataObject kind)
{
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
}