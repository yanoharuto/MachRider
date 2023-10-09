#include "Menu.h"
#include "UserInput.h"
#include "DxLib.h"
#include "Utility.h"
#include "GameScreen.h"
#include "UIDrawer.h"
#include "Clock.h"
//���j���[�̏��
Menu::MenuOptions Menu::menuOption = Menu::MenuOptions::continueGame;
//���j���[���J���Ă��邩
bool Menu::isOpenMenu = false;
//���j���[���J���Ă��鎞��
double Menu::openMenuTime=0;
/// <summary>
/// �eUI������
/// </summary>
Menu::Menu()
{
    using enum Menu::MenuOptions;
    using enum UIKind;
    //�Q�[�����s���
    menuOption = continueGame;
    //���ڂ��ړ�����J�[�\����UI
    cursorUIData = UIManager::CreateUIData(menuCursor);
    //�e���ڂ�UI����
    uiDatas[static_cast<int>(continueGame)] = UIManager::CreateUIData(playUI);
    uiDatas[static_cast<int>(exitGame)] = UIManager::CreateUIData(exitUI);
    uiDatas[static_cast<int>(retry)] = UIManager::CreateUIData(retryUI);
    uiDatas[static_cast<int>(returnTitle)] = UIManager::CreateUIData(returnTitleBottonUI);
    isOpenMenu = false;
    openMenuTime = 0;
}
/// <summary>
/// ���j���[���J�������Ԃ�0��
/// </summary>
Menu::~Menu()
{
    openMenuTime = 0;
    UIManager::DeleteUIGraph(&cursorUIData);
    for (int i = 0; i < MENU_STATE_KIND_NUM; i++)
    {
        UIManager::DeleteUIGraph(&uiDatas[i]);
    }
}
/// <summary>
/// ���ڂ̕ύX�Ȃ�
/// </summary>
void Menu::Update()
{    
    using enum Menu::MenuOptions;
    
    //�J���Ă���Ƃ��ɏ㉺�ɉ����ƍ��ڂ�ύX
    if (isOpenMenu)
    {
        if (UserInput::GetInputState(Up) == Push)
        {
            selectUI--;

            //��ԏ�̍��ڂ��炳��ɏ�ɍs���ꍇ���̂܂�
            if (selectUI == 0)
            {
                selectUI = 0;
            }
        }
        else if (UserInput::GetInputState(Down) == Push)
        {
            selectUI++;
            //��ԉ��̍��ڂ��炳��ɉ��ɍs���ꍇ���̂܂�
            if (selectUI > MENU_STATE_KIND_NUM)
            {
                selectUI = MENU_STATE_KIND_NUM;
            }
        }
        //�ړ���̃J�[�\��
        cursorUIData.y = uiDatas[selectUI % MENU_STATE_KIND_NUM].y;

        //���j���[���J������ԂŃX�y�[�X�L�[���������牟�������ڂ�ۑ�
        if (UserInput::GetInputState(Input::Space) == Push)
        {
            menuOption = static_cast<MenuOptions>(selectUI);
            isOpenMenu = !(menuOption == continueGame);
            openMenuTime += Clock::GetNowGameTime() - startTime;
        }
    }
    //Escape����������
    else if (UserInput::GetInputState(Input::EscapeKey) == Push)
    {
        //���j���[��ʂ��J�����������
        isOpenMenu = !isOpenMenu;
        selectUI = 0;

        if (isOpenMenu)
        {
            backScreen = GameScreen::GetScreen();
            //���j���[��ʂ��J�������Ԃ�����
            startTime = Clock::GetNowGameTime();
        }
        else
        {
            //���j���[��ʂ��J���Ă��鎞�Ԃ��v��
            openMenuTime += Clock::GetNowGameTime() - startTime;
        }
    }
}
/// <summary>
/// ���݂̃��j���[�̏��
/// </summary>
/// <returns>�v���C���[����蒼���������Q�[���𑱍s���������Ԃ�</returns>
Menu::MenuOptions Menu::GetMenuState()const
{
    return menuOption;
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
        SetDrawBright(Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE);
        //�eUI��`��  �I�𒆂Ȃ�񖇖ڂ̏�Ԃɂ���
        UIDrawer::DrawRotaUI(cursorUIData);
        DrawUI(MenuOptions::continueGame);
        DrawUI(MenuOptions::retry);
        DrawUI(MenuOptions::returnTitle);
        DrawUI(MenuOptions::exitGame);
    }
}
/// <summary>
/// ���j���[UI��\��
/// </summary>
/// <param name="option">�\������������ </param>
void Menu::DrawUI(Menu::MenuOptions state) const
{
    int menuKind = static_cast<int>(state);
    UIDrawer::DrawRotaUI(uiDatas[menuKind], selectUI == menuKind ? 0 : 1);
}