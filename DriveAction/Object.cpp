#include "Object.h"
#include "InitActor.h"
/// <summary>
/// �I�u�W�F�N�g�̎�ނ�n����
/// </summary>
/// <param name="kind"></param>
Object::Object(ObjectInit::InitObjKind kind)
{
    InitParamater(kind);
}
Object::~Object()
{
 
}
/// <summary>
/// �R���X�g���N�^�ŌĂ΂�鏈��
/// </summary>
void Object::InitParamater(ObjectInit::InitObjKind kind)
{
    ActorParameter initParam = InitActor::GetActorParamator(kind);
    //�|�W�V����
    position.y = initParam.firstPosY;
    //����
    direction = { 1,0,0 };
    //���˕Ԃ��
    bouncePower = initParam.setBouncePow;
    //���a
    radius = initParam.setRadius;
    //model�̑傫��
    modelSize = initParam.setModelSize;
}
/// <summary>
/// �ʒu�������Velocity�ɍ��킹�čX�V����
/// </summary>
void Object::ReflectsVelocity()
{
    // �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // �|�W�V�������X�V.
    position = VAdd(position, velocity);
}
