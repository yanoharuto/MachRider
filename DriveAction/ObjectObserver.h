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
    VECTOR GetSubPos();
    VECTOR GetSubDir();
    int GetObjHitCount(Object::ObjectTag objTag);
private:
    ObjectSubject* subject;
};

