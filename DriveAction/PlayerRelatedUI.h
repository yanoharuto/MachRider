#pragma once
#include <list>
#include "Utility.h"
#include "UIManager.h"
class CoinManager;
//���W�A�C�e���̃}�b�v
class MiniMap;
//�c�莞�Ԃ�\�����Ă����
class TimerUI;
//�Q�[���̎c�莞�ԂƂ��̃^�C�}�[
class Timer;
//�����Ɋւ���UI
class NumUI;
//�����X�V���Ă����
class ObjectSubject;
//Subject�����Ă���
class ObjectObserver;
//�����Ă��̃}�l�[�W���[
class RacerManager;
//�J�E���g�_�E��
class CountDown;
/// <summary>
/// �v���C���[�Ɋ֌W�̂���UI
/// </summary>
class PlayerRelatedUI final
{
public:
    PlayerRelatedUI(Timer* setTimer,int setFirstCoinNum,RacerManager* manager);
    ~PlayerRelatedUI();
    /// <summary>
    /// �~�j�}�b�v�̍X�V�@��R�C���̖������X�V
    /// </summary>
    /// <param name="relatedInfo"></param>
    /// <param name="setCoinPosList"></param>
    void Update(CoinManager* coinManager);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
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
    UIData slashHandle;  
  
    //�t�H���g�̃T�C�Y
    const int fontSize = 1;
    //�v���C���[�̈ʒu�Ƃ��R�C���̏������Ȃǂ������Ă����z
    ObjectObserver* playerObserver;
};