#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 初期位置を渡す
/// </summary>
/// <param name="dataKind">オブジェクトの種類によって読み込む情報を変更する</param>
/// <returns>そのオブジェクトの位置</returns>
std::vector<EditArrangementData> FirstPositionGetter::GetInitData(Object::ObjectTag tag)
{
    std::vector<EditArrangementData> initData;
    using enum Object::ObjectTag;

    switch (tag)
    {
    case player:
        initData = CSVConvertFirstData(StageDataManager::GetStageData(playerPositionFilePass));
        break;
    case damageObject:
        initData = CSVConvertFirstData(StageDataManager::GetStageData(enemyFilePass));
        break;
    case collect:
        initData = CSVConvertFirstData(StageDataManager::GetStageData(collectFilePass));
        break;
    }
    return initData;
}
/// <summary>
/// CSVファイルからステージに配置するための情報を所得
/// </summary>
/// <param name="fileName"></param>
std::vector<EditArrangementData> FirstPositionGetter::CSVConvertFirstData(std::string fileName)
{
    //初期化文字列リストを取ってくる
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    auto initStrDataVec = csv->GetLoadStringData();
    
    //データの種類と列の多さからオブジェクトの数を計算
    int objCount = csv->GetLineCount() / EDIT_ARRANGEMENT_DATA_KIND_NUM;

    //戻り値
    std::vector<EditArrangementData> dataVec;
    
    for (int i = 0; i < objCount; i++)
    {
        int groupNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        //配置初期化情報
        EditArrangementData initData = {};
        initData.objKind= atoi(initStrDataVec[groupNum + EditArrangementDataKind::objectKindNum].c_str());
        initData.missionNum = atoi(initStrDataVec[groupNum + EditArrangementDataKind::missionTurnNum].c_str());
        initData.posX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionX].c_str()));
        initData.posZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::positionZ].c_str()));
        initData.dirX = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionX].c_str()));
        initData.dirZ = static_cast<float>(atof(initStrDataVec[groupNum + EditArrangementDataKind::directionZ].c_str()));
        dataVec.push_back(initData);
    }
    SAFE_DELETE(csv);

    return dataVec;
}