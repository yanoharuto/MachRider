#include "ObjectObserver.h"

/// <summary>
/// �I�u�W�F�N�g�̊Ď���
/// </summary>
/// <param name="setSubject">�Ď��������I�u�W�F�N�g</param>
ObjectObserver::ObjectObserver(Object* setSubject)
{
    subject = setSubject;
}
/// <summary>
/// �Ď��Ώۂ̈ʒu��n��
/// </summary>
/// <returns></returns>
Object::ObjectState ObjectObserver::GetSubjectState() const
{
    return subject->GetObjectState();
}
/// <summary>
/// �Ď��Ώۂ̌���
/// </summary>
/// <returns></returns>
VECTOR ObjectObserver::GetSubjectPos() const
{
    return subject->GetPos();
}
/// <summary>
/// �Ď��Ώۂ̏��
/// </summary>
/// <returns></returns>
VECTOR ObjectObserver::GetSubjectDir() const
{
    return subject->GetDir();
}