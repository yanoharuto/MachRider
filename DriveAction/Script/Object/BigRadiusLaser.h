#pragma once
#include "RotatingLasers.h"
class ObjectObserver;
/// <summary>
/// y����]���郌�[�U�[
/// </summary>
class BigRadiusLaser:public RotatingLasers
{
public:
    /// <summary>
    /// y����]���锼�a���傫�����[�U�[
    /// </summary>
    /// <param name="setObserver"></param>
    BigRadiusLaser(std::unique_ptr<ObjectObserver> setObserver);

    /// <summary>
    /// y����]������
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;

private:
    //���[�U�[�G�t�F�N�g�̃p�X
    static const InitParam initParam;
    
    //��]���x
    static const float rotaSpeed;
};

