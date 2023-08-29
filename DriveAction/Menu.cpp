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
/// <summary>
/// �eUI������
/// </summary>
Menu::Menu()
{
    //�Q�[�����s���
    menuState = continueGame;
    cursorUIData = UIManager::CreateUIData(menuCursor);
    uiDatas[continueGame] = UIManager::CreateUIData(playUI);
    uiDatas[exitGame] = UIManager::CreateUIData(exitUI);
    uiDatas[retry] = UIManager::CreateUIData(retryUI);
    uiDatas[returnTitle] = UIManager::CreateUIData(returnTitleBottonUI);
    isOpenMenu = false;
    openMenuTime = 0;
}

Menu::~Menu()
{
    openMenuTime = 0;
}
/// <summary>
/// ���ڂ̕ύX�Ȃ�
/// </summary>
void Menu::Update()
{    
    //�J���Ă���Ƃ��ɏ㉺�ɉ����ƍ��ڂ�ύX
    if (isOpenMenu)
    {
        if (UserInput::GetInputState(Up)==Push)
        {
            cursolPos--;
            //��ԏ�̍��ڂ��炳��ɏ�ɍs���ꍇ���̂܂�
            if (cursolPos  < continueGame) 
            {
                cursolPos = continueGame;
            }
        }
        else if (UserInput::GetInputState(Down)==Push)
        {
            cursolPos++;
            //��ԉ��̍��ڂ��炳��ɉ��ɍs���ꍇ���̂܂�
            if (cursolPos > exitGame)
            {
                cursolPos = exitGame;
            }
        }
        cursorUIData.y = uiDatas[cursolPos].y;
        //���j���[���J������ԂŃX�y�[�X�L�[���������牟�������ڂ�ۑ�
        if (UserInput::GetInputState(Input::Space) == Push)
        {
            menuState = static_cast<MenuState>(cursolPos);
            isOpenMenu = !(menuState == continueGame);
            openMenuTime += Clock::GetNowGameTime() - startTime;
        }
    }
    //Escape����������
    else if (UserInput::GetInputState(Input::EscapeKey) == Push)
    {
        //���j���[��ʂ��J�����������
        isOpenMenu = !isOpenMenu;
        cursolPos = continueGame;
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
}
/// <summary>
/// ���݂̃��j���[�̏��
/// </summary>
/// <returns>�v���C���[����蒼���������Q�[���𑱍s���������Ԃ�</returns>
MenuState Menu::GetMenuState()const
{
    return menuState;
}
/// <summary>
/// ���j���[��ʂ��J���Ă��邩�ǂ���
/// </summary>
/// <returns>�J���Ă�����True</returns>
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
        //�eUI��`��  �I�𒆂Ȃ�񖇖ڂ̏�Ԃɂ���
        UIDrawer::DrawRotaUI(cursorUIData);
        UIDrawer::DrawRotaUI(uiDatas[continueGame], cursolPos == continueGame ? 0 : 1);
        UIDrawer::DrawRotaUI(uiDatas[retry], cursolPos == retry ? 0 : 1);
        UIDrawer::DrawRotaUI(uiDatas[exitGame], cursolPos == exitGame ? 0 : 1);
        UIDrawer::DrawRotaUI(uiDatas[returnTitle], cursolPos == returnTitle ? 0 : 1);
    }
}