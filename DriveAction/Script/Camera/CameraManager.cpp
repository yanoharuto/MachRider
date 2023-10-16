#include "CameraManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"


/// <summary>
/// ��������񏊓�
/// </summary>
/// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
CameraManager::CameraParamater CameraManager::GetCameraParamator(InitCamera::UseCameraSceneKind type)const
{
    //�J�������܂Ƃ߃t�@�C��������
    CSVFileLoader* initFileLoader = new CSVFileLoader(GetInitCsvFilePass(AssetList::camera));
    auto strData = initFileLoader->GeFileStringData();
    //�܂Ƃ߃t�@�C������V�[�����Ƃ̏�������
    CSVFileLoader* initDataLoader = new CSVFileLoader(strData[static_cast<int>(type)]);
    strData = initDataLoader->GeFileStringData();
    SAFE_DELETE(initFileLoader);
    using enum InitCamera::CameraParameter;
    //�Ԃ�l
    CameraParamater returnValue;
    //�J�����̗L���͈�
    returnValue.nearValue = STR_TO_F(strData[static_cast<int>(setNearValue)]);
    returnValue.farValue = STR_TO_F(strData[static_cast<int>(setFarValue)]);
    
    //�^�[�Q�b�g�Ƃ̋���
    returnValue.targetBetween = STR_TO_F(strData[static_cast<int>(setTargetBetween)]);
    //���x
    returnValue.setYPos = STR_TO_F(strData[static_cast<int>(setYPosition)]);
    //�J�����̑���
    returnValue.speed = STR_TO_F(strData[static_cast<int>(setCameraSpeed)]);
    //�J�����̌����Ă���͈�
    returnValue.lookAngle = STR_TO_F(strData[static_cast<int>(setLookingAngle)]);

    SAFE_DELETE(initDataLoader);
    return returnValue;
}
