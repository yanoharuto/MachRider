#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
#include "Object.h"
namespace InitStage
{
    /// <summary>
    /// �X�e�[�W���Ƃɐݒ肵�Ă���f�[�^
    /// </summary>
    enum StageData
    {
        //����
        width = 1,
        //�c��
        length = 3,
        //��Q���̈ʒu�̃t�@�C���p�X
        enemyFilePass = 5,
        //���W�A�C�e���ƓG�̈ʒu�̃t�@�C���p�X
        collectFilePass = 7,
        //�v���C���[�̏����ʒu�̃t�@�C���p�X
        playerPositionFilePass = 9,
        //��������
        gameTime = 11,
        //�X�e�[�W�̃X�R�A
        stageScoreFilePass = 13
    };
    /// <summary>
    /// �X�R�A�̐�����
    /// </summary>
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
class ResultScore;
class ReusableTimer;
class ScoreRecordWriter;
/// <summary>
/// �V�ԃX�e�[�W�̃f�[�^��n��
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
    /// �X�e�[�W�̑���
    /// </summary>
    /// <returns>�X�e�[�W�̑������Ԃ��Ă���</returns>
    static int GetStageTotalNumber();
    /// <summary>
    /// �V�ԃX�e�[�W�̃X�R�A�̃{�[�_�[���C����Ԃ�
    /// </summary>
    /// <returns>���ݗV��ł���X�e�[�W�̃X�R�A�̐�������Z�߂�����</returns>
    static ScoreBorder GetScoreBorder();
    /// <summary>
    /// �����ʒu�̕�������
    /// </summary>
    /// <param name="tag">�~�����I�u�W�F�N�g�̏����ʒu���̃^�O</param>
    /// <returns>tag�̃I�u�W�F�N�g�������ʒu�����߂�Ƃ��ɕK�v�ȕ�������</returns>
    static std::vector<std::string> GetPlaceStrData(Object::ObjectTag tag);
    /// <summary>
    /// �Q�[���̐������Ԃ̃^�C�}�[���쐬
    /// </summary>
    /// <returns>�Q�[���������ԃ^�C�}�[</returns>
    static ReusableTimer* CreateGameTimer();
    /// <summary>
    /// �X�R�A�̋L�^�X�V����n��
    /// </summary>
    /// <returns>�X�R�A�̋L�^�X�V��</returns>
    static ScoreRecordWriter* GetScoreRecordWriter();
private:
    /// <summary>
    /// �X�e�[�W�̏��Ǘ���
    /// </summary>
    StageDataManager();
    /// <summary>
    /// �e�X�e�[�W�̃f�[�^������Ă���
    /// </summary>
    /// <param name="dataKind">�~�����X�e�[�W�̃f�[�^�̎��</param>
    /// <returns>�X�e�[�W�̐������Ԃ�c�������A�����ʒu�̓������t�@�C���̃p�X�Ȃǂ��Ԃ��Ă���</returns>
    static std::string GetSelectStageData(StageData dataKind);
    /// <summary>
    /// �ǂ̃X�e�[�W��I��ł��邩
    /// </summary>
    /// <returns>�X�e�[�W�̖��O�������Ԃ�</returns>
    static std::string GetSelectStageName();
    /// <summary>
    /// ������
    /// </summary>
    static void InitStageData();
    //�S�X�e�[�W�̃��X�g�̃p�X���������t�@�C���̃p�X
    static const std::string allStageFilePath;
    //�X�e�[�W�̃f�[�^
    static std::vector<std::string> dataVector;
    //�e�X�e�[�W�̃f�[�^�̃p�X
    static std::string fileAddres;
    //��
    static int stageWidth;
    //����
    static int stageLength;
};