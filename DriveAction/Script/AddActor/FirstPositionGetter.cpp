#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "JsonFileLoader.h"
#include "StageDataManager.h"
std::string FirstPositionGetter::schemaPass = "";
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
/// 引数のファイルから読み取って初期位置を渡す
/// </summary>
/// <param name="fileName">配置情報ファイルの名前</param>
/// <param name="kind">配置したいオブジェクトの種類</param>
/// <returns>配置情報のコンテナ</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(std::string fileName, ObjectInit::InitObjKind kind)
{
    //初期化文字列をファイルから所得し
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    //配置情報に変換する
    auto placeData = CSVConvertFirstData(csv->GeFileStringData());
    
    //同じ種類のオブジェクトだけ選定して返り値にする
    std::vector<PlacementData> returnData = {};
    for (int i = 0; i < CONTAINER_GET_SIZE(placeData); i++)
    {
        if (placeData[i].objKind == static_cast<int>(kind))
        {
            returnData.push_back(placeData[i]);
        }
    }
    SAFE_DELETE(csv);
    return returnData;
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
        using enum EditArrangementDataKind;
        initData.objKind = STR_TO_I(placeStrData[dataKindNum + static_cast<int>(objectKindNum)]);
        initData.collectNum = STR_TO_I(placeStrData[dataKindNum + static_cast<int>(appearCollectNum)]);
        initData.posX = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(positionX)]);
        initData.posZ = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(positionZ)]);
        initData.dirX = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(directionX)]);
        initData.dirZ = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(directionZ)]);
        dataVec.push_back(initData);
    }
    return dataVec;
}
/// <summary>
/// Jsonファイルからステージに配置するための情報を所得
/// </summary>
/// <param name="fileName">初期位置までのファイルパス</param>
/// <returns>ステージ配置情報</returns>
std::vector<PlacementData> FirstPositionGetter::JsonConvertFirstData(std::string fileName)
{
    std::vector<PlacementData> returnValue;
    JsonFileLoader* fileLoader = new JsonFileLoader(fileName,schemaPass);
    if (fileLoader->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
    {
        const rapidjson::Value& list = fileLoader->GetLoadArray("arrangeData");
        auto array = list.Begin();
        //各オブジェクトの初期位置情報を所得
        for (int i = 0; i < static_cast<int>(list.Size()); i++)
        {
            PlacementData firstPlaceData;
            firstPlaceData.objKind = array->FindMember("objNum")->value.GetFloat();
            firstPlaceData.collectNum = array->FindMember("collectNum")->value.GetFloat();
            firstPlaceData.posX = array->FindMember("x")->value.GetFloat();
            firstPlaceData.posZ = array->FindMember("z")->value.GetFloat();
            firstPlaceData.dirX = array->FindMember("dirX")->value.GetFloat();
            firstPlaceData.dirZ = array->FindMember("dirZ")->value.GetFloat();
            array++;
        }
    }
    return returnValue;
}