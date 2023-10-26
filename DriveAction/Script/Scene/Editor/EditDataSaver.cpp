#include <iostream>
#include <cassert>
#include <vector>
#include "EditDataSaver.h"
#include "Utility.h"
#include "writer.h"
#include "StageDataEditor.h"


EditDataSaver::EditDataSaver()
{
}
/// <summary>
/// �ҏW�f�[�^��ۑ�����
/// </summary>
EditDataSaver::~EditDataSaver()
{
    //�v���C���[�̕ҏW�f�[�^��ۑ�����
    SaveEditDataForCSV(playerPlaceData,playerSaveFileName);
    SaveEditDataForJSON(playerPlaceData,playerSaveFileName);
    //���W�A�C�e���̕ҏW�f�[�^��ۑ�����
    SaveEditDataForCSV(collectPlaceData, collectSaveFileName);
    SaveEditDataForJSON(collectPlaceData, collectSaveFileName);
    //�G�̕ҏW�f�[�^��ۑ�����
    SaveEditDataForCSV(enemyPlaceData, enemySaveFileName);
    SaveEditDataForJSON(enemyPlaceData, enemySaveFileName);
}
/// <summary>
/// �ҏW��������ۑ�����
/// </summary>
/// <param name="editData">�ҏW��������Z�߂�Vector</param>
/// <param name="editObjKind">�ҏW�������</param>
void EditDataSaver::SaveEditData(std::weak_ptr<StageDataEditor> editor)
{
    std::string saveFileName;
    //�ۑ����������
    auto placeVector = editor.lock()->GetPlacementDataVector();
    //��ނ��Ƃɕۑ����������𕪂���
    switch (editor.lock()->GetEditObjectKind())
    {
    case InitObjKind::player:
        playerPlaceData.insert(playerPlaceData.end(), placeVector.begin(), placeVector.end());
        break;
    case InitObjKind::collect:
        collectPlaceData.insert(collectPlaceData.end(), placeVector.begin(), placeVector.end());
        break;
    default:
        enemyPlaceData.insert(enemyPlaceData.end(), placeVector.begin(),placeVector.end());
        break;
    }
}

/// <summary>
/// �ҏW��������ۑ�����
/// </summary>
/// <param name="editData">�ҏW�������</param>
/// <param name="saveFileName">�ۑ�����t�@�C��</param>
void EditDataSaver::SaveEditDataForCSV(std::vector<PlacementData> editData, std::string saveFileName) const
{
    //�z�u�������W�A�C�e����ۑ�
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        std::ofstream writing_file;
        auto data = editData[i];
        // �t�@�C�����J����
        writing_file.open(editFilePath + saveFileName + Utility::CSV_FILE, std::ios::app);
        //��؂蕶��
        std::string colon = ",";
        //�I�u�W�F�N�g�̎�ނ�
        writing_file << std::to_string(data.objKind) + colon << std::endl;
        //���Ԗڂ̎��W�A�C�e���̎���
        writing_file << std::to_string(data.collectNum) + colon << std::endl;
        //�ʒu
        writing_file << std::to_string(data.posX) + colon << std::endl;
        writing_file << std::to_string(data.posZ) + colon << std::endl;
        //����
        writing_file << std::to_string(data.dirX) + colon << std::endl;
        writing_file << std::to_string(data.dirZ) + colon << std::endl;
        writing_file.close();
    }
}
/// <summary>
/// �����̕ҏW����Json�ɕۑ��ł���悤�ɂ���
/// </summary>
/// <param name="editData">�ҏW���</param>
/// <param name="allocator">�ҏW�̂��߂ɕK�v��allocator</param>
/// <returns>Json�ɕۑ��ł���悤�ɂ�������</returns>
rapidjson::Value EditDataSaver::GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator) const
{
    //�ҏW���e�������o�ɓo�^
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember("objNum", editData.objKind, allocator);
    objValue.AddMember("collectNum", editData.collectNum, allocator);
    objValue.AddMember("x", editData.posX, allocator);
    objValue.AddMember("z", editData.posZ, allocator);
    objValue.AddMember("dirX", editData.dirX, allocator);
    objValue.AddMember("dirZ", editData.dirZ, allocator);
    return objValue;
}
/// <summary>
/// Json�`���ŕۑ�����
/// </summary>
/// <param name="editData">�ҏW���������Z��</param>
/// <param name="saveFileName">�ۑ���̃t�@�C���̖��O</param>
void EditDataSaver::SaveEditDataForJSON(std::vector<PlacementData> editData, std::string saveFileName)const
{
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    //�z��ɂ��ċl�ߍ���
    rapidjson::Value myArray(rapidjson::kArrayType);
    //�z�u�������W�A�C�e����ۑ�
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        myArray.PushBack(GetEditPlaceData(editData[i], allocator),allocator);
    }
    //�ҏW���e��saveFileName�̃t�@�C���ɏ�������
    jsonDoc.AddMember("arrangeData", myArray, allocator);
    //�t�@�C���̒��g��S����������Ԃŏ�������
    saveFileName = editFilePath + saveFileName + Utility::JSON_FILE;
    std::ofstream ofs(saveFileName);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    jsonDoc.Accept(writer);
}