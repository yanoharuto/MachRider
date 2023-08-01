#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "CSVFileLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "SphereCollider.h"
/// <summary>
/// �ړ���]�̂�����
/// </summary>
/// <param name="editData"></param>
MoveSaw::MoveSaw(EditArrangementData editData)
    :Saw(editData)
{
    InitParamater(moveSaw);
    firstDir = direction;
    ActorParameter initParam = InitActor::GetActorParamator(moveSaw);
    auto addDataLoader = new CSVFileLoader(initParam.addData);
    auto addStrDataVec = addDataLoader->GetLoadStringData();
    speed= atoi(addStrDataVec[moveSpeed].c_str());
    moveLarpTimer = new ReusableTimer(atoi(addStrDataVec[moveTime].c_str()));
    //�O�������ɓ���
    velocity = VScale(direction, speed);
    //�����蔻��
    collider = new SphereCollider(this);
}
/// <summary>
/// �ړ����Ȃ����]����
/// </summary>
void MoveSaw::Update()
{
    if (moveLarpTimer->IsOverLimitTime())//���Ԃ����ς��������甽�Ε����ɓ���
    {
        moveLarpTimer->Reuse();
        
        velocity = VSub(VGet(0,0,0),velocity);
    }
    position = VAdd(position, velocity);
    //��]
    direction = VNorm(OriginalMath::GetYRotateVector(direction, addRotate));
}