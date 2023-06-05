#include "UserInput.h"
InputState UserInput::aButtonState;
InputState UserInput::bButtonState;
InputState UserInput::keyInputState[KEY_INPUT_KIND_NUM];
StickValueStruct UserInput::stickValue;

UserInput::UserInput()
{
    keyInputCode[KeyInputKind::Up] = PAD_INPUT_UP;
    keyInputCode[KeyInputKind::Down] = PAD_INPUT_DOWN;
    keyInputCode[KeyInputKind::Left] = PAD_INPUT_LEFT;
    keyInputCode[KeyInputKind::Right] = PAD_INPUT_RIGHT;
    keyInputCode[KeyInputKind::Space] = PAD_INPUT_10;
    keyInputCode[KeyInputKind::Escape] = PAD_INPUT_9;
}

void UserInput::Update()
{
    //現在入力されたボタンを所得
    int inputKey = GetJoypadInputState(DX_INPUT_KEY);
    for (int i = 0; i < KEY_INPUT_KIND_NUM; i++)
    {
        ButtonUpdate(inputKey & keyInputCode[i], &keyInputState[i]);
    }
    //ゲームパッドの場合のボタン入力を所得
    XINPUT_STATE input;
    GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input);
    ButtonUpdate(input.Buttons[aButtonNum] != 0, &aButtonState);
    ButtonUpdate(input.Buttons[bButtonNum] != 0, &bButtonState);
    StickUpdate(input);
}


InputState UserInput::GetInputState(KeyInputKind inputKind)
{
    return keyInputState[inputKind];
}

StickValueStruct UserInput::GetStickValue()
{
    return stickValue;
}
/// <summary>
/// ボタンの入力状況を所得
/// </summary>
/// <param name="inputJudge"></param>
/// <param name="_Button"></param>
void UserInput::ButtonUpdate(bool inputJudge, InputState* _Button)
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
/// Stickの入力更新
/// </summary>
/// <param name="_Input"></param>
void UserInput::StickUpdate(XINPUT_STATE _Input)
{
    stickValue.LStickValueX = _Input.ThumbLX;
    stickValue.LStickValueY = _Input.ThumbLY;
    stickValue.RStickValueX = _Input.ThumbRX;
    stickValue.RStickValueY = _Input.ThumbRY;
}