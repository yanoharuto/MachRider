#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
namespace InitStage
{
    enum StageData
    {
        width = 1,
        length = 3,
        rockFilePass = 5,
        challengesListFilePass = 7,
        playerPositionFilePass = 9,
        gameTime = 11,
        stageScoreFilePass = 13
    };
    enum StageScore
    {
        firstScore,
        secondScore,
        thirdScore
    };
    enum Challenge
    {
        collectPositionFilePass = 1,
        enemyPositionFilePass = 3
    };
    /// <summary>
    /// �v���C���[�����Ȃ����e�@
    /// �W�߂�A�C�e���̈ʒu�ƓG�̈ʒu��ۑ����Ă���
    /// </summary>
    struct ChallengeData
    {
        std::unordered_map<int, std::vector<VECTOR>> collectPos;
        std::unordered_map<int, std::vector<VECTOR>> enemyPos;
    };
    enum class FirstPositionDataKind
    {
        playerPosition,
        rockPosition,
    };
}
using namespace InitStage;
/// <summary>
/// �V�ԃX�e�[�W�̃f�[�^�̃p�X��n��
/// </summary>
class StageDataPass
{
public:
    StageDataPass();
    virtual ~StageDataPass();
 
protected:
    /// <summary>
    /// �ǂ̃X�e�[�W��I��ł��邩
    /// </summary>
    /// <returns></returns>
    std::string GetLoadeStageName()const;
    /// <summary>
    /// �e�X�e�[�W�̃f�[�^������Ă���
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    std::string LoadStageData(StageData dataKind)const;
    //�X�e�[�W�̈ꗗ�I�ȓz
    const std::string allStageAddresFile = "data/stageData/stageDataList.csv";
    //�X�e�[�W�̃p�X��ǂݎ��
    std::vector<std::string> dataLoader;
    //�e�X�e�[�W�̃f�[�^�̃p�X
    static std::string fileAddres;
};