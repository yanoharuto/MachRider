#include "AddObjectDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 追加情報を読み取る
/// </summary>
AddObjectDataLoader::AddObjectDataLoader()
{
    addDataList = GetAssetList(AssetList::objectAddData);
}