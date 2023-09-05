#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "StageDataManager.h"
/// <summary>
/// �����ʒu��n��
/// </summary>
/// <param name="dataKind">�I�u�W�F�N�g�̎�ނɂ���ēǂݍ��ޏ���ύX����</param>
/// <returns>���̃I�u�W�F�N�g�̈ʒu���܂Ƃ߂��R���e�i</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(Object::ObjectTag tag)
{
    return CSVConvertFirstData(StageDataManager::GetPlaceStrData(tag));
}
/// <summary>
/// CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏�������
/// </summary>
/// <param name="fileName">�z�u���܂ł̃p�X</param>
/// <param name="kind">�����������z�u���̎��</param>
/// <returns>CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏��</returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(std::vector<std::string> placeStrData)
{
    //�f�[�^�̎�ނƗ�̑�������I�u�W�F�N�g�̐����v�Z
    int objCount = placeStrData.size() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //�߂�l
    std::vector<PlacementData> dataVec;

    for (int i = 0; i < objCount; i++)
    {
        //�\���̂̏��̎��
        int dataKindNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        //�z�u���������
        PlacementData initData = {};
        initData.objKind = atoi(placeStrData[dataKindNum + EditArrangementDataKind::objectKindNum].c_str());
        initData.collectNum = atoi(placeStrData[dataKindNum + EditArrangementDataKind::missionTurnNum].c_str());
        initData.posX = static_cast<float>(atof(placeStrData[dataKindNum + EditArrangementDataKind::positionX].c_str()));
        initData.posZ = static_cast<float>(atof(placeStrData[dataKindNum + EditArrangementDataKind::positionZ].c_str()));
        initData.dirX = static_cast<float>(atof(placeStrData[dataKindNum + EditArrangementDataKind::directionX].c_str()));
        initData.dirZ = static_cast<float>(atof(placeStrData[dataKindNum + EditArrangementDataKind::directionZ].c_str()));
        dataVec.push_back(initData);
    }
    return dataVec;
}
/// <summary>
/// CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏�������
/// </summary>
/// <param name="fileName">�z�u���܂ł̃p�X</param>
/// <param name="kind">�����������z�u���̎��</param>
/// <returns>CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏��</returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(std::string fileName, ObjectInit::InitObjKind kind)
{
    //�����������񃊃X�g������Ă���
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    auto initStrDataVec = csv->GetLoadStringData();

    //�f�[�^�̎�ނƗ�̑�������I�u�W�F�N�g�̐����o��
    int objCount = csv->GetLineCount() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //�߂�l
    std::vector<PlacementData> dataVec;

    for (int i = 0; i < objCount; i++)
    {
        //�\���̂̏��̎��
        int groupNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        
        //�z�u���������
        PlacementData initData = {};
        initData.objKind = atoi(initStrDataVec[groupNum + EditArrangementDataKind::objectKindNum].c_str());
        //������������񂾂�����
        if (initData.objKind == kind)
        {
            initData.collectNum = atoi(initStrDataVec[groupNum + EditArrangementDataKind::missionTurnNum].c_str());
            initData.posX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionX].c_str()));
            initData.posZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionZ].c_str()));
            initData.dirX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionX].c_str()));
            initData.dirZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionZ].c_str()));
            dataVec.push_back(initData);
        }
    }
    SAFE_DELETE(csv);
    return dataVec;
}
