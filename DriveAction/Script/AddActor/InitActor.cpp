#include <iostream>
#include <fstream>
#include <sstream>
#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "AssetManager.h"
#include "JsonFileLoader.h"
//initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
std::vector<std::string> InitActor::objectInitDataPassVec;
//����������p�X��Z�߂Ă���t�@�C���̖��O
std::string InitActor::initActorCSVFilePass = "data/model/InitObjPass.csv";
//����������I�u�W�F�N�g�̃p�X��Z�߂Ă���Json�̃p�X
std::string InitActor::initActorJsonFilePass = "data/model/InitObjPass.json";
//initActorJsonFilePass��JsonSchema�̃p�X
std::string InitActor::initActorSchemaPass = "data/model/InitObjPassSchema.json";
//�������v�f��JsonSchema�̃p�X
std::string InitActor::initObjParamatorSchemaPass = "data/model/InitObjParamatorSchema.json";
//�`�惂�f���̊Ǘ��S��
AssetManager* InitActor::assetManager;
/// <summary>
/// �S�Ă�actor�̏����������邽�߂̃p�X���������t�@�C����ǂݍ���
/// </summary>
InitActor::InitActor()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(initActorCSVFilePass);
    if (initDataLoader->IsOpenFile())//�t�@�C���������������ǂ���
    {
        objectInitDataPassVec = initDataLoader->GeFileStringData();
    }
    else
    {
        JsonFileLoader* initJsonFileLoader= new JsonFileLoader(initActorJsonFilePass,initActorSchemaPass);
        if (initJsonFileLoader->IsAccept())//�X�L�[�}�Ɠǂݍ��ރt�@�C���̃o���f�[�V�����`�F�b�N
        {
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("player"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("moveSaw"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("saw"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("bomberShip"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("bomber"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("upDownShip"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("circleLaserShip"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("laser"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("collect"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("floor"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("skyDome"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("wall"));
        }
        SAFE_DELETE(initJsonFileLoader);
    }
    //SAFE_DELETE(initDataLoader);
    assetManager = new AssetManager();
}
/// <summary>
/// �`�惂�f���Ǘ��S���̉��
/// </summary>
InitActor::~InitActor()
{
    SAFE_DELETE(assetManager);
}
/// <summary>
/// �������ɕK�v�ȏ�������
/// </summary>
/// <param name="obj">�������������I�u�W�F�N�g</param>
/// <returns>�������ɕK�v�ȏ��</returns>
ActorParameter InitActor::GetActorParamator(InitObjKind kind)
{
    //��������񕶎���x�N�^�[
    auto initData = GetActorParametorStrVec(kind);
    ActorParameter initParam = {};
    char* end;

    //�e����String�^����float�^�ɒu������
    initParam.firstPosY = strtof(initData[firstPosY].c_str(), &end);
    initParam.setBouncePow = strtof(initData[bouncePower].c_str(), &end);
    initParam.setRadius = strtof(initData[collRadius].c_str(), &end);
    return initParam;
}
/// <summary>
/// �����̎�ނ̕`�惂�f���n���h����n��
/// </summary>
/// <param name="kind">���o�������`�惂�f��</param>
/// <returns>�`�惂�f���n���h��</returns>
int InitActor::GetModelHandle(InitObjKind kind)
{
    //�`�惂�f��
    int modelHandle = assetManager->Get3DModelAssetHandle(GetActorInitPassData(kind).modelPass);
    char* end;
    //model�̑傫����ύX
    float modelScale = strtof(GetActorParametorStrVec(kind)[InitObjParamator::modelSize].c_str(), &end);
    MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));
    return modelHandle;
}
/// <summary>
/// �ǉ����̓������t�@�C���܂ł̃p�X��n��
/// </summary>
/// <param name="obj">�ǉ���񂪗~�����I�u�W�F�N�g</param>
/// <returns>�ǉ����̓������t�@�C���܂ł̃p�X</returns>
std::string InitActor::GetAddDataPass(InitObjKind kind)
{
    //�e�I�u�W�F�N�g���ɕK�v�Ȓǉ��f�[�^
    auto dataPass = GetActorInitPassData(kind);
    return dataPass.addData;
}
/// <summary>
/// �����̃I�u�W�F�N�g�̏������ɕK�v�ȐF�X�ȃp�X������
/// </summary>
/// <param name="obj">�������������I�u�W�F�N�g�̎��</param>
/// <returns>�������Ɏg���p�X</returns>
InitDataPass InitActor::GetActorInitPassData(InitObjKind obj)
{
    auto initData = GetActorParametorStrVec(obj);
    InitDataPass passData = {};
    passData.GetExtractParamator(initData);
    return passData;
}
/// <summary>
/// �������������p�����[�^�𕶎���ŏ���
/// </summary>
/// <param name="obj">�������������I�u�W�F�N�g</param>
/// <returns>�������������p�����[�^�̕�����</returns>
std::vector<std::string> InitActor::GetActorParametorStrVec(InitObjKind objKind)
{
    std::vector<std::string> initData;
    //�������������I�u�W�F�N�g�̎�ނ�int�^�ɂ���
    int num = CAST_I(objKind);
    //�f�[�^�ǂݎ��
    CSVFileLoader* initDataLoader = new CSVFileLoader(objectInitDataPassVec[num]);
    initData = initDataLoader->GeFileStringData();
    SAFE_DELETE(initDataLoader);
    return initData;
}