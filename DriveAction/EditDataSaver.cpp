#include "EditDataSaver.h"
#include <fstream>
EditDataSaver::EditDataSaver()
{
}

EditDataSaver::~EditDataSaver()
{
}

void EditDataSaver::SaveEditData(std::vector<PlacementData> editData, InitObjKind editObjKind)const
{
    std::string saveFileName;
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
    for (int i = 0; i < editData.size(); i++)
    {
        SaveEditData(editData[i], saveFileName);
    }
}
void EditDataSaver::SaveEditData(PlacementData editData, std::string saveFileName) const
{
    std::ofstream writing_file;
    // �t�@�C�����J����
    writing_file.open(saveFileName, std::ios::app);
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