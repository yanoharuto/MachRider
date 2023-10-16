#include "AddObjectDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 追加情報を読み取る
/// </summary>
/// <param name="loadData">読み取りたい追加情報</param>
AddObjectDataLoader::AddObjectDataLoader(AddData loadData)
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(GetInitCsvFilePass(AssetList::objectAddData));
    if (initDataLoader->IsOpenFile())//ファイルが見つかったかどうか
    {
         loadAddData = initDataLoader->GeFileStringData();
    }
    else//Jsonで読み込む
    {
        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(GetInitJsonFilePass(AssetList::objectAddData), schemaPass);
        loadAddData = GetAssetListJson(initJsonFileLoader);
        SAFE_DELETE(initJsonFileLoader);
    }
    SAFE_DELETE(initDataLoader);
}
/// <summary>
/// 追加情報を文字列で渡す
/// </summary>
/// <returns>文字列で渡す</returns>
std::vector<std::string> AddObjectDataLoader::GetLoadData()const
{
    return loadAddData;
}
