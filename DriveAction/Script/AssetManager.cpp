#include "AssetManager.h"
#include "DxLib.h"
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
 std::string const AssetManager::initJSONFilePass = "data/json/List/";
/// <summary>
/// �������Ŏg���t�@�C���̃p�X������
/// </summary>
/// <param name="fileKind">�~�����t�@�C���̎��</param>
/// <returns></returns>
std::string AssetManager::GetInitFilePass(AssetList fileKind) 
{
    return initCSVFilePass + initFileNames[CAST_I(fileKind)]+".csv";
}

 