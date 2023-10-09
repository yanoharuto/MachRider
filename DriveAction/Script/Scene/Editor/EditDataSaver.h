#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "EditObjectData.h"
#include "InitObjKind.h"

using namespace ObjectInit;
/// <summary>
/// �ҏW�������̂��t�@�C���ɕۑ�����
/// </summary>
class EditDataSaver
{
public:
    /// <summary>
    /// �ҏW�������̂��t�@�C���ɕۑ�����
    /// </summary>
    EditDataSaver() {};
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
    /// <summary>
    /// �ҏW��������ۑ�����
    /// </summary>
    /// <param name="editData">�ҏW�������</param>
    /// <param name="saveFileName">�ۑ�����t�@�C��</param>
    void SaveEditDataForJson(PlacementData editData,std::string saveFileName)const;
    //�v���C���[�̔z�u���̕ۑ���t�@�C��
    const std::string playerSaveFileName = "playerData(1)";
    //���W�A�C�e���̔z�u���̕ۑ��t�@�C��
    const std::string collectSaveFileName = "collectData(1)";
    //�G�̔z�u���̕ۑ��t�@�C��
    const std::string enemySaveFileName = "enemyData(1)";
    const std::string jsonFile = ".json";
    const std::string csvFIle = ".csv";
};