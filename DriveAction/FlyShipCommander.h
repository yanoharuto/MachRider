#pragma once
#include "DxLib.h"
#include "InitObjKind.h"
#include <list>
#include "InitActor.h"

namespace FlyShipInit
{
    /// <summary>
    /// ����ԑD�̏��������
    /// </summary>
    struct InitFlyShipParamator
    {
        ActorParametor actorParam;
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
class FlyShipCommander
{
public:
    FlyShipCommander();
    FlyShipCommander(ObjectInit::InitObjKind objKind, VECTOR playerPos);
    ~FlyShipCommander();
    void Update();
    void Draw();
protected:
    /// <summary>
    /// ���������邽�߂ɕK�v�ȃf�[�^������
    /// </summary>
    /// <param name="kind">������������FlyShip�̎��</param>
    /// <returns></returns>
    FlyShipInit::InitFlyShipParamator GetInitData(ObjectInit::InitObjKind kind);
    std::list<FlyShip*> flyShipList;
};
