#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"

//initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
std::vector<std::string> InitActor::objectInitDataPassVec;
//model�̃p�X�Ƃ��ۑ�
std::unordered_map<InitObjKind, InitDataPass> InitActor::initPassDataFileMap;
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
ActorParametor InitActor::GetActorParamator(InitObjKind obj)
{
    auto initData = GetActorParametorString(obj);
    ActorParametor initParam = {};
    initParam.GetExtractParamator(initData);
    return initParam;
}
/// <summary>
/// �������ɕK�v�ȐF�X�ȃp�X������
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
InitDataPass InitActor::GetActorInitPassData(InitObjKind obj)
{
    if (!initPassDataFileMap.contains(obj))//�܂������������Ƃ��Ȃ��Ȃ珊��
    {
        auto initData = GetActorParametorString(obj);
        InitDataPass passData = {};
        passData.GetExtractParamator(initData);
        initPassDataFileMap.insert(std::make_pair(obj,passData));
    }
    return initPassDataFileMap[obj];
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