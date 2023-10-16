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
//initActorFileNameの先のファイルから所得したデータをまとめたVector
std::vector<std::string> InitActor::objectInitDataPassVec;

//initActorJsonFilePassのJsonSchemaのパス
std::string InitActor::initActorSchemaPass = "data/Json/Schema/assetPassSchema.json";
//初期化要素のJsonSchemaのパス
std::string InitActor::initObjParamatorSchemaPass = "data/Json/Schema/InitObjParamatorSchema.json";
//描画モデルの管理担当
DrawModelManager* InitActor::drawModelManager;
/// <summary>
/// 全てのactorの初期化をするためのパスが入ったファイルを読み込む
/// </summary>
InitActor::InitActor()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(GetInitCsvFilePass(AssetList::object));
    if (initDataLoader->IsOpenFile())//ファイルが見つかったかどうか
    {
        objectInitDataPassVec = initDataLoader->GeFileStringData();
    }
    else//Jsonで読み込む
    {
        JsonFileLoader* initJsonFileLoader= new JsonFileLoader(GetInitJsonFilePass(AssetList::object),initActorSchemaPass);
        objectInitDataPassVec = GetAssetListJson(initJsonFileLoader);
        SAFE_DELETE(initJsonFileLoader);
    }
    SAFE_DELETE(initDataLoader);
    drawModelManager = new DrawModelManager();
}
/// <summary>
/// 描画モデル管理担当の解放
/// </summary>
InitActor::~InitActor()
{
    SAFE_DELETE(drawModelManager);
}
/// <summary>
/// 初期化に必要な情報を所得
/// </summary>
/// <param name="obj">初期化したいオブジェクト</param>
/// <returns>初期化に必要な情報</returns>
ActorParameter InitActor::GetActorParamator(InitObjKind kind)
{
    //初期化情報文字列ベクター
    auto initData = GetActorParametorStrVec(kind);
    ActorParameter initParam = {};
    char* end;

    //各情報をString型からfloat型に置き換え
    initParam.firstPosY = strtof(initData[CAST_I(InitObjParamator::firstPosY)].c_str(), &end);
    initParam.setBouncePow = strtof(initData[CAST_I(InitObjParamator::bouncePower)].c_str(), &end);
    initParam.setRadius = strtof(initData[CAST_I(InitObjParamator::collRadius)].c_str(), &end);
    return initParam;
}
/// <summary>
/// 引数の種類の描画モデルハンドルを渡す
/// </summary>
/// <param name="kind">取り出したい描画モデル</param>
/// <returns>描画モデルハンドル</returns>
int InitActor::GetModelHandle(InitObjKind kind)
{
    auto initData = GetActorParametorStrVec(kind);
    //描画モデル
    int modelHandle = drawModelManager->Get3DModelAssetHandle(initData[CAST_I(InitObjParamator::assetPass)]);
    char* end;
    //modelの大きさを変更
    float modelScale = strtof(GetActorParametorStrVec(kind)[CAST_I(InitObjParamator::modelSize)].c_str(), &end);
    MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));
    return modelHandle;
}
/// <summary>
/// 追加情報の入ったファイルまでのパスを渡す
/// </summary>
/// <param name="obj">追加情報が欲しいオブジェクト</param>
/// <returns>追加情報の入ったファイルまでのパス</returns>
std::string InitActor::GetAddDataPass(AddDataObject kind)
{
    //各オブジェクト毎に必要な追加データ
    auto dataPass = new CSVFileLoader(GetInitCsvFilePass(AssetList::objectAddData));
    auto loadPass = dataPass->GeFileStringData();
    SAFE_DELETE(dataPass);
    return loadPass[CAST_I(kind)];
}
/// <summary>
/// 初期化したいパラメータを文字列で所得
/// </summary>
/// <param name="obj">初期化したいオブジェクト</param>
/// <returns>初期化したいパラメータの文字列</returns>
std::vector<std::string> InitActor::GetActorParametorStrVec(InitObjKind objKind)
{
    std::vector<std::string> initData;
    //初期化したいオブジェクトの種類をint型にする
    int num = CAST_I(objKind);
    //データ読み取り
    CSVFileLoader* initDataLoader = new CSVFileLoader(objectInitDataPassVec[num]);
    initData = initDataLoader->GeFileStringData();
    SAFE_DELETE(initDataLoader);
    return initData;
}