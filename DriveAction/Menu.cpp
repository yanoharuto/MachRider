#include "Menu.h"
#include "UserInput.h"
#include "DxLib.h"
#include "Utility.h"
#include "StopWatch.h"
//メニューの状態
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
    //Escapeを押したら
    if (UserInput::GetInputState(Input::Escape) == Push)
    {
        //メニュー画面を開いたり閉じたり
        openMenu = !openMenu;
        cursolPos = 0;
        if (openMenu)
        {
            //開いている時間を計測開始
            stopWatch->Run();
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
        openMenu = !(menuState == continueGame);
    }
    //開いているときに上下に押すと項目を変更
    if (openMenu)
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
/// UIを描画
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
/// 引数のUIを描画
/// </summary>
/// <param name="data"></param>
/// <param name="handleNum"></param>
void Menu::DrawUI(UIData data, int handleNum)
{
    DrawRotaGraph(data.x, data.y, data.size, 0, data.dataHandle[handleNum], true, false);
}