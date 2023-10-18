#include "CameraManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "JsonFileLoader.h"
std::string CameraDataLoader::schemaPath = "cameraParametor.json";
/// <summary>
/// ��������񏊓�
/// </summary>
/// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
CameraDataLoader::CameraParamater CameraDataLoader::GetCameraParamator(UseCameraSceneKind type)const
{
    //�Ԃ�l
    CameraParamater returnValue;
    //�J�����̈ꗗ������
    std::vector<std::string> strData = GetAssetList(AssetList::camera);
    if (IsExistJsonFile())//json�œǂݍ���
    {
        auto fileLoader = new JsonFileLoader(strData[CAST_I(type)], schemaPath);//�V�[�����̏�������
        if (!fileLoader->IsAccept())
        {
            int a = 0;
        }
        using enum CameraParameter;//�e�p�����[�^������
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
        //�܂Ƃ߃t�@�C������V�[�����Ƃ̏�������
        CSVFileLoader* initDataLoader = new CSVFileLoader(strData[CAST_I(type)]);
        strData = initDataLoader->GetStringData();
        SAFE_DELETE(initDataLoader);

        using enum CameraParameter;
        //�J�����̗L���͈�
        returnValue.nearValue = STR_TO_F(strData[CAST_I(setNearValue)]);
        returnValue.farValue = STR_TO_F(strData[CAST_I(setFarValue)]);
        //�^�[�Q�b�g�Ƃ̋���
        returnValue.targetBetween = STR_TO_F(strData[CAST_I(setTargetBetween)]);
        //���x
        returnValue.setYPos = STR_TO_F(strData[CAST_I(setYPosition)]);
        //�J�����̑���
        returnValue.speed = STR_TO_F(strData[CAST_I(setCameraSpeed)]);
        //�J�����̌����Ă���͈�
        returnValue.lookAngle = STR_TO_F(strData[CAST_I(setLookingAngle)]);
    }
    return returnValue;
}
