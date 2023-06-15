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
    /// �ŏI�I�ȃX�R�A�̕ۑ�
    /// </summary>
    ResultScore(Timer* timer, std::shared_ptr<ObjectObserver> player);
    ~ResultScore() {};
    /// <summary>
    /// �X�R�A�̏���
    /// </summary>
    /// <returns></returns>
    int GetScore(ScoreKind scoreKind) const;
    
private:
    Timer* gameTimer;
    //�_���[�W����̂���I�u�W�F�N�g�ɐG�ꂽ��X�R�A����
    static const int damageObjHitDec = 30;
    //�c�莞�Ԃ̃{�[�i�X
    static const int timeBonus = 10;
    //��x��������Ȃ������ꍇ�̃X�R�A
    static const int noHitScore = 500;
    //�R�C���̓{�[�i�X
    static const int coinBonus = 500;
    //�v���C���[�̏���n���Ă������
    std::weak_ptr<ObjectObserver> playerObserver;
};

