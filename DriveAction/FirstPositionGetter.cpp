#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// �����ʒu��n��
/// </summary>
/// <param name="dataKind">�I�u�W�F�N�g�̎�ނɂ���ēǂݍ��ޏ���ύX����</param>
/// <returns>���̃I�u�W�F�N�g�̈ʒu</returns>
std::vector<EditArrangementData> FirstPositionGetter::GetInitData(Object::ObjectTag tag)
{
    std::vector<EditArrangementData> initData;
    using enum Object::ObjectTag;

    switch (tag)
    {
    case player:
        initData = CSVConvertFirstData(StageDataManager::GetStageData(playerPositionFilePass));
        break;
    case damageObject:
        initData = CSVConvertFirstData(StageDataManager::GetStageData(enemyFilePass));
        break;
    case collect:
        initData = CSVConvertFirstData(StageDataManager::GetStageData(collectFilePass));
        break;
    }
    return initData;
}
/// <summary>
/// CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏�������
/// </summary>
/// <param name="fileName"></param>
std::vector<EditArrangementData> FirstPositionGetter::CSVConvertFirstData(std::string fileName)
{
    //�����������񃊃X�g������Ă���
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    auto initStrDataVec = csv->GetLoadStringData();
    
    //�f�[�^�̎�ނƗ�̑�������I�u�W�F�N�g�̐����v�Z
    int objCount = csv->GetLineCount() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //�߂�l
    std::vector<EditArrangementData> dataVec;
    
    for (int i = 0; i < objCount; i++)
    {
        int groupNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        //�z�u���������
        EditArrangementData initData = {};
        initData.objKind= atoi(initStrDataVec[groupNum + EditArrangementDataKind::objectKindNum].c_str());
        initData.missionNum = atoi(initStrDataVec[groupNum + EditArrangementDataKind::missionTurnNum].c_str());
        initData.posX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionX].c_str()));
        initData.posZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionZ].c_str()));
        initData.dirX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionX].c_str()));
        initData.dirZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionZ].c_str()));
        dataVec.push_back(initData);
    }
    SAFE_DELETE(csv);

    return dataVec;
}