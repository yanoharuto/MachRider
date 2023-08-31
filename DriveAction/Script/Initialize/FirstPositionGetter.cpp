#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 初期位置を渡す
/// </summary>
/// <param name="dataKind">オブジェクトの種類によって読み込む情報を変更する</param>
/// <returns>そのオブジェクトの位置をまとめたコンテナ</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(Object::ObjectTag tag)
{
    std::vector<PlacementData> initData;//初期位置のコンテナ
    using enum Object::ObjectTag;

    switch (tag)//各オブジェクトの初期位置をまとめたコンテナを所得
    {
    case player:
        initData = CSVConvertFirstData(StageDataManager::GetSelectStageData(playerPositionFilePass));
        break;
    case damageObject:
        initData = CSVConvertFirstData(StageDataManager::GetSelectStageData(enemyFilePass));
        break;
    case collect:
        initData = CSVConvertFirstData(StageDataManager::GetSelectStageData(collectFilePass));
        break;
    }
    return initData;
}
/// <summary>
/// CSVファイルからステージに配置するための情報を所得
/// </summary>
/// <param name="fileName"></param>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(std::string fileName)
{
    //初期化文字列リストを取ってくる
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    auto initStrDataVec = csv->GetLoadStringData();
    
    //データの種類と列の多さからオブジェクトの数を計算
    int objCount = csv->GetLineCount() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //戻り値
    std::vector<PlacementData> dataVec;
    
    for (int i = 0; i < objCount; i++)
    {
        //構造体の情報の種類
        int dataKindNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        //配置初期化情報
        PlacementData initData = {};
        initData.objKind= atoi(initStrDataVec[dataKindNum + EditArrangementDataKind::objectKindNum].c_str());
        initData.collectNum = atoi(initStrDataVec[dataKindNum + EditArrangementDataKind::missionTurnNum].c_str());
        initData.posX = static_cast<float>(atof(initStrDataVec[dataKindNum + EditArrangementDataKind::positionX].c_str()));
        initData.posZ = static_cast<float>(atof(initStrDataVec[dataKindNum + EditArrangementDataKind::positionZ].c_str()));
        initData.dirX = static_cast<float>(atof(initStrDataVec[dataKindNum + EditArrangementDataKind::directionX].c_str()));
        initData.dirZ = static_cast<float>(atof(initStrDataVec[dataKindNum + EditArrangementDataKind::directionZ].c_str()));
        dataVec.push_back(initData);
    }
    SAFE_DELETE(csv);

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

    //データの種類と列の多さからオブジェクトの数を計算
    int objCount = csv->GetLineCount() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //戻り値
    std::vector<PlacementData> dataVec;

    for (int i = 0; i < objCount; i++)
    {
        //構造体の情報の種類
        int groupNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        
        //配置初期化情報
        PlacementData initData = {};
        initData.objKind = atoi(initStrDataVec[groupNum + EditArrangementDataKind::objectKindNum].c_str());
        //所得したい情報だったら
        if (initData.objKind == kind)
        {
            initData.collectNum = atoi(initStrDataVec[groupNum + EditArrangementDataKind::missionTurnNum].c_str());
            initData.posX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionX].c_str()));
            initData.posZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionZ].c_str()));
            initData.dirX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionX].c_str()));
            initData.dirZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionZ].c_str()));
            dataVec.push_back(initData);
        }
    }
    SAFE_DELETE(csv);
    return dataVec;
}
