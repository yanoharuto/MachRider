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
ActorParameter InitActor::GetActorParamator(InitObjKind kind)
{
    //初期化情報文字列コンテナ
    auto initData = GetActorParametorString(kind);
    ActorParameter initParam = {};
    char* end;
    //各情報をString型からfloat型に置き換え
    initParam.firstPosY = strtof(initData[InitObjParamator::firstPosY].c_str(), &end);
    initParam.setBouncePow = strtof(initData[InitObjParamator::bouncePower].c_str(), &end);
    initParam.setRadius = strtof(initData[InitObjParamator::collRadius].c_str(), &end);
    return initParam;
}
/// <summary>
/// 引数の種類の描画モデルを渡す
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
int InitActor::GetModelHandle(InitObjKind kind)
{
    //描画モデル
    int modelHandle = AssetManager::Get3DModelAssetHandle(GetActorInitPassData(kind).modelPass);
    char* end;
    //modelの大きさを変更
    float modelScale = strtof(GetActorParametorString(kind)[InitObjParamator::modelSize].c_str(), &end);
    MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));
    return modelHandle;
}
/// <summary>
/// 追加情報文字列ベクターを渡す
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
std::string InitActor::GetAddDataPass(InitObjKind kind)
{
    //各オブジェクト毎に必要な追加データ
    auto dataPass = GetActorInitPassData(kind);
    return dataPass.addData;
}
/// <summary>
/// 各アクターの位置を記すタイル番号を出す
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
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