#pragma once
#include "Camera.h"
/// <summary>
/// �ҏW���[�h���̃J����
/// </summary>
class EditorCamera :
    public Camera
{
public:
    EditorCamera();
    void Update();
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns></returns>
    static VECTOR GetNormDirection();
private:
    //��]���x
    const float rotaSpeed = 3.0f;
    //���L�������
    static VECTOR staticDir;
};

