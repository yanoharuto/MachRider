#include "AddObjectDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// �ǉ�����ǂݎ��
/// </summary>
/// <param name="loadData">�ǂݎ�肽���ǉ����</param>
AddObjectDataLoader::AddObjectDataLoader(AddData loadData)
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(GetInitCsvFilePass(AssetList::objectAddData));
    if (initDataLoader->IsOpenFile())//�t�@�C���������������ǂ���
    {
         loadAddData = initDataLoader->GeFileStringData();
    }
    else//Json�œǂݍ���
    {
        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(GetInitJsonFilePass(AssetList::objectAddData), schemaPass);
        loadAddData = GetAssetListJson(initJsonFileLoader);
        SAFE_DELETE(initJsonFileLoader);
    }
    SAFE_DELETE(initDataLoader);
}
/// <summary>
/// �ǉ����𕶎���œn��
/// </summary>
/// <returns>������œn��</returns>
std::vector<std::string> AddObjectDataLoader::GetLoadData()const
{
    return loadAddData;
}
