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
    enum KeyInputKind
    {
        Up = 0,
        Down = 1,
        Left = 2,
        Right = 3,
        Space = 4,
        Escape = 5
    };
#define KEY_INPUT_KIND_NUM 6
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
    /// �X�e�B�b�N�̓��͏󋵏���
    /// </summary>
    static StickValueStruct GetStickValue();
private:
    /// <summary>
    /// �{�^���̓��͍X�V
    /// </summary>
    /// <param name="_Input">���͏�</param>
    /// <param name="_Num">�{�^���̊��蓖�Ĕԍ�</param>
    /// <param name="_Button">�X�V�������{�^��</param>
    void ButtonUpdate(bool inputJudge,InputState* _Button);
    /// <summary>
    /// Stick�̓��͍X�V
    /// </summary>
    /// <param name="_Input"></param>
    void StickUpdate(XINPUT_STATE _Input);

    static InputState aButtonState;
    static InputState bButtonState;
    static InputState keyInputState[KEY_INPUT_KIND_NUM];
    static StickValueStruct stickValue;
    //A�{�^���̊��蓖�Ĕԍ�
    const int aButtonNum = 12;
    //B�{�^���̊��蓖�Ĕԍ�
    const int bButtonNum = 13;
    int keyInputCode[KEY_INPUT_KIND_NUM];
};
