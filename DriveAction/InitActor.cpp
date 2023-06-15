#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "AssetManager.h"
//initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
std::vector<std::string> InitActor::objectInitDataPassVec;
//����������p�X��Z�߂Ă���t�@�C���̖��O
std::string InitActor::initActorFileName = "data/model/InitObjPass.csv";
/// <summary>
/// actor�̏�����������
/// </summary>
InitActor::InitActor()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(initActorFileName);
    objectInitDataPassVec = initDataLoader->GetLoadStringData();
    
    SAFE_DELETE(initDataLoader);
}

InitActor::~InitActor()
{
}
/// <summary>
/// �������ɕK�v�ȏ�������
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
ActorParameter InitActor::GetActorParamator(InitObjKind obj)
{
    auto initData = GetActorParametorString(obj);
    ActorParameter initParam = {};
    initParam.GetExtractParamator(initData);
    auto dataPass = GetActorInitPassData(obj);
    initParam.modelHandle = AssetManager::Get3DModelAssetHandle(dataPass.modelPass);
    initParam.addData = dataPass.addData;
    return initParam;
}
int InitActor::GetActorTileNum(InitObjKind obj)
{
    auto initData = GetActorParametorString(obj);
    return atof(initData[mapTiledNum].c_str());
}
/// <summary>
/// �������ɕK�v�ȐF�X�ȃp�X������
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
InitDataPass InitActor::GetActorInitPassData(InitObjKind obj)
{
    auto initData = GetActorParametorString(obj);
    InitDataPass passData = {};
    passData.GetExtractParamator(initData);
    return passData;
}

/// <summary>
/// �����������������
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
std::vector<std::string> InitActor::GetActorParametorString(InitObjKind objKind)
{
    int num = static_cast<int>(objKind);
    //�f�[�^�ǂݎ��
    CSVFileLoader* initDataLoader = new CSVFileLoader(objectInitDataPassVec[num]);
    auto initData = initDataLoader->GetLoadStringData();
    SAFE_DELETE(initDataLoader);
    return initData;
}