#include "UserInput.h"
//入力情報
InputState UserInput::keyInputState[KEY_INPUT_KIND_NUM];
//パッドの情報
XINPUT_STATE UserInput::xInput;
//ゲームパッドで入力するか
bool UserInput::isInputPad;
/// <summary>
/// 入力したキーがどれか分かるように準備
/// </summary>
UserInput::UserInput()
{
    //ゲームパッド入力ならTrue
    isInputPad = GetJoypadNum() != 0;
    //各入力キー
    using enum KeyInputKind;
    keyInputCode[Up] = PAD_INPUT_UP;
    keyInputCode[Down] = PAD_INPUT_DOWN;
    keyInputCode[Left] = PAD_INPUT_LEFT;
    keyInputCode[Right] = PAD_INPUT_RIGHT;
    keyInputCode[Space] = PAD_INPUT_10;
    keyInputCode[EscapeKey] = PAD_INPUT_9;
    keyInputCode[WKey] = PAD_INPUT_8;
    keyInputCode[DKey] = PAD_INPUT_6;
    keyInputCode[SKey] = PAD_INPUT_5;
    keyInputCode[AKey] = PAD_INPUT_4;
}
/// <summary>
/// 入力状況更新
/// </summary>
void UserInput::Update()
{
    if (isInputPad)//パッド操作
    {
        UpdateGamePadButton();
    }
    else//キーボード操作
    {
        //現在入力されたボタンを所得
        int inputKey = GetJoypadInputState(DX_INPUT_KEY);
        for (int i = 0; i < KEY_INPUT_KIND_NUM; i++)
        {
            UpdateButton(inputKey & keyInputCode[i], &keyInputState[i]);
        }
    }
    //ゲームパッド入力ならTrue
    isInputPad = GetJoypadNum() != 0;
}

/// <summary>
/// ボタンの入力情報
/// </summary>
/// <param name="inputKind"></param>
/// <returns></returns>
InputState UserInput::GetInputState(KeyInputKind inputKind)
{
    return keyInputState[inputKind];
}
/// <summary>
/// キーボードボタンの入力更新
/// </summary>
/// <param name="_Input">入力状況</param>    
/// <param name="_Button">更新したいボタン</param>
void UserInput::UpdateButton(bool inputJudge, InputState* _Button)
{    
    //ボタンが押されてたら
    if (inputJudge)
    {
        //今押されたか押しっぱか
        switch (*_Button)
        {
        default:
            *_Button = InputState::Free;
            break;
        case InputState::Free:
            *_Button = InputState::Push;
            break;
        case InputState::Push:
            *_Button = InputState::Hold;
            break;
        case InputState::Hold:
            *_Button = InputState::Hold;
            break;
        }
    }
    else
    {
        //押してから離したか、押されていないか
        switch (*_Button)
        {
        default:
            *_Button = InputState::Free;
            break;
        case InputState::Detach:
            *_Button = InputState::Free;
            break;
        case InputState::Push:
            *_Button = InputState::Detach;
            break;
        case InputState::Hold:
            *_Button = InputState::Detach;
            break;
        }
    }
}
/// <summary>
/// ゲームパッドの入力更新
/// </summary>
void UserInput::UpdateGamePadButton()
{
    //ゲームパッドの場合のボタン入力を所得
    GetJoypadXInputState(DX_INPUT_KEY_PAD1, &xInput);

    UpdateButton(xInput.ThumbLY > SHORT_VALUE - 1, &keyInputState[Up]);
    UpdateButton(xInput.ThumbLY < -SHORT_VALUE, &keyInputState[Down]);
    UpdateButton(xInput.ThumbLX > SHORT_VALUE - 1, &keyInputState[Right]);
    UpdateButton(xInput.ThumbLX < -SHORT_VALUE, &keyInputState[Left]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_B] == 1, &keyInputState[Space]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_BACK] == 1, &keyInputState[EscapeKey]);   
}
