#pragma once
#include "ModelViewer.h"
class PlayerCar;
/// <summary>
/// �v���C���[�̋@�̂̌X���ȂǂɑΉ�����Viewer
/// </summary>
class PlayerViewer :
    public ModelViewer
{
public:
    /// <summary>
    /// �v���C���[�̋@�̂̌X���ȂǂɑΉ�����Viewer
    /// </summary>
    PlayerViewer();
    /// <summary>
    /// �v���C���[�̊p�x�ɍ��킹�ĉ�]����
    /// </summary>
    /// <param name="drawObj"></param>
    void Draw(PlayerCar* drawObj) const;
protected:
    /// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
    void ModelSetMatrix(PlayerCar* player) const;
};

