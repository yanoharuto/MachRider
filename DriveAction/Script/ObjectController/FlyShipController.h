#pragma once
#include "DxLib.h"
#include "InitObjKind.h"
#include <list>
#include "InitActor.h"
#include "AddableObjectController.h"
namespace FlyShipInit
{
    /// <summary>
    /// ����ԑD�̏��������
    /// </summary>
    struct InitFlyShipParamator
    {
        //�傫���Ƃ�model�̃p�X�Ƃ������蔻��̑傫���Ƃ�
        ActorParameter actorParam;
        //��������
        float setAliveTime;
        //�ړ����x
        float moveSpeed;
        //���˂̃N�[���^�C��
        float setCoolTime;
        //���j�b�g���m�̋���
        float unitBetween;
        //�c�̍s������ꍇ�̍\����
        int unitNum;
    };
    /// <summary>
    /// ����ԑD�̃p�����[�^���
    /// </summary>
    enum FlyShipParamator
    {
        //��������
        aliveTime = 2,

        //�ړ����x
        moveSpeed = 5,

        //�������甭�˂��鎞��
        coolTime = 8,

        //�\����
        unitNum = 11,

        //�U�����j�b�g���m�̋���
        unitBetween = 14
    };
}
class FlyShip;
using namespace FlyShipInit;
/// <summary>
/// ����ԑD�̂܂Ƃߖ�
/// </summary>
class FlyShipController abstract : public AddableObjectController
{
public:
    /// <summary>
    /// ���������邽�߂ɕK�v�ȃf�[�^������
    /// </summary>
    /// <param name="kind">������������FlyShip�̎��</param>
    FlyShipController(ObjectInit::InitObjKind kind);
protected:
    /// <summary>
    /// ���������邽�߂ɕK�v�ȃf�[�^������
    /// </summary>
    /// <param name="kind">������������FlyShip�̎��</param>
    /// <returns>�������f�[�^</returns>
    InitFlyShipParamator GetInitData(ObjectInit::InitObjKind kind);
    //���������
    InitFlyShipParamator param = {};
};

