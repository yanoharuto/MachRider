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
    /// <summary>
    /// スティック入力の値
    /// </summary>
    struct StickValueStruct
    {
        short LStickValueX;
        short LStickValueY;
        short RStickValueX;
        short RStickValueY;
    };
}
using namespace Input;
class UserInput
{
public:
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
    /// スティックの入力状況所得
    /// </summary>
    static StickValueStruct GetStickValue();
private:
    /// <summary>
    /// ボタンの入力更新
    /// </summary>
    /// <param name="_Input">入力状況</param>
    /// <param name="_Num">ボタンの割り当て番号</param>
    /// <param name="_Button">更新したいボタン</param>
    void ButtonUpdate(bool inputJudge,InputState* _Button);
    /// <summary>
    /// Stickの入力更新
    /// </summary>
    /// <param name="_Input"></param>
    void StickUpdate(XINPUT_STATE _Input);
    //ボタンの情報
    static InputState keyInputState[KEY_INPUT_KIND_NUM];
    static StickValueStruct stickValue;
    //Aボタンの割り当て番号
    const int aButtonNum = 12;
    //Bボタンの割り当て番号
    const int bButtonNum = 13;
    int keyInputCode[KEY_INPUT_KIND_NUM];
};

