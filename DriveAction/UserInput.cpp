#include "UserInput.h"
//���͏��
InputState UserInput::keyInputState[KEY_INPUT_KIND_NUM];
//�p�b�h�̏��
XINPUT_STATE UserInput::xInput;
bool UserInput::isInputPad;
UserInput::UserInput()
{
    //�Q�[���p�b�h���͂Ȃ�True
    isInputPad = GetJoypadNum() != 0;
    keyInputCode[KeyInputKind::Up] = PAD_INPUT_UP;
    keyInputCode[KeyInputKind::Down] = PAD_INPUT_DOWN;
    keyInputCode[KeyInputKind::Left] = PAD_INPUT_LEFT;
    keyInputCode[KeyInputKind::Right] = PAD_INPUT_RIGHT;
    keyInputCode[KeyInputKind::Space] = PAD_INPUT_10;
    keyInputCode[KeyInputKind::EscapeKey] = PAD_INPUT_9;
    keyInputCode[KeyInputKind::WKey] = PAD_INPUT_8;
    keyInputCode[KeyInputKind::DKey] = PAD_INPUT_6;
    keyInputCode[KeyInputKind::SKey] = PAD_INPUT_5;
    keyInputCode[KeyInputKind::AKey] = PAD_INPUT_4;
}
/// <summary>
/// ���͏󋵍X�V
/// </summary>
void UserInput::Update()
{
    if (isInputPad)
    {
        ButtonUpdate();
    }
    else//�p�b�h����
    {
        //���ݓ��͂��ꂽ�{�^��������
        int inputKey = GetJoypadInputState(DX_INPUT_KEY);
        for (int i = 0; i < KEY_INPUT_KIND_NUM; i++)
        {
            ButtonUpdate(inputKey & keyInputCode[i], &keyInputState[i]);
        }
    }
    //�Q�[���p�b�h���͂Ȃ�True
    isInputPad = GetJoypadNum() != 0;
}

/// <summary>
/// �{�^���̓��͏��
/// </summary>
/// <param name="inputKind"></param>
/// <returns></returns>
InputState UserInput::GetInputState(KeyInputKind inputKind)
{
    return keyInputState[inputKind];
}

/// <summary>
/// �{�^���̓��͏󋵂�����
/// </summary>
/// <param name="inputJudge"></param>
/// <param name="_Button"></param>
void UserInput::ButtonUpdate(bool inputJudge, InputState* _Button)
{    
    //�{�^����������Ă���
    if (inputJudge)
    {
        //�������ꂽ���������ς�
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
        //�����Ă��痣�������A������Ă��Ȃ���
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
/// �{�^���̓��͍X�V
/// </summary>
void UserInput::ButtonUpdate()
{
    //�Q�[���p�b�h�̏ꍇ�̃{�^�����͂�����
    GetJoypadXInputState(DX_INPUT_KEY_PAD1, &xInput);

    ButtonUpdate(xInput.ThumbLY > SHORT_VALUE - 1, &keyInputState[Up]);
    ButtonUpdate(xInput.ThumbLY < -SHORT_VALUE, &keyInputState[Down]);
    ButtonUpdate(xInput.ThumbLX > SHORT_VALUE - 1, &keyInputState[Right]);
    ButtonUpdate(xInput.ThumbLX < -SHORT_VALUE, &keyInputState[Left]);
    ButtonUpdate(xInput.Buttons[XINPUT_BUTTON_B] == 1, &keyInputState[Space]);
    ButtonUpdate(xInput.Buttons[XINPUT_BUTTON_BACK] == 1, &keyInputState[EscapeKey]);   
}
