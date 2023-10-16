#include <iostream>
#include <fstream>
#include <sstream>
#include <document.h>
#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "DrawModelManager.h"
#include "JsonFileLoader.h"
//initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
std::vector<std::string> InitActor::objectInitDataPassVec;

//initActorJsonFilePass��JsonSchema�̃p�X
std::string InitActor::initActorSchemaPass = "data/Json/Schema/assetPassSchema.json";
//�������v�f��JsonSchema�̃p�X
std::string InitActor::initObjParamatorSchemaPass = "data/Json/Schema/InitObjParamatorSchema.json";
//�`�惂�f���̊Ǘ��S��
DrawModelManager* InitActor::drawModelManager;
/// <summary>
/// �S�Ă�actor�̏����������邽�߂̃p�X���������t�@�C����ǂݍ���
/// </summary>
InitActor::InitActor()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(GetInitCsvFilePass(AssetList::object));
    if (initDataLoader->IsOpenFile())//�t�@�C���������������ǂ���
    {
        objectInitDataPassVec = initDataLoader->GeFileStringData();
    }
    else//Json�œǂݍ���
    {
        JsonFileLoader* initJsonFileLoader= new JsonFileLoader(GetInitJsonFilePass(AssetList::object),initActorSchemaPass);
        objectInitDataPassVec = GetAssetListJson(initJsonFileLoader);
        SAFE_DELETE(initJsonFileLoader);
    }
    SAFE_DELETE(initDataLoader);
    drawModelManager = new DrawModelManager();
}
/// <summary>
/// �`�惂�f���Ǘ��S���̉��
/// </summary>
InitActor::~InitActor()
{
    SAFE_DELETE(drawModelManager);
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
    initParam.firstPosY = strtof(initData[CAST_I(InitObjParamator::firstPosY)].c_str(), &end);
    initParam.setBouncePow = strtof(initData[CAST_I(InitObjParamator::bouncePower)].c_str(), &end);
    initParam.setRadius = strtof(initData[CAST_I(InitObjParamator::collRadius)].c_str(), &end);
    return initParam;
}
/// <summary>
/// �����̎�ނ̕`�惂�f���n���h����n��
/// </summary>
/// <param name="kind">���o�������`�惂�f��</param>
/// <returns>�`�惂�f���n���h��</returns>
int InitActor::GetModelHandle(InitObjKind kind)
{
    auto initData = GetActorParametorStrVec(kind);
    //�`�惂�f��
    int modelHandle = drawModelManager->Get3DModelAssetHandle(initData[CAST_I(InitObjParamator::assetPass)]);
    char* end;
    //model�̑傫����ύX
    float modelScale = strtof(GetActorParametorStrVec(kind)[CAST_I(InitObjParamator::modelSize)].c_str(), &end);
    MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));
    return modelHandle;
}
/// <summary>
/// �ǉ����̓������t�@�C���܂ł̃p�X��n��
/// </summary>
/// <param name="obj">�ǉ���񂪗~�����I�u�W�F�N�g</param>
/// <returns>�ǉ����̓������t�@�C���܂ł̃p�X</returns>
std::string InitActor::GetAddDataPass(AddDataObject kind)
{
    //�e�I�u�W�F�N�g���ɕK�v�Ȓǉ��f�[�^
    auto dataPass = new CSVFileLoader(GetInitCsvFilePass(AssetList::objectAddData));
    auto loadPass = dataPass->GeFileStringData();
    SAFE_DELETE(dataPass);
    return loadPass[CAST_I(kind)];
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