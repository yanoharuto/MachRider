#include "FlyShipController.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// ���������邽�߂ɕK�v�ȃf�[�^������
/// </summary>
/// <param name="kind">������������FlyShip�̎��</param>
FlyShipController::FlyShipController(ObjectInit::InitObjKind kind, std::shared_ptr<DamageObjectGenerator> damageObjGenerator)
    :AddableObjectController(kind)
{
    param = GetInitData(kind);
    damageObjectGenerator = damageObjGenerator;
}
/// <summary>
/// actorList��DrawModel��damageObjectGenerator�̉��
/// </summary>
FlyShipController::~FlyShipController()
{
    DeleteActorListAndDrawModel();
    damageObjectGenerator.reset();
}
/// <summary>
/// ����ł��̏�񏊓�
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
InitFlyShipParamator FlyShipController::GetInitData(ObjectInit::InitObjKind kind)
{
    //model�̓����蔻��Ƃ�����Ă���
    InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip�p�̃f�[�^�����[�h
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(kind));
    auto addData = addDataLoader->GeFileStringData();
    using enum FlyShipParamator;
    //�ړ����x
    param.moveSpeed = STR_TO_F(addData[CAST_I(moveSpeed)]);
    //��������
    param.setAliveTime = STR_TO_F(addData[CAST_I(aliveTime)]);
    //�N�[���^�C��
    param.setCoolTime = STR_TO_F(addData[CAST_I(coolTime)]);
    //�P�O���[�v���̂�
    param.unitNum = STR_TO_I(addData[CAST_I(unitNum)]);
    //�̊ԋ���
    param.unitBetween = STR_TO_F(addData[CAST_I(unitBetween)]);
    return param;
}