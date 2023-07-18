#pragma once
#include "UIManager.h"

enum MenuState
{
    //�Q�[���𑱍s�������ꍇ
    continueGame = 0,
    //��蒼�����������
    retry = 1,
    //�Q�[���I��
    exitGame = 2,
};
class StopWatch;
using namespace UIInit;
class Menu
{
public:
    Menu();
    ~Menu();
    /// <summary>
    /// ���ڂ̕ύX�Ȃ�
    /// </summary>
    /// <returns></returns>
    void Update();
    /// <summary>
    /// ���݂̃��j���[�̏��
    /// </summary>
    /// <returns></returns>
    MenuState GetMenuState();
    /// <summary>
    /// ���j���[��ʂ��J���Ă��邩�ǂ���
    /// </summary>
    /// <returns></returns>
    static bool IsMenuOpen();
    /// <summary>
    /// ���j���[��ʂ��J���Ă��鎞�Ԃ�����
    /// </summary>
    /// <returns></returns>
    static double GetOpenMenuTime();
    /// <summary>
    /// UI��`��
    /// </summary>
    void Draw()const;
private:
    //���j���[��ʂ��J���Ă��鎞�Ԃ̌v��
    float startTime;
    //���j���[�̔w�i
    int backScreen;
    //�w�i�̖��邳
    int backScreenBright = 80;
    //���j���[�̏��
    static MenuState menuState;
    //���j���[��ʂ��J���Ă��邩
    static bool isOpenMenu;
    //���j���[��ʂ��J���Ă���Ԃɗ����Ă��鎞��
    static double openMenuTime;
    //Menu�̊O�g
    UIData cursorUIData;
    //���j���[�̍���
    UIData uiDatas[3];
    //�I��
    int cursolPos = 0;
};

