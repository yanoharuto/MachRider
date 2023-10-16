#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include "EditObjectData.h"
#include "InitObjKind.h"
class StageDataEditor;
using namespace ObjectInit;
/// <summary>
/// �ҏW�������̂��t�@�C���ɕۑ�����
/// </summary>
class EditDataSaver
{
public:
    EditDataSaver();
    ~EditDataSaver();
    /// <summary>
    /// �ҏW��������ۑ�����
    /// </summary>
    /// <param name="editor">�ҏW���e��n���N���X</param>
    void SaveEditData(std::weak_ptr<StageDataEditor> editor);
private:
    /// <summary>
    /// �ҏW��������ۑ�����
    /// </summary>
    /// <param name="editData">�ҏW�������</param>
    /// <param name="saveFileName">�ۑ�����t�@�C��</param>
    void SaveEditDataForCSV(std::vector<PlacementData> editData,std::string saveFileName)const;
    /// <summary>
    /// �����̕ҏW����Json�ɕۑ��ł���悤�ɂ���
    /// </summary>
    /// <param name="editData">�ҏW���</param>
    /// <param name="allocator">�ҏW�̂��߂ɕK�v��allocator</param>
    /// <returns>Json�ɕۑ��ł���悤�ɂ�������</returns>
    rapidjson::Value GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator)const;
    /// <summary>
    /// Json�`���ŕۑ�����
    /// </summary>
    /// <param name="editData">�ҏW���������Z��</param>
    /// <param name="saveFileName">�ۑ���̃t�@�C���̖��O</param>
    void SaveEditDataForJSON(std::vector<PlacementData> editData, std::string saveFileName)const;
    //�v���C���[�̔z�u���̕ۑ���t�@�C��
    const std::string playerSaveFileName = "playerData(1)";
    //���W�A�C�e���̔z�u���̕ۑ��t�@�C��
    const std::string collectSaveFileName = "collectData(1)";
    //�G�̔z�u���̕ۑ��t�@�C��
    const std::string enemySaveFileName = "enemyData(1)";
    //json�`��
    const std::string jsonFile = ".json";
    //�������`��
    const std::string csvFile = ".csv";
    //�v���C���[�ҏW�ʒu���
    std::vector<PlacementData> playerPlaceData;
    //�G�ҏW�ʒu���
    std::vector<PlacementData> enemyPlaceData;
    //���W�A�C�e���ʒu���
    std::vector<PlacementData> collectPlaceData;
};