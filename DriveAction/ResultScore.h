#pragma once
#include <iostream>
#include <memory>
#define SCORE_KIND_NUM 4
class Timer;
class PlayerObserver;

/// <summary>
/// �ŏI�I�ȃX�R�A�̕ۑ���
/// </summary>
class ResultScore
{
public:
    /// <summary>
/// �ŏI�I�ȃX�R�A�̕ۑ�
/// </summary>
    ResultScore() {};
    ~ResultScore() {};
    enum ScoreKind
    {
        timeBonus = 0,
        collectBonus = 1,
        total = 2
    };
    /// <summary>
    /// �X�R�A����
    /// </summary>
    /// <param name="scoreKind">�ǂ̃X�R�A���~������</param>
    /// <returns></returns>
    int GetScore(ScoreKind scoreKind);
    /// <summary>
    /// �X�R�A�̔{��������
    /// </summary>
    /// <param name="scoreKind"></param>
    /// <returns></returns>
    int GetScoreBonus(ScoreKind scoreKind);
    /// <summary>
    /// �X�R�A���m�肳����
    /// </summary>
    /// <param name="timer"></param>
    /// <param name="player"></param>
    void FixScore(Timer* timer, std::weak_ptr<PlayerObserver> player);
private:
    //�c�莞�Ԃ̃X�R�A
    int timeScore = 0;
    //���W�A�C�e�����W�߂��X�R�A
    int collectScore = 0;
    //�c�莞�Ԃ̃{�[�i�X
    static const int clearTimeBonus;
    //�R�C���̓{�[�i�X
    static const int getCollectBonus;
};

