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
    //��������񕶎���R���e�i
    auto initData = GetActorParametorString(kind);
    ActorParameter initParam = {};
    char* end;
    //�e����String�^����float�^�ɒu������
    initParam.firstPosY = strtof(initData[InitObjParamator::firstPosY].c_str(), &end);
    initParam.setBouncePow = strtof(initData[InitObjParamator::bouncePower].c_str(), &end);
    initParam.setRadius = strtof(initData[InitObjParamator::collRadius].c_str(), &end);
    return initParam;
}
/// <summary>
/// �����̎�ނ̕`�惂�f����n��
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
int InitActor::GetModelHandle(InitObjKind kind)
{
    //�`�惂�f��
    int modelHandle = AssetManager::Get3DModelAssetHandle(GetActorInitPassData(kind).modelPass);
    char* end;
    //model�̑傫����ύX
    float modelScale = strtof(GetActorParametorString(kind)[InitObjParamator::modelSize].c_str(), &end);
    MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));
    return modelHandle;
}
/// <summary>
/// �ǉ���񕶎���x�N�^�[��n��
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
std::string InitActor::GetAddDataPass(InitObjKind kind)
{
    //�e�I�u�W�F�N�g���ɕK�v�Ȓǉ��f�[�^
    auto dataPass = GetActorInitPassData(kind);
    return dataPass.addData;
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