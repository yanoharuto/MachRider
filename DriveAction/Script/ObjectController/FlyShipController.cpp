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
    //�ړ����x
    param.moveSpeed = SAFE_STR_TO_F(addData[moveSpeed]);
    //��������
    param.setAliveTime = SAFE_STR_TO_F(addData[aliveTime]);
    //�N�[���^�C��
    param.setCoolTime = SAFE_STR_TO_F(addData[coolTime]);
    //�P�O���[�v���̂�
    param.unitNum = SAFE_STR_TO_I(addData[unitNum]);
    //�̊ԋ���
    param.unitBetween = SAFE_STR_TO_F(addData[unitBetween]);
    return param;
}