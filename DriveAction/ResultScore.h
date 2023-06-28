#pragma once
#include <iostream>
#include <memory>
#define SCORE_KIND_NUM 4
class Timer;
class ObjectObserver;

/// <summary>
/// �ŏI�I�ȃX�R�A�̕ۑ���
/// </summary>
class ResultScore
{
public:
    enum ScoreKind
    {
        time = 0,
        collect = 1,
        hit = 2,
        total = 3
    };
    /// <summary>
    /// �X�R�A����
    /// </summary>
    /// <param name="scoreKind">�ǂ̃X�R�A���~������</param>
    /// <returns></returns>
    static int GetScore(ScoreKind scoreKind);
    /// <summary>
    /// �X�R�A���m�肳����
    /// </summary>
    /// <param name="timer"></param>
    /// <param name="player"></param>
    static void FixScore(Timer* timer, std::weak_ptr<ObjectObserver> player);
private:

    /// <summary>
    /// �ŏI�I�ȃX�R�A�̕ۑ�
    /// </summary>
    ResultScore() {};
    ~ResultScore() {};
    static int timeScore;
    static int collectScore;
    static bool noHit;
    //�_���[�W����̂���I�u�W�F�N�g�ɐG�ꂽ��X�R�A����
    static const int damageObjHitDec = 30;
    //�c�莞�Ԃ̃{�[�i�X
    static const int timeBonus = 10;
    //��x��������Ȃ������ꍇ�̃X�R�A
    static const int noHitScore = 500;
    //�R�C���̓{�[�i�X
    static const int coinBonus = 500;
    
};

