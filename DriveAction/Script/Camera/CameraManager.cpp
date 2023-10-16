#include "CameraManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"


/// <summary>
/// 初期化情報所得
/// </summary>
/// <param name="type">シーンによってカメラの性能を変える</param>
CameraManager::CameraParamater CameraManager::GetCameraParamator(InitCamera::UseCameraSceneKind type)const
{
    //カメラ情報まとめファイルを所得
    CSVFileLoader* initFileLoader = new CSVFileLoader(GetInitCsvFilePass(AssetList::camera));
    auto strData = initFileLoader->GeFileStringData();
    //まとめファイルからシーンごとの情報を所得
    CSVFileLoader* initDataLoader = new CSVFileLoader(strData[static_cast<int>(type)]);
    strData = initDataLoader->GeFileStringData();
    SAFE_DELETE(initFileLoader);
    using enum InitCamera::CameraParameter;
    //返り値
    CameraParamater returnValue;
    //カメラの有効範囲
    returnValue.nearValue = STR_TO_F(strData[static_cast<int>(setNearValue)]);
    returnValue.farValue = STR_TO_F(strData[static_cast<int>(setFarValue)]);
    
    //ターゲットとの距離
    returnValue.targetBetween = STR_TO_F(strData[static_cast<int>(setTargetBetween)]);
    //高度
    returnValue.setYPos = STR_TO_F(strData[static_cast<int>(setYPosition)]);
    //カメラの速さ
    returnValue.speed = STR_TO_F(strData[static_cast<int>(setCameraSpeed)]);
    //カメラの見えている範囲
    returnValue.lookAngle = STR_TO_F(strData[static_cast<int>(setLookingAngle)]);

    SAFE_DELETE(initDataLoader);
    return returnValue;
}
