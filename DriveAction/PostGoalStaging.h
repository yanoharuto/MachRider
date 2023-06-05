#pragma once
#include <string>
#include "Utility.h"
#include "DxLib.h"
#include "UIManager.h"
#include "ResultScore.h"
class NumUI;
class SwitchUI;
class Timer;

/// <summary>
/// �X�R�A�̕\��
/// </summary>
struct ScoreUI
{
    UIData data;
    int score;
    NumUI* ui;
};
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
    bool Update();
    /// <summary>
    /// �X�R�A�̕`��
    /// </summary>
    void Draw();
private:
    /// <summary>
    /// �X�R�A�Ɋւ���UI�̏�����
    /// </summary>
    /// <param name="kind"></param>
    /// <param name="index"></param>
    void InitScoreUI(UIKind kind,int index);
    //�I���A�i�E���X
    int spaceClickCount = 0;
    //�A�i�E���X�̈ړ���
    const float goalMoveX = 10.0f;
    //�X�y�[�X�L�[����������
    const float spaceKeyCoolTime = 1.5f;
    //�I���̃A�i�E���X�̐F
    unsigned int goalMarkerUIColor = GetColor(200, 100, 100);
    //�X�y�[�X�L�[�Ñ�
    SwitchUI* switchUI;
    //�e�X�R�A��\�����邽�߂̔z��
    ScoreUI scoreUI[SCORE_KIND_NUM] = { {},{},{},{} };
    //�S�[�������Ƃ��̏I���A�i�E���X
    //�^�C�}�[
    Timer* timer;
};
