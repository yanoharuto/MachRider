#pragma once
#include "UIManager.h"
/// <summary>
/// ���j���[�̏��
/// </summary>
enum MenuState
{
    //�Q�[���𑱍s�������ꍇ
    continueGame = 0,
    //��蒼�����������
    retry = 1,
    //�^�C�g���ɖ߂�
    returnTitle=2,
    //�Q�[���I��
    exitGame = 3,
};

using namespace UIInit;
/// <summary>
/// �Q�[�����f�@�\
/// </summary>
class Menu
{
public:
    /// <summary>
    /// �eUI������
    /// </summary>
    Menu();
    /// <summary>
    /// ���j���[���J�������Ԃ�0��
    /// </summary>
    ~Menu();
    /// <summary>
    /// ���ڂ̕ύX�Ȃ�
    /// </summary>
    void Update();
    /// <summary>
    /// ���݂̃��j���[�̏��
    /// </summary>
    /// <returns>�v���C���[����蒼���������Q�[���𑱍s���������Ԃ�</returns>
    MenuState GetMenuState()const;
    /// <summary>
    /// ���j���[��ʂ��J���Ă��邩�ǂ���
    /// </summary>
    /// <returns>�J���Ă�����True</returns>
    bool IsMenuOpen();
    /// <summary>
    /// ���j���[��ʂ��J���Ă��鎞�Ԃ�����
    /// </summary>
    /// <returns></returns>
    static double GetOpenMenuTime();
    /// <summary>
    /// UI��`��
    /// </summary>
    void Draw()const;
private:
    //���j���[��ʂ��J���Ă��鎞�Ԃ̌v��
    double startTime;
    //���j���[�̔w�i
    int backScreen;
    //�w�i�̖��邳
    int backScreenBright = 80;
    //���j���[�̏��
    static MenuState menuState;
    //���j���[��ʂ��J���Ă��邩
    static bool isOpenMenu;
    //���j���[��ʂ��J���Ă���Ԃɗ����Ă��鎞��
    static double openMenuTime;
    //Menu�̊O�g
    UIData cursorUIData;
    //���j���[�̍���
    UIData uiDatas[4];
    //�I��
    int selectUI = 0;
};

