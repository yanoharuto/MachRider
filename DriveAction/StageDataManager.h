#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
namespace InitStage
{
    enum StageData
    {
        width = 1,//����
        length = 3,//�c��
        enemyFilePass = 5,//��Q���̈ʒu�̃t�@�C���p�X
        collectFilePass = 7,//���W�A�C�e���ƓG�̈ʒu�̃t�@�C���p�X
        playerPositionFilePass = 9,//�v���C���[�̏����ʒu�̃t�@�C���p�X
        gameTime = 11,//��������
        stageScoreFilePass = 13//�X�e�[�W�̃X�R�A
    };
    //�X�R�A�̊K��
    enum StageScore
    {
        //��Ԗڂɂ����X�R�A
        goldScore,
        //��Ԗڂɂ����X�R�A
        silverScore,
        //�O�Ԗڂɂ����X�R�A
        bronzeScore,
        //�V�񂾒��ōō��X�R�A
        highScore,
        //��Ԗڂɂ����X�R�A
        secondScore,
        //3�Ԗڂɂ����X�R�A
        thirdScore
    };
    /// <summary>
    /// �X�R�A�̊K��
    /// </summary>
    struct  ScoreBorder
    {
        //��Ԗڂɂ����X�R�A
        int gold;
        //��Ԗڂɂ����X�R�A
        int silver;
        //�O�Ԗڂɂ����X�R�A
        int bronze;
        //�V�񂾒��ōō��X�R�A
        int highScore;
        //��Ԗڂɂ����X�R�A
        int second;
        //3�Ԗڂɂ����X�R�A
        int third;
    };
}
using namespace InitStage;
class StageSelect;
/// <summary>
/// �V�ԃX�e�[�W�̃f�[�^�̃p�X��n��
/// </summary>
class StageDataManager
{
public:
    /// <summary>
    /// ��������X�e�[�W�̕ύX
    /// </summary>
    /// <param name="select">���I��ł���X�e�[�W�������Ă��炤</param>
    static void ChangeStageData(StageSelect* const select);
    /// <summary>
    /// �X�e�[�W�̐�
    /// </summary>
    /// <returns></returns>
    static int GetStageTotalNumber();
    /// <summary>
    /// �ǂ̃X�e�[�W��I��ł��邩
    /// </summary>
    /// <returns></returns>
    static std::string GetLoadeStageName();
    /// <summary>
    /// �e�X�e�[�W�̃f�[�^������Ă���
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    static std::string GetStageData(StageData dataKind);
    /// <summary>
    /// �X�e�[�W�̉���
    /// </summary>
    /// <returns></returns>
    static int GetStageWidth() { return stageWidth; };
    /// <summary>
    /// �X�e�[�W�̏c��
    /// </summary>
    /// <returns></returns>
    static int GetStageLength() { return stageLength; };
    /// <summary>
    /// �V�ԃX�e�[�W�̃X�R�A�̃{�[�_�[���C����Ԃ�
    /// </summary>
    /// <returns></returns>
    static ScoreBorder GetScoreBorder();
    /// <summary>
    /// �V�ԃX�e�[�W�̃n�C�X�R�A���X�V
    /// </summary>
    static void SaveHiScore(int score);
private:
    /// <summary>
    /// ������
    /// </summary>
    static void InitStageData();
    //�X�e�[�W�̈ꗗ�I�ȓz
    static const std::string allStageAddresFile;
    //�X�e�[�W�̃f�[�^
    static std::vector<std::string> dataVector;
    //�e�X�e�[�W�̃f�[�^�̃p�X
    static std::string fileAddres;
    //��
    static int stageWidth;
    //����
    static int stageLength;
private:
    StageDataManager();
};