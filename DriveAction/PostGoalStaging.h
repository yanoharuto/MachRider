#pragma once
#include <unordered_map>
#include "UIManager.h"
#include "ResultScore.h"
class NumUI;
class FlashUI;
class Timer;
class TimerUI;
/// <summary>
/// �X�R�A�̕\��
/// </summary>
struct ScoreUI
{
    UIData scoreKindData = {};//�X�R�A�̎�ނ�`�悷��
    int score = 0;//�X�R�A��
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
    PostGoalStaging(Timer* timer, std::weak_ptr<HitCountObserver> player);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PostGoalStaging();
    /// <summary>
    /// �X�R�A�̐��������X�ɏo���Ă�������
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
    /// �����ׂ�����
    /// </summary>
    /// <returns></returns>
    void UpdateNowProcess();
    /// <summary>
    /// �X�R�A�Ɋւ���UI������
    /// </summary>
    /// <param name="kind"></param>
    /// <returns></returns>
    ScoreUI GetScoreUI(UIKind kind);
    //���������ׂčs������
    bool isEndProcess = false;
    //���v�X�R�A��`�悵����
    bool isEndUpdateScore = false;
    //�N���A�^�C��
    float clearTime = 0;
    //���̉�ʂ̖��邳��Ⴍ����
    const int backScreenBright = 60;
    //�A�i�E���X�̈ړ���
    const float goalMoveX = 10.0f;
    //�\������X�R�A���ϓ����Ă�������
    const float scoreLarpTime = 3.0f;
    //�`�悷��N���A�^�C���@�X�R�A�Ɋ��Z���Ă���
    float drawClearTime = 0;
    //�`�悷����W�A�C�e���̐�
    int drawCollectIconNum = 0;
    //�Q�b�g�����A�C�e���̐�
    int getCollectNum = 0;
    //�Q�[���I�����̉��
    int gameEndScreen = -1;
    //�X�y�[�X�L�[�Ñ�
    FlashUI* switchUI;
    //���v�X�R�A
    ScoreUI totalScoreUI;
    //���W�A�C�e�����W�߂ē���X�R�A
    ScoreUI collectScoreUI;
    //�c�莞�ԃ{�[�i�X�X�R�A
    ScoreUI timeScoreUI;

    //���W�A�C�e���̃f�[�^
    UIData collectData;
    //�N���A�^�C����\������p
    NumUI* clearTimeUI;
    //���v�X�R�A�\��
    NumUI* totalScoreNumUI;
    //�����̏������s���Ă��邩
    ResultScore::ScoreKind nowProcess;
    //�^�C�}�[
    Timer* larpTimer;
    //�X�R�A�̕ۑ�
    ResultScore* resultScore;
    //�X�y�[�X�L�[�Ñ�UI
    FlashUI* pressSpaceKeyUI;
};
