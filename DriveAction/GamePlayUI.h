#pragma once
#include <iostream>
#include <memory>
#include <list>
#include "Utility.h"
#include "UIManager.h"
class MiniMap;
class TimerUI;
class Timer;
class NumUI;
class ObjectObserver;
class CountDown;
class Player;
class ChallengeFlow;
class CollectSign;
/// <summary>
/// �v���C���[�Ɋ֌W�̂���UI
/// </summary>
class GamePlayUI final
{
public:
    GamePlayUI(Timer* setTimer,ChallengeFlow* challengeFlow, std::shared_ptr<ObjectObserver> player);
    ~GamePlayUI();
    /// <summary>
    /// �~�j�}�b�v�̍X�V�@��R�C���̖������X�V
    /// </summary>
    /// <param name="relatedInfo"></param>
    /// <param name="setCoinPosList"></param>
    void Update(ChallengeFlow* challengeFlow);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()const;
private:
    //�ŏ��̃R�C���̖���
    int firstCoinNum = 0;
    // �v���C���[��������������
    int nowGetCoinNum = 0;
    //�^�C�}�[
    TimerUI* timerUI;
    //�~�j�}�b�v
    MiniMap* minimapUI;
    //�ŏ��̃R�C���̖�����`�悷��N���X
    NumUI* firstNumUI;
    //�Q�b�g�����R�C���̖�����`��
    NumUI* getNumUI;
    //���������UI���
    UIData manualData;
    //�X���b�V��
    UIData slashData;  
    //���W�A�C�e���̃}�[�J�[
    UIData collectSignData;
    //�J�E���g�_�E��
    CountDown* countDown;
    //�v���C���[�̈ʒu�Ƃ��R�C���̏������Ȃǂ������Ă����z
    std::weak_ptr<ObjectObserver> playerObserver;
    CollectSign* cSign;
};