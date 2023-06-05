#pragma once
#include "UIManager.h"

enum MenuState
{
    //ゲームを続行させた場合
    continueGame = 0,
    //やり直しをした状態
    retry = 1,
    //ゲーム終了
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
    /// 項目の変更など
    /// </summary>
    /// <returns></returns>
    void Update();
    /// <summary>
    /// 現在のメニューの状態
    /// </summary>
    /// <returns></returns>
    MenuState GetMenuState();
    static bool IsMenuOpen();
    static double GetOpenMenuTime();
    /// <summary>
    /// UIを描画
    /// </summary>
    void Draw();
private:
    /// <summary>
    /// 引数のUIを描画
    /// </summary>
    /// <param name="data"></param>
    /// <param name="handleNum"></param>
    void DrawUI(UIData data,int handleNum);
    StopWatch* stopWatch;
    //メニューの状態
    static MenuState menuState;
    //メニュー画面を開いているか
    static bool openMenu;

    static double openMenuTime;
    //Menuの外枠
    UIData cursorUIData;

    UIData uiDatas[3];
    //選択
    int cursolPos = 0;
};

