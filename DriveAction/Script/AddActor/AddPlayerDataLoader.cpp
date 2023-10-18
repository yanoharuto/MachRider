#include "AddPlayerDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// プレイヤーの追加情報を所得
/// </summary>
AddPlayerDataLoader::AddPlayerDataLoader()
{
    
    if (IsExistJsonFile())//jsonファイルが見つかったかどうか
    {

        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(addDataList[CAST_I(AddData::playerSpeed)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("acceleSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("lowestSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("maxSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("turboAddSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("turboTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("gripPower")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("breakPower")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("turboChargeTime")));
        SAFE_DELETE(initJsonFileLoader); 
    }
    else//csvで読み込む
    {
        CSVFileLoader* initDataLoader = new CSVFileLoader(addDataList[CAST_I(AddData::playerSpeed)]);
        loadData = initDataLoader->GetStringData();
        SAFE_DELETE(initDataLoader);
    }
    
}
