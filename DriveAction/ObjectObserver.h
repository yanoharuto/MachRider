#pragma once
#include "DxLib.h"
#include <string>
#include "Object.h"
class ObjectSubject;
class ObjectObserver
{
public:
    /// <summary>
    /// 監視役
    /// </summary>
    /// <param name="setSubject"></param>
    ObjectObserver(ObjectSubject* setSubject);
    ~ObjectObserver();
    /// <summary>
    /// 監視対象の位置を渡す
    /// </summary>
    /// <returns></returns>
    VECTOR GetSubjectPos() const;
    /// <summary>
    /// 監視対象の向き
    /// </summary>
    /// <returns></returns>
    VECTOR GetSubjectDir() const;
    /// <summary>
    /// 監視対象が引数のものに当たった回数を返す
    /// </summary>
    /// <param name="objTag"></param>
    /// <returns></returns>
    int GetSubjectHitCount(Object::ObjectTag objTag)const;
    /// <summary>
    /// 監視対象の状態
    /// </summary>
    /// <returns></returns>
    Object::ObjectState GetSubjectState()const;
private:
    ObjectSubject* subject;
};

