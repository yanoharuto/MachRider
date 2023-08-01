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
ActorParameter InitActor::GetActorParamator(InitObjKind kind)
{
    auto initData = GetActorParametorString(kind);
    ActorParameter initParam = {};
    //������R���e�i���珉�����f�[�^����
    initParam.GetExtractParamator(initData);
    auto dataPass = GetActorInitPassData(kind);
    //model����
    initParam.modelHandle = AssetManager::Get3DModelAssetHandle(dataPass.modelPass);
    initParam.addData = dataPass.addData;
    return initParam;
}
/// <summary>
/// �e�A�N�^�[�̈ʒu���L���^�C���ԍ����o��
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
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