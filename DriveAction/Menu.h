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
    static bool IsMenuOpen();
    static double GetOpenMenuTime();
    /// <summary>
    /// UI��`��
    /// </summary>
    void Draw();
private:
    /// <summary>
    /// ������UI��`��
    /// </summary>
    /// <param name="data"></param>
    /// <param name="handleNum"></param>
    void DrawUI(UIData data,int handleNum);
    StopWatch* stopWatch;
    //���j���[�̏��
    static MenuState menuState;
    //���j���[��ʂ��J���Ă��邩
    static bool openMenu;

    static double openMenuTime;
    //Menu�̊O�g
    UIData cursorUIData;

    UIData uiDatas[3];
    //�I��
    int cursolPos = 0;
};

