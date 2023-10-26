#include "UserInput.h"
#include "Utility.h"
//���͏��
UserInput::InputState UserInput::keyInputState[KEY_INPUT_KIND_NUM];
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
    //�e���̓L�[�̑Ή��}�N����ݒ�
    keyInputCode[CAST_I(KeyInputKind::Up)] = PAD_INPUT_UP;
    keyInputCode[CAST_I(KeyInputKind::Down)] = PAD_INPUT_DOWN;
    keyInputCode[CAST_I(KeyInputKind::Left)] = PAD_INPUT_LEFT;
    keyInputCode[CAST_I(KeyInputKind::Right)] = PAD_INPUT_RIGHT;
    keyInputCode[CAST_I(KeyInputKind::Space)] = PAD_INPUT_10;
    keyInputCode[CAST_I(KeyInputKind::EscapeKey)] = PAD_INPUT_9;
    keyInputCode[CAST_I(KeyInputKind::WKey)] = PAD_INPUT_8;
    keyInputCode[CAST_I(KeyInputKind::DKey)] = PAD_INPUT_6;
    keyInputCode[CAST_I(KeyInputKind::SKey)] = PAD_INPUT_5;
    keyInputCode[CAST_I(KeyInputKind::AKey)] = PAD_INPUT_4;
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
UserInput::InputState UserInput::GetInputState(KeyInputKind inputKind)
{
    return keyInputState[CAST_I(inputKind)];
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

    UpdateButton(xInput.ThumbLY > LEVER_VALUE - 1, &keyInputState[CAST_I(KeyInputKind::Up)]);
    UpdateButton(xInput.ThumbLY < -LEVER_VALUE, &keyInputState[CAST_I(KeyInputKind::Down)]);
    UpdateButton(xInput.ThumbLX > LEVER_VALUE - 1, &keyInputState[CAST_I(KeyInputKind::Right)]);
    UpdateButton(xInput.ThumbLX < -LEVER_VALUE, &keyInputState[CAST_I(KeyInputKind::Left)]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_B] == 1, &keyInputState[CAST_I(KeyInputKind::Space)]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_BACK] == 1, &keyInputState[CAST_I(KeyInputKind::EscapeKey)]);   
}
