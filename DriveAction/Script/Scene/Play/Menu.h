#pragma once
#include "UIManager.h"
/// <summary>
/// メニューの状態
/// </summary>
enum MenuState
{
    //ゲームを続行させた場合
    continueGame = 0,
    //やり直しをした状態
    retry = 1,
    //タイトルに戻る
    returnTitle=2,
    //ゲーム終了
    exitGame = 3,
};

using namespace UIInit;
/// <summary>
/// ゲーム中断機能
/// </summary>
class Menu
{
public:
    /// <summary>
    /// 各UI初期化
    /// </summary>
    Menu();
    /// <summary>
    /// メニューを開いた時間を0に
    /// </summary>
    ~Menu();
    /// <summary>
    /// 項目の変更など
    /// </summary>
    void Update();
    /// <summary>
    /// 現在のメニューの状態
    /// </summary>
    /// <returns>プレイヤーがやり直したいかゲームを続行したいか返す</returns>
    MenuState GetMenuState()const;
    /// <summary>
    /// メニュー画面を開いているかどうか
    /// </summary>
    /// <returns>開いていたらTrue</returns>
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
    double startTime;
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
    UIData uiDatas[4];
    //選択
    int selectUI = 0;
};

