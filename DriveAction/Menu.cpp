#include "Menu.h"
#include "UserInput.h"
#include "DxLib.h"
#include "Utility.h"
#include "RaceScreen.h"
#include "UIDrawer.h"
#include "Clock.h"
//���j���[�̏��
MenuState Menu::menuState=continueGame;
//���j���[���J���Ă��邩
bool Menu::isOpenMenu = false;
//���j���[���J���Ă��鎞��
double Menu::openMenuTime=0;

Menu::Menu()
{
    menuState = continueGame;
    cursorUIData = UIManager::CreateUIData(menuCursor);
    uiDatas[continueGame] = UIManager::CreateUIData(playUI);
    uiDatas[exitGame] = UIManager::CreateUIData(exitUI);
    uiDatas[retry] = UIManager::CreateUIData(retryUI);
    isOpenMenu = false;
    openMenuTime = 0;
}

Menu::~Menu()
{
    openMenuTime = 0;
}

void Menu::Update()
{
    //Escape����������
    if (UserInput::GetInputState(Input::EscapeKey) == Push)
    {
        //���j���[��ʂ��J�����������
        isOpenMenu = !isOpenMenu;
        cursolPos = 0;
        if (isOpenMenu)
        {
            backScreen = RaceScreen::GetScreen();
            //���j���[��ʂ��J�������Ԃ�����
            startTime = Clock::GetNowGameTime();
        }
        else
        {
            openMenuTime += Clock::GetNowGameTime() - startTime;
        }
    }
    //���j���[���J������ԂŃX�y�[�X�L�[���������牟�������ڂ�ۑ�
    else if (UserInput::GetInputState(Input::Space) == Push && isOpenMenu)
    {
        menuState = static_cast<MenuState>(cursolPos);
        isOpenMenu = !(menuState == continueGame);
        openMenuTime += Clock::GetNowGameTime() - startTime;
    }
    //�J���Ă���Ƃ��ɏ㉺�ɉ����ƍ��ڂ�ύX
    if (isOpenMenu)
    {
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
/// <summary>
/// ���j���[��ʂ��J���Ă��邩�ǂ���
/// </summary>
/// <returns></returns>
bool Menu::IsMenuOpen()
{
    return isOpenMenu;
}
/// <summary>
/// ���j���[��ʂ��J���Ă��鎞�Ԃ�����
/// </summary>
/// <returns></returns>
double Menu::GetOpenMenuTime()
{
    return openMenuTime;
}
/// <summary>
/// UI��`��
/// </summary>
void Menu::Draw() const
{
    if (isOpenMenu)
    {
        SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
        DrawGraph(0, 0, backScreen, false);
        SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
        //�eUI��`��
        UIDrawer::DrawRotaUI(cursorUIData);
        UIDrawer::DrawRotaUI(uiDatas[continueGame], cursolPos == 0 ? 0 : 1);
        UIDrawer::DrawRotaUI(uiDatas[retry], cursolPos == 1 ? 0 : 1);
        UIDrawer::DrawRotaUI(uiDatas[exitGame], cursolPos == 2 ? 0 : 1);
    }
}