#pragma once
#include "UIManager.h"

class PlayManualUI
{
public:
    /// <summary>
    /// �ړ����@UI�̕\��
    /// </summary>
    PlayManualUI();
    ~PlayManualUI();
    /// <summary>
    /// �v���C���[�̓��͂ɂ����UI�ύX
    /// </summary>
    void Update();
    /// <summary>
    /// ������@��`��
    /// </summary>
    void Draw() const;
private:
    //���������UI���
    UIData manualData;
};

