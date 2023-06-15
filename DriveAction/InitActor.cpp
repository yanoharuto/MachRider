#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "AssetManager.h"
//initActorFileNameの先のファイルから所得したデータをまとめたVector
std::vector<std::string> InitActor::objectInitDataPassVec;
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
/// 初期化に必要な色々なパスを所得
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