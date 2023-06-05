#pragma once
#include "RotatingLasers.h"
class ObjectObserver;

class BigRadiusLaser:public RotatingLasers
{
public:
    BigRadiusLaser(ObjectObserver* setObserver);

    /// <summary>
/// ��]������
/// </summary>
/// <param name="deltaTime"></param>
    void Update()override;

private:
    //���[�U�[�G�t�F�N�g�̃p�X
    static const InitParam initParam;
    
    //��]���x
    static const float rotaSpeed;
};

