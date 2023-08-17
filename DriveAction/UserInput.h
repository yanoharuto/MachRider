#pragma once
#include "DxLib.h"
namespace Input
{/// <summary>
/// �{�^���̓��͏�
/// </summary>
    enum InputState
    {
        Free,
        Push,
        Hold,
        Detach
    };
    /// <summary>
    /// �{�^���̏��
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
class UserInput
{
public:
    UserInput();
    ~UserInput() {};
    /// <summary>
    /// ���͏󋵍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �{�^���̓��͏��
    /// </summary>
    /// <param name="inputKind"></param>
    /// <returns></returns>
    static InputState GetInputState(KeyInputKind inputKind);
    /// <summary>
    /// �Q�[���p�b�h�ŗV��ł��邩
    /// </summary>
    /// <returns>�V��ł�����True</returns>
    static bool IsInputPad() { return isInputPad; };
private:
    /// <summary>
    /// �{�^���̓��͍X�V
    /// </summary>
    /// <param name="_Input">���͏�</param>
    /// <param name="_Num">�{�^���̊��蓖�Ĕԍ�</param>
    /// <param name="_Button">�X�V�������{�^��</param>
    void ButtonUpdate(bool inputJudge,InputState* _Button);
    /// <summary>
    /// �{�^���̓��͍X�V
    /// </summary>
    void ButtonUpdate();
    //�{�^���̏��
    static InputState keyInputState[KEY_INPUT_KIND_NUM];
    //�p�b�h�̏��
    static XINPUT_STATE xInput;
    //A�{�^���̊��蓖�Ĕԍ�
    const int aButtonNum = 12;
    //B�{�^���̊��蓖�Ĕԍ�
    const int bButtonNum = 13;
    //�Q�[���p�b�h�œ��͂��邩
    static bool isInputPad;
    //�Ή����Ă���{�^���̈ꗗ
    int keyInputCode[KEY_INPUT_KIND_NUM];
};

