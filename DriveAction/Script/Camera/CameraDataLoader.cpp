#include "CameraDataLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "JsonFileLoader.h"
std::string CameraDataLoader::schemaPath = "cameraParametor.json";
/// <summary>
/// 初期化情報所得
/// </summary>
/// <param name="type">シーンによってカメラの性能を変える</param>
CameraDataLoader::CameraParamater CameraDataLoader::GetCameraParamator(UseCameraSceneKind type)const
{
    //返り値
    CameraParamater returnValue;
    //カメラの一覧を所得
    std::vector<std::string> strData = GetAssetList(AssetList::camera);
    if (IsExistJsonFile())//jsonで読み込む
    {
        auto fileLoader = new JsonFileLoader(strData[CAST_I(type)], schemaPath);//シーン毎の情報を所得
        returnValue.nearValue = fileLoader->GetLoadInt("nearValue");
        returnValue.farValue = fileLoader->GetLoadInt("farValue");
        returnValue.lookAngle = fileLoader->GetLoadInt("lookAngle");
        returnValue.targetBetween = fileLoader->GetLoadInt("targetBetween");
        returnValue.setYPos = fileLoader->GetLoadInt("setYPos");
        returnValue.speed = fileLoader->GetLoadFloat("speed");
        SAFE_DELETE(fileLoader);
    }
    else
    {
        //まとめファイルからシーンごとの情報を所得
        CSVFileLoader* initDataLoader = new CSVFileLoader(strData[CAST_I(type)]);
        strData = initDataLoader->GetStringData();
        SAFE_DELETE(initDataLoader);

        //カメラの有効範囲
        returnValue.nearValue = STR_TO_F(strData[CAST_I(CameraParameter::setNearValue)]);
        returnValue.farValue = STR_TO_F(strData[CAST_I(CameraParameter::setFarValue)]);
        //ターゲットとの距離
        returnValue.targetBetween = STR_TO_F(strData[CAST_I(CameraParameter::setTargetBetween)]);
        //高度
        returnValue.setYPos = STR_TO_F(strData[CAST_I(CameraParameter::setYPosition)]);
        //カメラの速さ
        returnValue.speed = STR_TO_F(strData[CAST_I(CameraParameter::setCameraSpeed)]);
        //カメラの見えている範囲
        returnValue.lookAngle = STR_TO_F(strData[CAST_I(CameraParameter::setLookingAngle)]);
    }
    return returnValue;
}
