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
    /// �J�����̌���ׂ�������ύX
    /// </summary>
    /// <param name="targetPlaceData">���������ꏊ�̔z�u���</param>
    void UpdatePositionAndTarget(PlacementData targetPlaceData);
    /// <summary>
    /// �㉺���E�L�[�Ō����ƃ^�[�Q�b�g�܂ł̋�����ύX����
    /// </summary>
    void UpdateDirectionAndTargetBetween();

private:
    //��]���x
    const float rotaSpeed = 3.0f;
};

