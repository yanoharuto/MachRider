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
        initData.objKind = SAFE_STR_TO_I(placeStrData[dataKindNum + objectKindNum]);
        initData.collectNum = SAFE_STR_TO_I(placeStrData[dataKindNum + missionTurnNum]);
        initData.posX = SAFE_STR_TO_F(placeStrData[dataKindNum + positionX]);
        initData.posZ = SAFE_STR_TO_F(placeStrData[dataKindNum + positionZ]);
        initData.dirX = SAFE_STR_TO_F(placeStrData[dataKindNum + directionX]);
        initData.dirZ = SAFE_STR_TO_F(placeStrData[dataKindNum + directionZ]);
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
        initData.objKind = SAFE_STR_TO_I(initStrDataVec[groupNum + objectKindNum]);
        //������������񂾂�����
        if (initData.objKind == kind)
        {
            initData.collectNum = SAFE_STR_TO_I(initStrDataVec[groupNum + missionTurnNum]);
            initData.posX = SAFE_STR_TO_F(initStrDataVec[groupNum + positionX]);
            initData.posZ = SAFE_STR_TO_F(initStrDataVec[groupNum + positionZ]);
            initData.dirX = SAFE_STR_TO_F(initStrDataVec[groupNum + directionX]);
            initData.dirZ = SAFE_STR_TO_F(initStrDataVec[groupNum + directionZ]);
            dataVec.push_back(initData);
        }
    }
    SAFE_DELETE(csv);
    return dataVec;
}
