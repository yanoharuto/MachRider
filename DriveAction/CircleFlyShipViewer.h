#pragma once
#include "EditorDrawModel.h"

/// <summary>
/// �~�`��ɐw�`��g�ޓG�̕`��S��
/// </summary>
class CircleFlyShipDrawer final:
    public EditorDrawModel
{
public:
    CircleFlyShipDrawer();
    /// <summary>
    /// �`�悷��
    /// </summary>
    /// <param name="data"></param>
    void Draw(PlacementData data)const override;
    /// <summary>
    /// �ҏW���ɑI������Ă���Ƃ��኱���ɕ`�悷��
    /// </summary>
    /// <param name="data"></param>
    void SelectDraw(PlacementData data)const override;
private:
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    void Init();
    //���j�b�g�̐�
    int uniNum = 0;
    //�e���j�b�g�̕����ւ̊p�x
    float uniDirRota = 0.0f;
    //���j�b�g���m�̋���
    float uniBetween=0.0f;
};