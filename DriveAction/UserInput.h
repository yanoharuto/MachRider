#pragma once
#include "DxLib.h"
namespace Input
{/// <summary>
/// ボタンの入力状況
/// </summary>
    enum InputState
    {
        Free,
        Push,
        Hold,
        Detach
    };
    /// <summary>
    /// ボタンの情報
    /// </summary>
    enum KeyInputKind
    {
        Up = 0,
        Down = 1,
        Left = 2,
        Right = 3,
        Space = 4,
        EscapeKey = 5,
        WKey = 6,
        DKey = 7,
        SKey = 8,
        AKey = 9
    };
#define KEY_INPUT_KIND_NUM 10
#define SHORT_VALUE 12767
}
using namespace Input;
/// <summary>
/// ユーザーが入力した情報
/// </summary>
class UserInput
{
public:
    /// <summary>
/// 入力したキーがどれか分かるように準備
/// </summary>
    UserInput();
    ~UserInput() {};
    /// <summary>
    /// 入力状況更新
    /// </summary>
    void Update();
    /// <summary>
    /// ボタンの入力情報
    /// </summary>
    /// <param name="inputKind"></param>
    /// <returns></returns>
    static InputState GetInputState(KeyInputKind inputKind);
    /// <summary>
    /// ゲームパッドで遊んでいるか
    /// </summary>
    /// <returns>遊んでいたらTrue</returns>
    static bool IsInputPad() { return isInputPad; };
private:
    /// <summary>
    /// キーボードボタンの入力更新
    /// </summary>
    /// <param name="_Input">入力状況</param>    
    /// <param name="_Button">更新したいボタン</param>
    void UpdateButton(bool inputJudge,InputState* _Button);
    /// <summary>
    /// ゲームパッドの入力更新
    /// </summary>
    void UpdateGamePadButton();
    //ボタンの情報
    static InputState keyInputState[KEY_INPUT_KIND_NUM];
    //パッドの情報
    static XINPUT_STATE xInput;
    //Aボタンの割り当て番号
    const int aButtonNum = 12;
    //Bボタンの割り当て番号
    const int bButtonNum = 13;
    //ゲームパッドで入力するか
    static bool isInputPad;
    //対応しているボタンの一覧
    int keyInputCode[KEY_INPUT_KIND_NUM];
};

