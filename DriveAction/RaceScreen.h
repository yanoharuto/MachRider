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
    /// �`�悵����ʂ�ۑ�
    /// </summary>
    void ScreenUpdate();
    /// <summary>
    /// �ۑ�������ʂ�n��
    /// </summary>
    /// <returns></returns>
    static int GetScreen();
    
private:
   static int screen;
};

