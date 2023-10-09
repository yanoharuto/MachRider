#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include "EditDataSaver.h"
#include "Utility.h"
#include "writer.h"
/// <summary>
/// �ҏW��������ۑ�����
/// </summary>
/// <param name="editData">�ҏW��������Z�߂�Vector</param>
/// <param name="editObjKind">�ҏW�������</param>
void EditDataSaver::SaveEditData(std::vector<PlacementData> editData, InitObjKind editObjKind)const
{
    std::string saveFileName;
    using enum InitObjKind;
    //��ނ��Ƃɕۑ����ς���
    switch (editObjKind)
    {
    case player:
        saveFileName = playerSaveFileName;
        break;
    case collect:
        saveFileName = collectSaveFileName;
        break;
    default:
        saveFileName = enemySaveFileName;
        break;
    }
    //�z�u�������W�A�C�e����ۑ�
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        SaveEditData(editData[i], saveFileName);
        SaveEditDataForJson(editData[i], saveFileName);
    }
}

/// <summary>
/// �ҏW��������ۑ�����
/// </summary>
/// <param name="editData">�ҏW�������</param>
/// <param name="saveFileName">�ۑ�����t�@�C��</param>
void EditDataSaver::SaveEditData(PlacementData editData, std::string saveFileName) const
{
    std::ofstream writing_file;
    // �t�@�C�����J����
    writing_file.open(saveFileName + csvFIle, std::ios::app);
    //��؂蕶��
    std::string colon = ",";
    //�I�u�W�F�N�g�̎�ނ�
    writing_file << std::to_string(editData.objKind) + colon << std::endl;
    //���Ԗڂ̎��W�A�C�e���̎���
    writing_file << std::to_string(editData.collectNum) + colon << std::endl;
    //�ʒu
    writing_file << std::to_string(editData.posX) + colon << std::endl;
    writing_file << std::to_string(editData.posZ) + colon << std::endl;
    //����
    writing_file << std::to_string(editData.dirX) + colon << std::endl;
    writing_file << std::to_string(editData.dirZ) + colon << std::endl;
    writing_file.close();
}
/// <summary>
/// �ҏW��������ۑ�����
/// </summary>
/// <param name="editData">�ҏW�������</param>
/// <param name="saveFileName">�ۑ�����t�@�C��</param>
void EditDataSaver::SaveEditDataForJson(PlacementData editData, std::string saveFileName) const
{
    using namespace rapidjson;
    Document doc(kObjectType);
    doc.AddMember("objectKindNum", editData.objKind, doc.GetAllocator());

    doc.AddMember("appearCollectNum", editData.collectNum,doc.GetAllocator());
    doc.AddMember("positionX", editData.collectNum,doc.GetAllocator());
    doc.AddMember("positionZ", editData.collectNum,doc.GetAllocator());
    doc.AddMember("directionX", editData.collectNum,doc.GetAllocator());
    doc.AddMember("directionZ", editData.collectNum,doc.GetAllocator());

    std::ofstream ofs(saveFileName + jsonFile);
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    doc.Accept(writer);
}
