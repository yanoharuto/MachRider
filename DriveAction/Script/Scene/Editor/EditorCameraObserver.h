#pragma once
#include <memory>
#include <iostream>
#include "DxLib.h"

class EditorCamera;
/// <summary>
/// �J�����̌������I�u�W�F�N�g�ɓn�����߂̃N���X
/// </summary>
class EditorCameraObserver
{
public:
    /// <summary>
    /// �J���������L���Ă��炤
    /// </summary>
    /// <param name="editorCamera">���L���Ă��炤�J����</param>
    EditorCameraObserver(std::shared_ptr<EditorCamera> editorCamera);
    /// <summary>
    /// �J�����J��
    /// </summary>
    ~EditorCameraObserver();
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns>�ҏW�J�����̌���</returns>
    VECTOR GetCameraDir()const;
private:
    //�ҏW���̃J����
    std::shared_ptr<EditorCamera> camera;
};

