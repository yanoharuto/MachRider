#pragma once
#include <unordered_map>
#include "UIManager.h"
#include "ResultScore.h"
class NumUI;
class SpaceKeyUI;
class Timer;

/// <summary>
/// �X�R�A�̕\��
/// </summary>
struct ScoreUI
{
    UIData scoreKindData;//�X�R�A�̎�ނ�`�悷��
    int score;//�X�R�A��
    bool draw;//�`�悷�邩�ǂ���
    NumUI* numUI;//�X�R�A�ʂ�`�悷��
};
using enum ResultScore::ScoreKind;
/// <summary>
/// �S�[����̉��o������
/// </summary>
class PostGoalStaging final
{
public:
    /// <summary>
    /// �S�[����̉��o������
    /// </summary>
    PostGoalStaging();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PostGoalStaging();
    /// <summary>
    /// �X�R�A�����X�ɓn��
    /// </summary>
    /// <returns></returns>
    void Update();
    /// <summary>
    /// �X�R�A�̕`��
    /// </summary>
    void Draw()const;
    /// <summary>
    /// �������I��������
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess()const;
private:
    /// <summary>
    /// �����ׂ�����������
    /// </summary>
    /// <returns></returns>
    void GetNextProcess();
    /// <summary>
    /// �X�R�A�Ɋւ���UI�̒ǉ�
    /// </summary>
    /// <param name="scoreKind">�ǉ�����UI</param>
    void AddScoreUI(ResultScore::ScoreKind scoreKind);
    //���������ׂčs������
    bool isEndProcess = false;
    //���v�X�R�A��`�悵����
    bool isDrawTotalScore = false;
    //���̉�ʂ̖��邳��Ⴍ����
    const int backScreenBright = 60;
    //�A�i�E���X�̈ړ���
    const float goalMoveX = 10.0f;
    //�\������X�R�A���ϓ����Ă�������
    const float scoreChangeTime = 0.2f;
    //�Q�[���I�����̉��
    int gameEndScreen = -1;
    //�X�y�[�X�L�[�Ñ�
    SpaceKeyUI* switchUI;
    //�e�X�R�A��\�����邽�߂̔z��
    std::unordered_map<ResultScore::ScoreKind,ScoreUI> scoreUI;
    //�����̏������s���Ă��邩
    ResultScore::ScoreKind nowProcess;
    //�^�C�}�[
    Timer* timer;
};
