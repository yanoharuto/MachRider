#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
#include "JsonFileLoader.h"
#include "Utility.h"
//�������t�@�C���̖��O
 std::string const AssetManager::initFileNames[]
= { 
    {"CameraInitPass"},
    {"initEffectPass"},
    {"InitObjPass"},
    {"InitUIPass"},
    {"SoundInitPass"},
    {"stageDataList"},
    {"ObjectAddDataPass"},
};
 //csv�t�@�C���܂ł̃p�X
 std::string const AssetManager::initCSVFilePass = "data/csv/List/";
 //json�t�@�C���܂ł̃p�X
 std::string const AssetManager::initJSONFilePass = "data/Json/List/";
/// <summary>
/// �������Ŏg���t�@�C���̃p�X������
/// </summary>
/// <param name="fileKind">�~�����t�@�C���̎��</param>
/// <returns></returns>
std::string AssetManager::GetInitCsvFilePass(AssetList fileKind) 
{
    return initCSVFilePass + initFileNames[CAST_I(fileKind)] + ".csv";
}

/// <summary>
/// �������Ŏg��Json�t�@�C���̃p�X������
/// </summary>
/// <param name="fileKind">�~�����t�@�C���̎��</param>
/// <returns>�������Ŏg��Json�t�@�C���̃p�X</returns>
std::string AssetManager::GetInitJsonFilePass(AssetList fileKind)
{
    return initJSONFilePass + initFileNames[CAST_I(fileKind)] + ".json";
}
/// <summary>
/// �ǂݎ�����t�@�C������asset�ꗗ��Vector�Ɉڂ��Ă���
/// </summary>
/// <param name="fileLoader">�ǂݎ�����t�@�C��</param>
std::vector<std::string> AssetManager::GetAssetListJson(JsonFileLoader* const fileLoader)
{
    std::vector<std::string> returnValue;
    if (fileLoader->IsAccept())//�X�L�[�}�Ɠǂݍ��ރt�@�C���̃o���f�[�V�����`�F�b�N
    {
        const rapidjson::Value& list = fileLoader->GetLoadArray("assetPass");
        auto array = list.Begin();
        //�e�I�u�W�F�N�g�̏�񂪂���t�@�C���̃p�X������
        for (int i = 0; i < static_cast<int>(list.Size()); i++)
        {
            returnValue.push_back(array->FindMember("item")->value.GetString());
            array++;
        }
    }
    return returnValue;
}

 