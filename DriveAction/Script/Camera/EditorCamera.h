#pragma once
#include "Camera.h"
/// <summary>
/// �ҏW���[�h���̃J����
/// </summary>
class EditorCamera : public Camera
{
public:
    /// <summary>
    /// �ҏW���[�h���̃J����
    /// </summary>
    EditorCamera();
    /// <summary>
    /// �㉺�L�[�œ��������Ƃ��o����
    /// </summary>
    void Update();
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns>�J�����̌����x�N�g��</returns>
    static VECTOR GetNormDirection();
private:
    //��]���x
    const float rotaSpeed = 3.0f;
    //���L�������
    static VECTOR staticDir;
};

