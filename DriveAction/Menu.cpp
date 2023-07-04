#include "Menu.h"
#include "UserInput.h"
#include "DxLib.h"
#include "Utility.h"
#include "StopWatch.h"
#include "RaceScreen.h"
#include "UIDrawer.h"
//メニューの状態
MenuState Menu::menuState=continueGame;
//メニューを開いているか
bool Menu::isOpenMenu = false;
//メニューを開いている時間
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
    stopWatch = new StopWatch();
}

Menu::~Menu()
{
    openMenuTime = 0;
    SAFE_DELETE(stopWatch);
}

void Menu::Update()
{
    //Escapeを押したら
    if (UserInput::GetInputState(Input::EscapeKey) == Push)
    {
        //メニュー画面を開いたり閉じたり
        isOpenMenu = !isOpenMenu;
        cursolPos = 0;
        if (isOpenMenu)
        {
            //開いている時間を計測開始
            stopWatch->Run();
            backScreen = RaceScreen::GetScreen();
        }
        else
        {
            //閉じたら計測中断
            stopWatch->Stop();
        }
    }
    else if (UserInput::GetInputState(Input::Space) == Push)
    {
        //メニューを開いた状態でスペースキーを押したら押した項目を保存
        menuState = static_cast<MenuState>(cursolPos);
        isOpenMenu = !(menuState == continueGame);
    }
    //開いているときに上下に押すと項目を変更
    if (isOpenMenu)
    {
        //メニュー画面を開いている時間を増やす
        openMenuTime = stopWatch->GetRunTime();
        if (UserInput::GetInputState(Up)==Push)
        {
            cursolPos--;
            //一番上の項目からさらに上に行く場合そのまま
            if (cursolPos  < 0) 
            {
                cursolPos = 0;
            }
        }
        else if (UserInput::GetInputState(Down)==Push)
        {
            cursolPos++;
            //一番下の項目からさらに下に行く場合そのまま
            if (cursolPos > 2)
            {
                cursolPos = 2;
            }
        }
        cursorUIData.y = uiDatas[cursolPos].y;
    }
}
/// <summary>
/// 現在のメニューの状態
/// </summary>
/// <returns></returns>
MenuState Menu::GetMenuState()
{
    return menuState;
}
/// <summary>
/// メニュー画面を開いているかどうか
/// </summary>
/// <returns></returns>
bool Menu::IsMenuOpen()
{
    return isOpenMenu;
}
/// <summary>
/// メニュー画面を開いている時間を所得
/// </summary>
/// <returns></returns>
double Menu::GetOpenMenuTime()
{
    printfDx("MenuTime::%f", openMenuTime);
    return openMenuTime;
}
/// <summary>
/// UIを描画
/// </summary>
void Menu::Draw() const
{
    if (isOpenMenu)
    {
        SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
        DrawGraph(0, 0, backScreen, false);
        SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
        //各UIを描画
        UIDrawer::DrawRotaUI(cursorUIData);
        UIDrawer::DrawRotaUI(uiDatas[continueGame], cursolPos == 0 ? 0 : 1);
        UIDrawer::DrawRotaUI(uiDatas[retry], cursolPos == 1 ? 0 : 1);
        UIDrawer::DrawRotaUI(uiDatas[exitGame], cursolPos == 2 ? 0 : 1);
    }
}