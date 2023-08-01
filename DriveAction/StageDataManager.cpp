#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "StageSelect.h"
//
std::string StageDataManager::fileAddres = "-1";
//
std::vector<std::string> StageDataManager::dataLoader;
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
    if (dataLoader.empty())
    {
        InitStageData();
    }
    //�I��ł���X�e�[�W�̃A�h���X��ۑ�
    fileAddres = dataLoader[select->GetStageNum()];

    stageWidth = atof(GetStageData(InitStage::width).c_str());
    stageLength = atof(GetStageData(InitStage::length).c_str());
}
/// <summary>
/// �X�e�[�W�̐�
/// </summary>
/// <returns></returns>
int StageDataManager::GetStageTotalNumber()
{
    return dataLoader.size();
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
/// �X�R�A�̃{�[�_�[���C����Ԃ�
/// </summary>
/// <returns></returns>
ScoreBorder StageDataManager::GetScoreBorder()
{
    auto fileLoader = new CSVFileLoader(GetStageData(stageScoreFilePass));
    auto scoreInfo = fileLoader->GetLoadStringData();
    ScoreBorder scoreBorder;
    scoreBorder.first = atoi(scoreInfo[StageScore::firstScore].c_str());
    scoreBorder.second = atoi(scoreInfo[StageScore::secondScore].c_str());
    scoreBorder.third = atoi(scoreInfo[StageScore::thirdScore].c_str());
    return scoreBorder;
}
/// <summary>
/// ������
/// </summary>
void StageDataManager::InitStageData()
{
    auto fileLoader = new CSVFileLoader(allStageAddresFile);//�S�X�e�[�W�̃f�[�^���X�g��ǂݎ��
    dataLoader = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    fileAddres = dataLoader[0];//�Ƃ肠�����擪��n��
}
