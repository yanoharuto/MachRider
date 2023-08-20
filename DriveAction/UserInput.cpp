#include "UserInput.h"
//���͏��
InputState UserInput::keyInputState[KEY_INPUT_KIND_NUM];
//�p�b�h�̏��
XINPUT_STATE UserInput::xInput;
//�Q�[���p�b�h�œ��͂��邩
bool UserInput::isInputPad;
/// <summary>
/// ���͂����L�[���ǂꂩ������悤�ɏ���
/// </summary>
UserInput::UserInput()
{
    //�Q�[���p�b�h���͂Ȃ�True
    isInputPad = GetJoypadNum() != 0;
    //�e���̓L�[
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
/// ���͏󋵍X�V
/// </summary>
void UserInput::Update()
{
    if (isInputPad)//�p�b�h����
    {
        UpdateGamePadButton();
    }
    else//�L�[�{�[�h����
    {
        //���ݓ��͂��ꂽ�{�^��������
        int inputKey = GetJoypadInputState(DX_INPUT_KEY);
        for (int i = 0; i < KEY_INPUT_KIND_NUM; i++)
        {
            UpdateButton(inputKey & keyInputCode[i], &keyInputState[i]);
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
/// �L�[�{�[�h�{�^���̓��͍X�V
/// </summary>
/// <param name="_Input">���͏�</param>    
/// <param name="_Button">�X�V�������{�^��</param>
void UserInput::UpdateButton(bool inputJudge, InputState* _Button)
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
/// �Q�[���p�b�h�̓��͍X�V
/// </summary>
void UserInput::UpdateGamePadButton()
{
    //�Q�[���p�b�h�̏ꍇ�̃{�^�����͂�����
    GetJoypadXInputState(DX_INPUT_KEY_PAD1, &xInput);

    UpdateButton(xInput.ThumbLY > SHORT_VALUE - 1, &keyInputState[Up]);
    UpdateButton(xInput.ThumbLY < -SHORT_VALUE, &keyInputState[Down]);
    UpdateButton(xInput.ThumbLX > SHORT_VALUE - 1, &keyInputState[Right]);
    UpdateButton(xInput.ThumbLX < -SHORT_VALUE, &keyInputState[Left]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_B] == 1, &keyInputState[Space]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_BACK] == 1, &keyInputState[EscapeKey]);   
}
