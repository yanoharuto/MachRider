#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
#include "JsonFileLoader.h"
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
 std::string const AssetManager::initJSONFilePass = "data/Json/List/";
/// <summary>
/// 初期化で使うファイルのパスを所得
/// </summary>
/// <param name="fileKind">欲しいファイルの種類</param>
/// <returns></returns>
std::string AssetManager::GetInitCsvFilePass(AssetList fileKind) 
{
    return initCSVFilePass + initFileNames[CAST_I(fileKind)] + ".csv";
}

/// <summary>
/// 初期化で使うJsonファイルのパスを所得
/// </summary>
/// <param name="fileKind">欲しいファイルの種類</param>
/// <returns>初期化で使うJsonファイルのパス</returns>
std::string AssetManager::GetInitJsonFilePass(AssetList fileKind)
{
    return initJSONFilePass + initFileNames[CAST_I(fileKind)] + ".json";
}
/// <summary>
/// 読み取ったファイルからasset一覧をVectorに移していく
/// </summary>
/// <param name="fileLoader">読み取ったファイル</param>
std::vector<std::string> AssetManager::GetAssetListJson(JsonFileLoader* const fileLoader)
{
    std::vector<std::string> returnValue;
    if (fileLoader->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
    {
        const rapidjson::Value& list = fileLoader->GetLoadArray("assetPass");
        auto array = list.Begin();
        //各オブジェクトの情報があるファイルのパスを所得
        for (int i = 0; i < static_cast<int>(list.Size()); i++)
        {
            returnValue.push_back(array->FindMember("item")->value.GetString());
            array++;
        }
    }
    return returnValue;
}

 