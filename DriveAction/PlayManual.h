#pragma once
#include "UIManager.h"
#include "UserInput.h"
/// <summary>
/// 操作説明を描画する
/// </summary>
class PlayManual
{
public:
    PlayManual();
    ~PlayManual();
    /// <summary>
    /// プレイヤーの入力によって操作説明を変える
    /// </summary>
    void Update();
    /// <summary>
    /// 操作説明の描画
    /// </summary>
    void Draw()const;
private:
    //描画する操作方法データ
    UIData playManualData = {};
    //操作方法の下に引く枠
    UIData sheatData = {};
    //描画したい操作方法
    UIKind nowUIKind = manual;
    //各キーの操作方法
    struct ButtonUI
    {
        UIData data = {};
        bool push = false;
    };
    //左ボタン入力UI
    ButtonUI leftBUI;
    //右ボタン入力UI
    ButtonUI rightBUI;
    //下ボタン入力UI
    ButtonUI downBUI;
};