#pragma once

//fps
#define FLAME 60
class Clock
{
public:
    Clock();
    ~Clock();
    /// <summary>
    /// �^�C�}�[���X�V����
    /// </summary>
    void Update();

    static double GetNowGameTime();
private:

    double timeD;
    double openMenuTime;
    static double gameTime;
    static double totalOpenMenuTime;
    //���j���[���J��������
    static double openStartMenuTime;
};