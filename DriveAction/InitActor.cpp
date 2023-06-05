#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"

//initActorFileNameの先のファイルから所得したデータをまとめたVector
std::vector<std::string> InitActor::objectInitDataPassVec;
//modelのパスとか保存
std::unordered_map<InitObjKind, InitDataPass> InitActor::initPassDataFileMap;
//初期化するパスを纏めているファイルの名前
std::string InitActor::initActorFileName = "data/model/InitObjPass.csv";
/// <summary>
/// actorの初期化をする
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
/// 初期化に必要な情報を所得
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
/// 初期化に必要な色々なパスを所得
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
InitDataPass InitActor::GetActorInitPassData(InitObjKind obj)
{
    if (!initPassDataFileMap.contains(obj))//まだ所得したことがないなら所得
    {
        auto initData = GetActorParametorString(obj);
        InitDataPass passData = {};
        passData.GetExtractParamator(initData);
        initPassDataFileMap.insert(std::make_pair(obj,passData));
    }
    return initPassDataFileMap[obj];
}

/// <summary>
/// 初期化文字列を所得
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
std::vector<std::string> InitActor::GetActorParametorString(InitObjKind objKind)
{
    int num = static_cast<int>(objKind);
    //データ読み取り
    CSVFileLoader* initDataLoader = new CSVFileLoader(objectInitDataPassVec[num]);
    auto initData = initDataLoader->GetLoadStringData();
    SAFE_DELETE(initDataLoader);
    return initData;
}