#include "ObjectObserver.h"

/// <summary>
/// オブジェクトの監視役
/// </summary>
/// <param name="setSubject">監視したいオブジェクト</param>
ObjectObserver::ObjectObserver(Object* setSubject)
{
    subject = setSubject;
}
/// <summary>
/// 監視対象の位置を渡す
/// </summary>
/// <returns></returns>
Object::ObjectState ObjectObserver::GetSubjectState() const
{
    return subject->GetObjectState();
}
/// <summary>
/// 監視対象の向き
/// </summary>
/// <returns></returns>
VECTOR ObjectObserver::GetSubjectPos() const
{
    return subject->GetPos();
}
/// <summary>
/// 監視対象の状態
/// </summary>
/// <returns></returns>
VECTOR ObjectObserver::GetSubjectDir() const
{
    return subject->GetDir();
}