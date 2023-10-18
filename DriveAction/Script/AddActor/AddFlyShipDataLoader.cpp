#include "AddFlyShipDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// ��s�D�̏���ǂݎ��
/// </summary>
/// <param name="data">�ǂݎ���s�D</param>
AddFlyShipDataLoader::AddFlyShipDataLoader(AddData data)
    :AddObjectDataLoader()
{

    if (IsExistJsonFile())//json�t�@�C���������������ǂ���
    {

        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(addDataList[CAST_I(data)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("aliveTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("coolTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadInt("unitNum")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("unitBetween")));
        SAFE_DELETE(initJsonFileLoader);
        
    }
    else//csv�œǂݍ���
    {
        CSVFileLoader* initDataLoader = new CSVFileLoader(addDataList[CAST_I(data)]);
        loadData = initDataLoader->GetStringData();
        SAFE_DELETE(initDataLoader);
    }

}