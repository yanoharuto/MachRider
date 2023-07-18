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
    /// <summary>
    /// メニュー画面を開いているかどうか
    /// </summary>
    /// <returns></returns>
    static bool IsMenuOpen();
    /// <summary>
    /// メニュー画面を開いている時間を所得
    /// </summary>
    /// <returns></returns>
    static double GetOpenMenuTime();
    /// <summary>
    /// UIを描画
    /// </summary>
    void Draw()const;
private:
    //メニュー画面を開いている時間の計測
    float startTime;
    //メニューの背景
    int backScreen;
    //背景の明るさ
    int backScreenBright = 80;
    //メニューの状態
    static MenuState menuState;
    //メニュー画面を開いているか
    static bool isOpenMenu;
    //メニュー画面を開いている間に立っている時間
    static double openMenuTime;
    //Menuの外枠
    UIData cursorUIData;
    //メニューの項目
    UIData uiDatas[3];
    //選択
    int cursolPos = 0;
};

