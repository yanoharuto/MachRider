#pragma once
#include "DxLib.h"
#include <string>
#include "Object.h"
class ObjectSubject;
class ObjectObserver
{
public:
    ObjectObserver(ObjectSubject* setSubject);
    ~ObjectObserver();
    VECTOR GetSubjectPos() const;
    VECTOR GetSubjectDir() const;
    int GetSubjectHitCount(Object::ObjectTag objTag)const;
    Object::ObjectState GetSubjectState()const;
private:
    ObjectSubject* subject;
};

