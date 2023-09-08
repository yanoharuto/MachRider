#pragma once
#include "Camera.h"
#include "EditObjectData.h"
/// <summary>
/// �ҏW���[�h���̃J����
/// </summary>
class EditorCamera : public Camera
{
public:
    /// <summary>
    /// �J�����̃X�s�[�h�Ȃǂ̏�����
    /// </summary>
    EditorCamera();
    /// <summary>
    /// �㉺���E�L�[�œ��������Ƃ��o����
    /// </summary>
    /// <param name="targetPlaceData">���������ꏊ�̔z�u���</param>
    void Update(PlacementData targetPlaceData);
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns>�J�����̌����x�N�g��</returns>
    VECTOR GetNormDirection();
private:
    //��]���x
    const float rotaSpeed = 3.0f;
};

