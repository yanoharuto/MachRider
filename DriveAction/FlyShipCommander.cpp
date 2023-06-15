#include "FlyShipCommander.h"
#include "CSVFileLoader.h"

FlyShipCommander::FlyShipCommander()
{
}

using namespace FlyShipInit;
FlyShipInit::InitFlyShipParamator FlyShipCommander::GetInitData(ObjectInit::InitObjKind kind)
{
    //model�̓����蔻��Ƃ�����Ă���
    FlyShipInit::InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip�p�̃f�[�^�����[�h
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetActorParamator(kind).addData);
    auto addData = addDataLoader->GetLoadCharData();
    param.moveSpeed = atof(addData[moveSpeed]);
    param.setAliveTime = atof(addData[aliveTime]);
    param.setCoolTime = atof(addData[coolTime]);
    param.unitNum = atof(addData[unitNum]);
    param.unitBetween = atof(addData[unitBetween]);
    return param;
}
