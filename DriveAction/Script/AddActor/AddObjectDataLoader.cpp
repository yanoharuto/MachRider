#include "AddObjectDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// ’Ç‰Áî•ñ‚ğ“Ç‚İæ‚é
/// </summary>
/// <param name="loadData">“Ç‚İæ‚è‚½‚¢’Ç‰Áî•ñ</param>
AddObjectDataLoader::AddObjectDataLoader(AddData loadData)
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(GetInitCsvFilePass(AssetList::objectAddData));
    if (initDataLoader->IsOpenFile())//ƒtƒ@ƒCƒ‹‚ªŒ©‚Â‚©‚Á‚½‚©‚Ç‚¤‚©
    {
         loadAddData = initDataLoader->GeFileStringData();
    }
    else//Json‚Å“Ç‚İ‚Ş
    {
        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(GetInitJsonFilePass(AssetList::objectAddData), schemaPass);
        loadAddData = GetAssetListJson(initJsonFileLoader);
        SAFE_DELETE(initJsonFileLoader);
    }
    SAFE_DELETE(initDataLoader);
}
/// <summary>
/// ’Ç‰Áî•ñ‚ğ•¶š—ñ‚Å“n‚·
/// </summary>
/// <returns>•¶š—ñ‚Å“n‚·</returns>
std::vector<std::string> AddObjectDataLoader::GetLoadData()const
{
    return loadAddData;
}
