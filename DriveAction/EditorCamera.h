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
    /// ����
    /// </summary>
    /// <returns></returns>
    static VECTOR GetNormDirection();
private:
    const float rotaSpeed = 3.0f;
    static VECTOR staticDir;
};

