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
    //配置した収集アイテムを保存
    for (int i = 0; i < editData.size(); i++)
    {
        SaveEditData(editData[i], saveFileName);
    }
}
void EditDataSaver::SaveEditData(PlacementData editData, std::string saveFileName) const
{
    std::ofstream writing_file;
    // ファイルを開いて
    writing_file.open(saveFileName, std::ios::app);
    //区切り文字
    std::string colon = ",";
    //オブジェクトの種類と
    writing_file << std::to_string(editData.objKind) + colon << std::endl;
    //何番目の収集アイテムの時か
    writing_file << std::to_string(editData.collectNum) + colon << std::endl;
    //位置
    writing_file << std::to_string(editData.posX) + colon << std::endl;
    writing_file << std::to_string(editData.posZ) + colon << std::endl;
    //向き
    writing_file << std::to_string(editData.dirX) + colon << std::endl;
    writing_file << std::to_string(editData.dirZ) + colon << std::endl;
    writing_file.close();
}