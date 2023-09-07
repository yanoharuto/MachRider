#include <iostream>
#include <fstream>
#include <sstream>
#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "AssetManager.h"
#include "document.h"
#include "istreamwrapper.h"

//initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
std::vector<std::string> InitActor::objectInitDataPassVec;
//����������p�X��Z�߂Ă���t�@�C���̖��O
std::string InitActor::initActorFileName = "data/model/InitObjPass.csv";
//�`�惂�f���̊Ǘ��S��
AssetManager* InitActor::assetManager;

using namespace rapidjson;
/// <summary>
/// �S�Ă�actor�̏����������邽�߂̃p�X���������t�@�C����ǂݍ���
/// </summary>
InitActor::InitActor()
{
    if (initActorFileName.find("csv") != -1)//csv�Ə����Ă���Ȃ�
    {
        CSVFileLoader* initDataLoader = new CSVFileLoader(initActorFileName);
        objectInitDataPassVec = initDataLoader->GeFileStringData();
        SAFE_DELETE(initDataLoader);
    }
    else//json�`��
    {
        //�t�@�C�����J��
        std::ifstream ifs(initActorFileName.c_str());
        //�t�@�C�����J�����Ȃ�
        if(ifs.good())
        {
            rapidjson::Document doc;
            rapidjson::IStreamWrapper isw(ifs);
            doc.ParseStream(isw);
            
            objectInitDataPassVec.push_back(doc["player"].GetString());
            objectInitDataPassVec.push_back(doc["moveSaw"].GetString());
            objectInitDataPassVec.push_back(doc["bomber"].GetString());
            objectInitDataPassVec.push_back(doc["upDownShip"].GetString());
            objectInitDataPassVec.push_back(doc["circleLaserShip"].GetString());
            objectInitDataPassVec.push_back(doc["laser"].GetString());
            objectInitDataPassVec.push_back(doc["collect"].GetString());
            objectInitDataPassVec.push_back(doc["floor"].GetString());
            objectInitDataPassVec.push_back(doc["skyDome"].GetString());
            objectInitDataPassVec.push_back(doc["stage"].GetString());
        }
    }
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
/// �������ɕK�v�ȐF�X�ȃp�X������
/// </summary>
/// <param name="obj">�������������I�u�W�F�N�g</param>
/// <returns>�����̃I�u�W�F�N�g�̒ǉ�����`�惂�f���܂ł̃p�X</returns>
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
    int num = static_cast<int>(objKind);
    //CSV�t�@�C���ł͂Ȃ�������
    if(initActorFileName.find("csv")!=-1)
    {
        //�f�[�^�ǂݎ��
        CSVFileLoader* initDataLoader = new CSVFileLoader(objectInitDataPassVec[num]);
        initData = initDataLoader->GeFileStringData();
        SAFE_DELETE(initDataLoader);
    }
    else
    {
        num = objKind / 3 - player;
        std::string path = objectInitDataPassVec[num];
        //�t�@�C�����J��
        std::ifstream ifs(path.c_str());
        //�t�@�C�����J�����Ȃ�
        if (ifs.good())
        {
            rapidjson::Document doc;
            rapidjson::IStreamWrapper isw(ifs);
            doc.ParseStream(isw);

            initData.push_back(doc["modelSize"].GetString());
            initData.push_back(doc["firstPosY"].GetString());
            initData.push_back(doc["collRadius"].GetString());
            initData.push_back(doc["bouncePower"].GetString());
            initData.push_back(doc["addDataPass"].GetString());
        }
    }
    return initData;
}