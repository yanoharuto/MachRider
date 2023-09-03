#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "StageSelect.h"
#include "ReusableTimer.h"
#include "ResultScore.h"
#include "ScoreRecordWriter.h"
//�X�e�[�W�̃t�@�C���̖��O
std::string StageDataManager::fileAddres = "-1";
//�X�e�[�W�̃f�[�^
std::vector<std::string> StageDataManager::dataVector;
//�S�X�e�[�W�̃��X�g�̃p�X���������t�@�C���̃p�X
const std::string StageDataManager::allStageFilePath = "data/stageData/stageDataList.csv";
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
    fileAddres = dataVector[select->GetSelectStageNum()];

    stageWidth = atof(GetSelectStageData(InitStage::width).c_str());
    stageLength = atof(GetSelectStageData(InitStage::length).c_str());
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
std::string StageDataManager::GetSelectStageName()
{
    if (fileAddres == "-1")
    {
        InitStageData();
    }
    return fileAddres;
}
/// <summary>
/// �e�X�e�[�W�̃f�[�^������Ă���
/// </summary>
/// <param name="dataKind">�~�����X�e�[�W�̃f�[�^�̎��</param>
/// <returns>�X�e�[�W�̐������Ԃ�c�������A�����ʒu�̓������t�@�C���̃p�X�Ȃǂ��Ԃ��Ă���</returns>
std::string StageDataManager::GetSelectStageData(StageData dataKind)
{
    //���I�𒆂̃X�e�[�W�̏�������
    auto fileLoader = new CSVFileLoader(GetSelectStageName());
    auto setStageInitDataVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    //�����̏���Ԃ�
    return setStageInitDataVec[dataKind];
}
/// <summary>
/// �V�ԃX�e�[�W�̃X�R�A�̃{�[�_�[���C����Ԃ�
/// </summary>
/// <returns>���ݗV��ł���X�e�[�W�̃X�R�A�̐�������Z�߂�����</returns>
ScoreBorder StageDataManager::GetScoreBorder()
{
    auto fileLoader = new CSVFileLoader(GetSelectStageData(stageScoreFilePass));
    //�X�e�[�W��񕶎���R���e�i
    auto scoreStrInfoVec = fileLoader->GetLoadStringData();
    //�X�e�[�W�̃X�R�A�̐�����
    ScoreBorder scoreBorder;
    scoreBorder.gold = atoi(scoreStrInfoVec[StageScore::goldScore].c_str());
    scoreBorder.silver = atoi(scoreStrInfoVec[StageScore::silverScore].c_str());
    scoreBorder.bronze = atoi(scoreStrInfoVec[StageScore::bronzeScore].c_str());
    scoreBorder.highScore = atoi(scoreStrInfoVec[StageScore::highScore].c_str());
    scoreBorder.second = atoi(scoreStrInfoVec[StageScore::secondScore].c_str());
    scoreBorder.third = atoi(scoreStrInfoVec[StageScore::thirdScore].c_str());
    return scoreBorder;
}
/// <summary>
/// �����ʒu�̕�������
/// </summary>
/// <param name="tag">�~�����I�u�W�F�N�g�̏����ʒu���̃^�O</param>
/// <returns>tag�̃I�u�W�F�N�g�������ʒu�����߂�Ƃ��ɕK�v�ȕ�������</returns>
std::vector<std::string> StageDataManager::GetPlaceStrData(Object::ObjectTag tag)
{
    ///���I�����Ă���X�e�[�W�̏����ʒu�̓������t�@�C���̃p�X
    std::string selectStageFirstPlaceFilePath;
    //�e�I�u�W�F�N�g�̏����ʒu�̃t�@�C���܂ł̃p�X������
    switch (tag)
    {
    case Object::player:
        selectStageFirstPlaceFilePath = GetSelectStageData(playerPositionFilePass);
        break;
    case Object::collect:
        selectStageFirstPlaceFilePath = GetSelectStageData(collectFilePass);
        break;
    default:
        selectStageFirstPlaceFilePath = GetSelectStageData(enemyFilePass);
        break;
    }
    //�����������񃊃X�g������Ă���
    CSVFileLoader* csv = new CSVFileLoader(selectStageFirstPlaceFilePath);
    return csv->GetLoadStringData();
}
/// <summary>
/// �Q�[���̐������Ԃ̃^�C�}�[���쐬
/// </summary>
/// <returns>�Q�[���������ԃ^�C�}�[</returns>
ReusableTimer* StageDataManager::CreateGameTimer()
{
    float gameLimitTime = SAFE_STR_TO_F(GetSelectStageData(gameTime));
    return new ReusableTimer(gameLimitTime);
}
/// <summary>
/// �X�R�A�̋L�^�X�V����n��
/// </summary>
/// <returns>�X�R�A�̋L�^�X�V��</returns>
ScoreRecordWriter* StageDataManager::GetScoreRecordWriter()
{
    return new ScoreRecordWriter(GetSelectStageData(stageScoreFilePass),GetScoreBorder());
}
/// <summary>
/// ������
/// </summary>
void StageDataManager::InitStageData()
{
    auto fileLoader = new CSVFileLoader(allStageFilePath);//�S�X�e�[�W�̃f�[�^���X�g��ǂݎ��
    dataVector = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    fileAddres = dataVector[0];//�Ƃ肠�����擪��n��
}
