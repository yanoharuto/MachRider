#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
//初期化ファイルの名前
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
 //csvファイルまでのパス
 std::string const AssetManager::initCSVFilePass = "data/csv/List/";
 //jsonファイルまでのパス
 std::string const AssetManager::initJSONFilePass = "data/json/List/";
/// <summary>
/// 初期化で使うファイルのパスを所得
/// </summary>
/// <param name="fileKind">欲しいファイルの種類</param>
/// <returns></returns>
std::string AssetManager::GetInitFilePass(AssetList fileKind) 
{
    return initCSVFilePass + initFileNames[CAST_I(fileKind)]+".csv";
}

 