#include "Menu.h"
#include "UserInput.h"
#include "DxLib.h"
#include "Utility.h"
#include "StopWatch.h"
//���j���[�̏��
MenuState Menu::menuState=continueGame;
bool Menu::openMenu = false;
double Menu::openMenuTime=0;
Menu::Menu()
{
    menuState = continueGame;
    cursorUIData = UIManager::CreateUIData(menuCursor);
    uiDatas[continueGame] = UIManager::CreateUIData(playUI);
    uiDatas[exitGame] = UIManager::CreateUIData(exitUI);
    uiDatas[retry] = UIManager::CreateUIData(retryUI);
    openMenu = false;
    openMenuTime = 0;
    stopWatch = new StopWatch();
}

Menu::~Menu()
{
    openMenuTime = 0;
    SAFE_DELETE(stopWatch);
}

void Menu::Update()
{
    //Escape����������
    if (UserInput::GetInputState(Input::Escape) == Push)
    {
        //���j���[��ʂ��J�����������
        openMenu = !openMenu;
        cursolPos = 0;
        if (openMenu)
        {
            //�J���Ă��鎞�Ԃ��v���J�n
            stopWatch->Run();
        }
        else
        {
            //������v�����f
            stopWatch->Stop();
        }
    }
    else if (UserInput::GetInputState(Input::Space) == Push)
    {
        //���j���[���J������ԂŃX�y�[�X�L�[���������牟�������ڂ�ۑ�
        menuState = static_cast<MenuState>(cursolPos);
        openMenu = !(menuState == continueGame);
    }
    //�J���Ă���Ƃ��ɏ㉺�ɉ����ƍ��ڂ�ύX
    if (openMenu)
    {
        //���j���[��ʂ��J���Ă��鎞�Ԃ𑝂₷
        openMenuTime = stopWatch->GetRunTime();
        if (UserInput::GetInputState(Up)==Push)
        {
            cursolPos--;
            //��ԏ�̍��ڂ��炳��ɏ�ɍs���ꍇ���̂܂�
            if (cursolPos  < 0) 
            {
                cursolPos = 0;
            }
        }
        else if (UserInput::GetInputState(Down)==Push)
        {
            cursolPos++;
            //��ԉ��̍��ڂ��炳��ɉ��ɍs���ꍇ���̂܂�
            if (cursolPos > 2)
            {
                cursolPos = 2;
            }
        }
        cursorUIData.y = uiDatas[cursolPos].y;
    }
}
/// <summary>
/// ���݂̃��j���[�̏��
/// </summary>
/// <returns></returns>
MenuState Menu::GetMenuState()
{
    return menuState;
}
bool Menu::IsMenuOpen()
{
    return openMenu;
}
double Menu::GetOpenMenuTime()
{
    printfDx("MenuTime::%f", openMenuTime);
    return openMenuTime;
}
/// <summary>
/// UI��`��
/// </summary>
void Menu::Draw()
{
    if (openMenu)
    {
        DrawUI(cursorUIData, 0);
        DrawUI(uiDatas[continueGame], cursolPos == 0 ? 0 : 1);
        DrawUI(uiDatas[retry], cursolPos == 1 ? 0 : 1);
        DrawUI(uiDatas[exitGame], cursolPos == 2 ? 0 : 1);
    }
}
/// <summary>
/// ������UI��`��
/// </summary>
/// <param name="data"></param>
/// <param name="handleNum"></param>
void Menu::DrawUI(UIData data, int handleNum)
{
    DrawRotaGraph(data.x, data.y, data.size, 0, data.dataHandle[handleNum], true, false);
}