#include "FlyShipController.h"
#include "CSVFileLoader.h"

/// <summary>
/// ���������邽�߂ɕK�v�ȃf�[�^������
/// </summary>
/// <param name="kind">������������FlyShip�̎��</param>
/// <returns></returns>
using namespace FlyShipInit;
FlyShipController::FlyShipController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
    param = GetInitData(kind);
}
FlyShipInit::InitFlyShipParamator FlyShipController::GetInitData(ObjectInit::InitObjKind kind)
{
    //model�̓����蔻��Ƃ�����Ă���
    FlyShipInit::InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip�p�̃f�[�^�����[�h
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetActorParamator(kind).addData);
    auto addData = addDataLoader->GetLoadCharData();
    param.moveSpeed = static_cast<float>(atof(addData[moveSpeed]));
    param.setAliveTime = static_cast<float>(atof(addData[aliveTime]));
    param.setCoolTime = static_cast<float>(atof(addData[coolTime]));
    param.unitNum = static_cast<float>(atof(addData[unitNum]));
    param.unitBetween = static_cast<float>(atof(addData[unitBetween]));
    return param;
}
