#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "EditObjectData.h"
#include "InitObjKind.h"

using namespace ObjectInit;
/// <summary>
/// �ҏW�������̂�CSV�t�@�C���ɕۑ�����
/// </summary>
class EditDataSaver
{
public:
    EditDataSaver();
    ~EditDataSaver();
    /// <summary>
    /// �ҏW��������ۑ�����
    /// </summary>
    /// <param name="editData">�ҏW��������Z�߂�Vector</param>
    /// <param name="editObjKind">�ҏW�������</param>
    void SaveEditData(std::vector<PlacementData> editData,InitObjKind editObjKind)const;
private:
    /// <summary>
    /// �ҏW��������ۑ�����
    /// </summary>
    /// <param name="editData">�ҏW�������</param>
    /// <param name="saveFileName">�ۑ�����t�@�C��</param>
    void SaveEditData(PlacementData editData,std::string saveFileName)const;

    const std::string playerSaveFileName = "playerData(1).csv";
    const std::string collectSaveFileName = "collectData(1).csv";
    const std::string enemySaveFileName = "enemyData(1).csv";
};