#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
class GimmickObject :
    public Object
{
public:
    GimmickObject();
    ~GimmickObject();
    virtual void Draw();
    virtual void ConflictProcess();
protected:
    int modelHandle;
};

