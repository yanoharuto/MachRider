#pragma once
#include "Object.h"
/// <summary>
/// �X�J�C�h�[��
/// </summary>
class SkyDome final :public Object
{
public:
    /// <summary>
    /// model�̃��[�h�ƃ^�O�t��
    /// </summary>
    /// <returns></returns>
    SkyDome();
    //model�̃f���[�g
    ~SkyDome();
    /// <summary>
    /// ��]������
    /// </summary>
    void Update();
    /// <summary>
    /// model�̕`��
    /// </summary>
    void Draw();

private:
    int modelHandle;
    float setSize = 4.0f;
    float rotaSpeed = 0.2f;
};

