#pragma once
#include "DxLib.h"

/// <summary>
/// �`�悵���摜��ۑ�����
/// </summary>
class RaceScreen
{
public:
    RaceScreen();
    ~RaceScreen();
    /// <summary>
    /// �`�悵�Ă���摜���X�V
    /// </summary>
    void ScreenUpdate();
    void Draw();
    
private:
   int screen;
};

