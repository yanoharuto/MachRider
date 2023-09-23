#pragma once
#include <memory>
#include <iostream>
#include "DxLib.h"
class Object;
class Camera;
/// <summary>
/// �J�����̌������I�u�W�F�N�g�ɓn�����߂̃N���X
/// </summary>
class CameraObserver
{
public:
    /// <summary>
    /// �J���������L���Ă��炤
    /// </summary>
    /// <param name="setCamera">���L���Ă��炤�J����</param>
    CameraObserver(std::shared_ptr<Camera> setCamera);
    /// <summary>
    /// �J�����J��
    /// </summary>
    ~CameraObserver();
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns>�ҏW�J�����̌���</returns>
    VECTOR GetCameraDir()const;
    /// <summary>
    /// �����̂��̂��J�����͈͓̔������ׂ�
    /// </summary>
    /// <param name="obj">���ׂ����I�u�W�F�N�g</param>
    /// <returns>�J�����͈͓̔��Ȃ�True</returns>
    bool IsLookingCamera(const Object* const obj) const;
private:
    //�ҏW���̃J����
    std::shared_ptr<Camera> camera;
};
