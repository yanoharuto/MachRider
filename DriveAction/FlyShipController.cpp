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
/// <summary>
/// ����ł��̏�񏊓�
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
FlyShipInit::InitFlyShipParamator FlyShipController::GetInitData(ObjectInit::InitObjKind kind)
{
    //model�̓����蔻��Ƃ�����Ă���
    FlyShipInit::InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip�p�̃f�[�^�����[�h
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(kind));
    auto addData = addDataLoader->GetLoadCharData();
    //�ړ����x
    param.moveSpeed = static_cast<float>(atof(addData[moveSpeed]));
    //��������
    param.setAliveTime = static_cast<float>(atof(addData[aliveTime]));
    //�N�[���^�C��
    param.setCoolTime = static_cast<float>(atof(addData[coolTime]));
    //�P�O���[�v���̂�
    param.unitNum = static_cast<float>(atof(addData[unitNum]));
    //�̊ԋ���
    param.unitBetween = static_cast<float>(atof(addData[unitBetween]));
    return param;
}
