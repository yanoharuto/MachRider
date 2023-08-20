#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "StageSelect.h"
//�X�e�[�W�̃t�@�C���̖��O
std::string StageDataManager::fileAddres = "-1";
//�X�e�[�W�̃f�[�^
std::vector<std::string> StageDataManager::dataVector;
//�S�X�e�[�W�̃f�[�^�������Ă���
const std::string StageDataManager::allStageAddresFile = "data/stageData/stageDataList.csv";

//�X�e�[�W�̉���
int StageDataManager::stageWidth;
//�X�e�[�W�̏c��
int StageDataManager::stageLength;
/// <summary>
/// ��������X�e�[�W�̕ύX
/// </summary>
/// <param name="select">���I��ł���X�e�[�W�������Ă��炤</param>
void StageDataManager::ChangeStageData(StageSelect* const select)
{
    //�󂾂�����ǂݍ���
    if (dataVector.empty())
    {
        InitStageData();
    }
    //�I��ł���X�e�[�W�̃A�h���X��ۑ�
    fileAddres = dataVector[select->GetStageNum()];

    stageWidth = atof(GetStageData(InitStage::width).c_str());
    stageLength = atof(GetStageData(InitStage::length).c_str());
}
/// <summary>
/// �X�e�[�W�̐�
/// </summary>
/// <returns></returns>
int StageDataManager::GetStageTotalNumber()
{
    return dataVector.size();
}

/// <summary>
/// �X�e�[�W�̖��O
/// </summary>
/// <returns></returns>
std::string StageDataManager::GetLoadeStageName()
{
    if (fileAddres == "-1")
    {
        InitStageData();
    }
    return fileAddres;
}
/// <summary>
/// �����ɂ��Ă̕�������o��
/// </summary>
/// <param name="dataKind"></param>
/// <returns></returns>
std::string StageDataManager::GetStageData(StageData dataKind)
{
    //���I�𒆂̃X�e�[�W�̏�������
    auto fileLoader = new CSVFileLoader(GetLoadeStageName());
    auto setStageInitDataVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    //�����̏���Ԃ�
    return setStageInitDataVec[dataKind];
}
/// <summary>
/// �V�ԃX�e�[�W�̃X�R�A�̃{�[�_�[���C����Ԃ�
/// </summary>
/// <returns></returns>
ScoreBorder StageDataManager::GetScoreBorder()
{
    auto fileLoader = new CSVFileLoader(GetStageData(stageScoreFilePass));
    auto scoreInfo = fileLoader->GetLoadStringData();
    ScoreBorder scoreBorder;
    scoreBorder.gold = atoi(scoreInfo[StageScore::goldScore].c_str());
    scoreBorder.silver = atoi(scoreInfo[StageScore::silverScore].c_str());
    scoreBorder.bronze = atoi(scoreInfo[StageScore::bronzeScore].c_str());
    scoreBorder.highScore = atoi(scoreInfo[StageScore::highScore].c_str());
    scoreBorder.second = atoi(scoreInfo[StageScore::secondScore].c_str());
    scoreBorder.third = atoi(scoreInfo[StageScore::thirdScore].c_str());
    return scoreBorder;
}
/// <summary>
/// �V��ł���X�e�[�W�̃n�C�X�R�A���X�V
/// </summary>
/// <param name="hiScore">�V�񂾃X�e�[�W�ŏo���X�R�A</param>
void StageDataManager::SaveHiScore(int hiScore)
{
    ScoreBorder score= GetScoreBorder();
    //��؂蕶��
    std::string colon = ",";
    std::string borderString = std::to_string(score.gold) + colon + std::to_string(score.silver) + colon + std::to_string(score.bronze) + colon;
    std::string updateString;
    //�n�C�X�R�A�̍X�V
    if (score.highScore < hiScore)
    {
        updateString = std::to_string(hiScore) + colon + std::to_string(score.highScore) + colon + std::to_string(score.second) + colon;
    }
    else if (score.second < hiScore)
    {
        updateString = std::to_string(score.highScore) + colon + std::to_string(hiScore) + colon + std::to_string(score.second) + colon;
    }
    else if (score.third < hiScore)
    {
        updateString = std::to_string(score.highScore) + colon + std::to_string(score.second) + colon + std::to_string(hiScore) + colon;
    }
    //�X�R�A�X�V�L��Ȃ珑������
    if(!updateString.empty())
    {
        std::ofstream writing_file;
        std::string filePass = GetStageData(stageScoreFilePass);
        // �t�@�C�����J����
        writing_file.open(filePass, std::ios::out);
        //�X�R�A�̍X�V
        writing_file << borderString + updateString << std::endl;
    }
}
/// <summary>
/// ������
/// </summary>
void StageDataManager::InitStageData()
{
    auto fileLoader = new CSVFileLoader(allStageAddresFile);//�S�X�e�[�W�̃f�[�^���X�g��ǂݎ��
    dataVector = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    fileAddres = dataVector[0];//�Ƃ肠�����擪��n��
}
