#pragma once
#include <iostream>
#include <memory>
#include <list>

class MiniMap;
class TimerUI;
class Timer;
class NumUI;
class HitCountObserver;
class EndCountDown;
class Player;
class EnemyGenerator;
class CollectSign;
/// <summary>
/// �V��ł���Ƃ���UI
/// </summary>
class GamePlayUI final
{
public:
    GamePlayUI(Timer* setTimer,std::weak_ptr<HitCountObserver> player);

    ~GamePlayUI();
    /// <summary>
    /// �~�j�}�b�v�̍X�V����W�A�C�e���̖������X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()const;
private:
    //�ŏ��̎��W�A�C�e���̖���
    int firstCoinNum = 0;
    // �v���C���[��������������
    int nowGetCoinNum = 0;
    //�c��̎��W�A�C�e������\�����邩
    bool isDrawGetNum = false;
    //�c��̎��W�A�C�e������\�����鎞��
    float remainingNumDrawTime = 2.0f;
    //�c�������W�A�C�e���̐���\�����鎞�Ԃ��v��
    Timer* remainingNumDrawTimer = nullptr;
    //�Q�[���c�莞�ԃ^�C�}�[
    TimerUI* gameTimerUI;
    //�~�j�}�b�v
    MiniMap* minimapUI;
    //�ŏ��̎��W�A�C�e���̖�����`�悷��N���X
    NumUI* firstNumUI;
    //�Q�b�g�������W�A�C�e���̖�����`��
    NumUI* getNumUI;
    //�c�������W�A�C�e���̐�
    NumUI* remainingNumUI;
    //�c����W�A�C�e���ɂ��Ẵt���[�Y
    UIData remainingFraze;
    //�����̊Ԃɒu���X���b�V��
    UIData slashData;  
    //���W�A�C�e���̃}�[�J�[
    UIData collectSignData;
    //�J�E���g�_�E��
    EndCountDown* countDown;
    //�v���C���[�̈ʒu�Ƃ����W�A�C�e���̏������Ȃǂ������Ă����z
    std::weak_ptr<HitCountObserver> playerObserver;
    //���W�A�C�e���̕����Ƃ��������Ă����
    CollectSign* cSign;
};