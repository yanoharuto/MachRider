#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "StageDataPass.h"
//�X�e�[�W�̉���
int FirstPositionGetter::stageWidth;
//�X�e�[�W�̏c��
int FirstPositionGetter::stageLength;

FirstPositionGetter::FirstPositionGetter()
{
    //���W�A�C�e���ƓG�̈ʒu��ۑ�
    auto fileLoader = new CSVFileLoader(LoadStageData(challengesListFilePass));
    challengeVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    //�X�e�[�W�̉����c����ݒ�
    stageWidth = atoi(LoadStageData(width).c_str());
    stageLength = atoi(LoadStageData(length).c_str());

    using enum FirstPositionDataKind;
    //�e�I�u�W�F�N�g�̏����ʒu
    positionDataPassMap.insert(std::make_pair(playerPosition, LoadStageData(playerPositionFilePass)));
    positionDataPassMap.insert(std::make_pair(rockPosition, LoadStageData(rockFilePass)));
}

FirstPositionGetter::~FirstPositionGetter()
{
}
/// <summary>
/// �����ʒu��n��
/// </summary>
/// <param name="dataKind"></param>
/// <returns></returns>
std::unordered_map<int, std::vector<VECTOR>> FirstPositionGetter::GetFirstPositionLoad(FirstPositionDataKind dataKind)
{
    using enum FirstPositionDataKind;
    std::unordered_map<int, std::vector<VECTOR>> map;
    switch (dataKind)
    {
    case playerPosition:
        CSVConvertPosition(&map,positionDataPassMap[playerPosition]);
        break;
    case rockPosition:
        CSVConvertPosition(&map,positionDataPassMap[rockPosition]);
        break;
    }
    return map;
}
/// <summary>
/// ���W�A�C�e���ƓG�̈ʒu�f�[�^
/// </summary>
/// <returns></returns>
std::vector<ChallengeData> FirstPositionGetter::GetChallengeData()
{
    std::vector<ChallengeData> challengeDataVec;//�������Ɉڂ�
    for (int i = 0; i < challengeVec.size(); i++)
    {
        auto fileLoader = new CSVFileLoader(challengeVec[i]);
        auto passData = fileLoader->GetLoadStringData();
        SAFE_DELETE(fileLoader);
        ChallengeData challengeData;
        CSVConvertPosition(&challengeData.collectPos,passData[collectPositionFilePass]);//���W�A�C�e���̈ʒu
        CSVConvertPosition(&challengeData.enemyPos,passData[enemyPositionFilePass]);//�G�̃A�C�e���̈ʒu

        challengeDataVec.push_back(challengeData);
    }
    return challengeDataVec;
}
/// <summary>
/// CSV�t�@�C�����������map��key�̏ꏊ��ϊ�
/// </summary>
/// <param name="map"></param>
/// <param name="fileName"></param>
void FirstPositionGetter::CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>* map, std::string fileName)
{
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    std::vector<std::string> positionData;
    positionData = csv->GetLoadStringData();
    //��̐��𐔂���
    int lineCount = csv->GetLineCount();

    //�s�̐��𐔂���
    int sideLine = positionData.size() / lineCount;
    //�Z���̐������������ď����ʒu�����X�g��
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < sideLine; j++)
        {
            int num = std::atof(positionData[i * sideLine + j].c_str());
            //-1�ȊO�̐��������͂���Ă�����}�b�v���X�V
            if (num != -1)
            {
                VECTOR pos;
                pos.x = j * stageWidth / lineCount - stageWidth / 2;
                pos.z = i * stageLength / sideLine - stageLength / 2;
                (*map)[num].push_back(pos);
            }
        }
    }
    SAFE_DELETE(csv);
}