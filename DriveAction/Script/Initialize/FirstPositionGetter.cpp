#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "StageDataManager.h"
/// <summary>
/// 初期位置を渡す
/// </summary>
/// <param name="dataKind">オブジェクトの種類によって読み込む情報を変更する</param>
/// <returns>そのオブジェクトの位置をまとめたコンテナ</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(Object::ObjectTag tag)
{
    return CSVConvertFirstData(StageDataManager::GetPlaceStrData(tag));
}
/// <summary>
/// CSVファイルからステージに配置するための情報を所得
/// </summary>
/// <param name="fileName">配置情報までのパス</param>
/// <param name="kind">所得したい配置物の種類</param>
/// <returns>CSVファイルからステージに配置するための情報</returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(std::vector<std::string> placeStrData)
{
    //データの種類と列の多さからオブジェクトの数を計算
    int objCount = placeStrData.size() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //戻り値
    std::vector<PlacementData> dataVec;

    for (int i = 0; i < objCount; i++)
    {
        //構造体の情報の種類
        int dataKindNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        //配置初期化情報
        PlacementData initData = {};
        initData.objKind = SAFE_STR_TO_I(placeStrData[dataKindNum + objectKindNum]);
        initData.collectNum = SAFE_STR_TO_I(placeStrData[dataKindNum + missionTurnNum]);
        initData.posX = SAFE_STR_TO_F(placeStrData[dataKindNum + positionX]);
        initData.posZ = SAFE_STR_TO_F(placeStrData[dataKindNum + positionZ]);
        initData.dirX = SAFE_STR_TO_F(placeStrData[dataKindNum + directionX]);
        initData.dirZ = SAFE_STR_TO_F(placeStrData[dataKindNum + directionZ]);
        dataVec.push_back(initData);
    }
    return dataVec;
}
/// <summary>
/// CSVファイルからステージに配置するための情報を所得
/// </summary>
/// <param name="fileName">配置情報までのパス</param>
/// <param name="kind">所得したい配置物の種類</param>
/// <returns>CSVファイルからステージに配置するための情報</returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(std::string fileName, ObjectInit::InitObjKind kind)
{
    //初期化文字列リストを取ってくる
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    auto initStrDataVec = csv->GetLoadStringData();

    //データの種類と列の多さからオブジェクトの数を出す
    int objCount = csv->GetLineCount() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //戻り値
    std::vector<PlacementData> dataVec;
    
    for (int i = 0; i < objCount; i++)
    {
        //構造体の情報の種類
        int groupNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        
        //配置初期化情報
        PlacementData initData = {};
        initData.objKind = SAFE_STR_TO_I(initStrDataVec[groupNum + objectKindNum]);
        //所得したい情報だったら
        if (initData.objKind == kind)
        {
            initData.collectNum = SAFE_STR_TO_I(initStrDataVec[groupNum + missionTurnNum]);
            initData.posX = SAFE_STR_TO_F(initStrDataVec[groupNum + positionX]);
            initData.posZ = SAFE_STR_TO_F(initStrDataVec[groupNum + positionZ]);
            initData.dirX = SAFE_STR_TO_F(initStrDataVec[groupNum + directionX]);
            initData.dirZ = SAFE_STR_TO_F(initStrDataVec[groupNum + directionZ]);
            dataVec.push_back(initData);
        }
    }
    SAFE_DELETE(csv);
    return dataVec;
}
