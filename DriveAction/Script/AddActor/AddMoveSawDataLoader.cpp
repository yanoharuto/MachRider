#include "AddMoveSawDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// �ړ��ۋ��̏���ǂݎ��
/// </summary>
AddMoveSawDataLoader::AddMoveSawDataLoader()
    :AddObjectDataLoader()
{
    
    if (IsExistJsonFile())//json�t�@�C���������������ǂ���
    {

        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(addDataList[CAST_I(AddData::moveSaw)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveTime")));
        SAFE_DELETE(initJsonFileLoader);
    }
    else//csv�œǂݍ���
    {
        CSVFileLoader* initDataLoader = new CSVFileLoader(addDataList[CAST_I(AddData::moveSaw)]);
        loadData = initDataLoader->GetStringData();
        SAFE_DELETE(initDataLoader);
    }
    
}