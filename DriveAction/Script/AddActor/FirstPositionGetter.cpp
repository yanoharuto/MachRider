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
/// �����̃t�@�C������ǂݎ���ď����ʒu��n��
/// </summary>
/// <param name="fileName">�z�u���t�@�C���̖��O</param>
/// <param name="kind">�z�u�������I�u�W�F�N�g�̎��</param>
/// <returns>�z�u���̃R���e�i</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(std::string fileName, ObjectInit::InitObjKind kind)
{
    //��������������t�@�C�����珊����
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    //�z�u���ɕϊ�����
    auto placeData = CSVConvertFirstData(csv->GeFileStringData());
    
    //������ނ̃I�u�W�F�N�g�����I�肵�ĕԂ�l�ɂ���
    std::vector<PlacementData> returnData = {};
    for (int i = 0; i < CONTAINER_GET_SIZE(placeData); i++)
    {
        if (placeData[i].objKind == static_cast<int>(kind))
        {
            returnData.push_back(placeData[i]);
        }
    }
    SAFE_DELETE(csv);
    return returnData;
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
        using enum EditArrangementDataKind;
        initData.objKind = STR_TO_I(placeStrData[dataKindNum + static_cast<int>(objectKindNum)]);
        initData.collectNum = STR_TO_I(placeStrData[dataKindNum + static_cast<int>(appearCollectNum)]);
        initData.posX = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(positionX)]);
        initData.posZ = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(positionZ)]);
        initData.dirX = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(directionX)]);
        initData.dirZ = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(directionZ)]);
        dataVec.push_back(initData);
    }
    return dataVec;
}