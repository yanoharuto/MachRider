#pragma once
#include<memory>
#include<iostream>
#include <list>
#include "DxLib.h"
#include "InitObjKind.h"
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
    enum class FlyShipParamator
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
class DamageObjectGenerator;
using namespace FlyShipInit;
/// <summary>
/// ����ԑD�̂܂Ƃߖ�
/// </summary>
class FlyShipController abstract : public AddableObjectController
{
public:
    /// <summary>
    /// �Z�߂��s�D�̏��������邽�߂ɕK�v�ȃf�[�^������ 
    /// ��s�D�����˂��镨�𐶐��ł���damageObjGenerator������
    /// </summary>
    /// <param name="kind">������������FlyShip�̎��</param>
    /// <param name="damageObjGenerator">���[�U�[�┚�e�𔭎˂���̂Ɏg��</param>
    FlyShipController(ObjectInit::InitObjKind kind, std::shared_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// actorList��DrawModel��damageObjectGenerator�̉��
    /// </summary>
    ~FlyShipController()override;
protected:
    /// <summary>
    /// ���������邽�߂ɕK�v�ȃf�[�^������
    /// </summary>
    /// <param name="kind">������������FlyShip�̎��</param>
    /// <returns>�������f�[�^</returns>
    InitFlyShipParamator GetInitData(ObjectInit::InitObjKind kind);
    //���������
    InitFlyShipParamator param = {};
    //���[�U�[�┚�e�𔭎˂���̂Ɏg��
    std::shared_ptr<DamageObjectGenerator> damageObjectGenerator;
};