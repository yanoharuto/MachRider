#include "Clock.h"
#include "DxLib.h"
#include "Utility.h"
#include "Menu.h"
//���ʂ̌o�ߕb��
double Clock::gameTime;
Clock::Clock()
{
    // ���݂̃J�E���g���擾����
    timeD = static_cast<double>(GetNowHiPerformanceCount());
    gameTime = static_cast<double>(GetNowHiPerformanceCount()) / 1000000;
}

Clock::~Clock()
{
}

/// <summary>
/// �^�C�}�[���X�V����
/// </summary>
void Clock::Update()
{
    // �P�V�~���b(��b�ԂU�O�t���[�����������̂P�t���[��������̌o�ߎ���)
    // �o�߂���܂ł����ő҂�
   double temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    while (temp < DELTATIME)
    {
        temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    }

    // ���݂̃J�E���g���擾����
    timeD =  static_cast<double>(GetNowHiPerformanceCount());
    
    gameTime = timeD / 1000000;
}

double Clock::GetNowGameTime()
{
    return gameTime - Menu::GetOpenMenuTime();
}
