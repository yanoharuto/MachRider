#pragma once
#include "RotatingLasers.h"

/// <summary>
/// ����]���锼�a�����������[�U�[
/// </summary>
class LittleRadiusLaser :
    public RotatingLasers
{
public:
    /// <summary>
/// ����]���锼�a�����������[�U�[
/// </summary>
    LittleRadiusLaser(std::unique_ptr<ObjectObserver> observer);
    /// <summary>
    /// ��]
    /// </summary>
    void Update()override;
private:
    /// ��]���x
    static const float rotaSpeed;
    
    /// ���������
    static const InitParam initParam;
};

