#pragma once
#include "DamageObjectController.h"
#include <vector>
class ObjectSubject;
class ObjectObserver;
/// <summary>
/// ���e�̍X�V��
/// </summary>
class BomberController :
    public DamageObjectController
{
public:
    /// <summary>
    /// ���e�̍X�V��
    /// </summary>
    BomberController() ;
    /// <summary>
    /// ���e���X�V�ł���悤�ɂ���
    /// </summary>
    /// <param name="sub">���e�𓊉������I�u�W�F�N�g</param>
    void AddObject(std::unique_ptr<ObjectObserver> sub)override;
private:
   
};

