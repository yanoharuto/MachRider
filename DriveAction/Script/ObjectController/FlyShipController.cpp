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
    param.actorParam = InitActor::GetActorParamator(kind);
    ObjectInit::AddDataObject addKind = AddDataObject::circleFlyShip;
    switch (kind)//�~�����ǉ��f�[�^�̎��
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
    GetInitAddData(addKind);//�ǉ��f�[�^����
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
void FlyShipController::GetInitAddData(ObjectInit::AddDataObject kind)
{
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
}