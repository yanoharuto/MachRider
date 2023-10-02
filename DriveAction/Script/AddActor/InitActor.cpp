#include <iostream>
#include <fstream>
#include <sstream>
#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "AssetManager.h"
#include "JsonFileLoader.h"
//initActorFileNameの先のファイルから所得したデータをまとめたVector
std::vector<std::string> InitActor::objectInitDataPassVec;
//初期化するパスを纏めているファイルの名前
std::string InitActor::initActorCSVFilePass = "data/model/InitObjPass.csv";
//初期化するオブジェクトのパスを纏めているJsonのパス
std::string InitActor::initActorJsonFilePass = "data/model/InitObjPass.json";
//initActorJsonFilePassのJsonSchemaのパス
std::string InitActor::initActorSchemaPass = "data/model/InitObjPassSchema.json";
//初期化要素のJsonSchemaのパス
std::string InitActor::initObjParamatorSchemaPass = "data/model/InitObjParamatorSchema.json";
//描画モデルの管理担当
AssetManager* InitActor::assetManager;
/// <summary>
/// 全てのactorの初期化をするためのパスが入ったファイルを読み込む
/// </summary>
InitActor::InitActor()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(initActorCSVFilePass);
    if (initDataLoader->IsOpenFile())//ファイルが見つかったかどうか
    {
        objectInitDataPassVec = initDataLoader->GeFileStringData();
    }
    else
    {
        JsonFileLoader* initJsonFileLoader= new JsonFileLoader(initActorJsonFilePass,initActorSchemaPass);
        if (initJsonFileLoader->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
        {
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("player"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("moveSaw"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("saw"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("bomberShip"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("bomber"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("upDownShip"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("circleLaserShip"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("laser"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("collect"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("floor"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("skyDome"));
            objectInitDataPassVec.push_back(initJsonFileLoader->GetLoadString("wall"));
        }
        SAFE_DELETE(initJsonFileLoader);
    }
    //SAFE_DELETE(initDataLoader);
    assetManager = new AssetManager();
}
/// <summary>
/// 描画モデル管理担当の解放
/// </summary>
InitActor::~InitActor()
{
    SAFE_DELETE(assetManager);
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
    initParam.firstPosY = strtof(initData[firstPosY].c_str(), &end);
    initParam.setBouncePow = strtof(initData[bouncePower].c_str(), &end);
    initParam.setRadius = strtof(initData[collRadius].c_str(), &end);
    return initParam;
}
/// <summary>
/// 引数の種類の描画モデルハンドルを渡す
/// </summary>
/// <param name="kind">取り出したい描画モデル</param>
/// <returns>描画モデルハンドル</returns>
int InitActor::GetModelHandle(InitObjKind kind)
{
    //描画モデル
    int modelHandle = assetManager->Get3DModelAssetHandle(GetActorInitPassData(kind).modelPass);
    char* end;
    //modelの大きさを変更
    float modelScale = strtof(GetActorParametorStrVec(kind)[InitObjParamator::modelSize].c_str(), &end);
    MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));
    return modelHandle;
}
/// <summary>
/// 追加情報の入ったファイルまでのパスを渡す
/// </summary>
/// <param name="obj">追加情報が欲しいオブジェクト</param>
/// <returns>追加情報の入ったファイルまでのパス</returns>
std::string InitActor::GetAddDataPass(InitObjKind kind)
{
    //各オブジェクト毎に必要な追加データ
    auto dataPass = GetActorInitPassData(kind);
    return dataPass.addData;
}
/// <summary>
/// 引数のオブジェクトの初期化に必要な色々なパスを所得
/// </summary>
/// <param name="obj">初期化したいオブジェクトの種類</param>
/// <returns>初期化に使うパス</returns>
InitDataPass InitActor::GetActorInitPassData(InitObjKind obj)
{
    auto initData = GetActorParametorStrVec(obj);
    InitDataPass passData = {};
    passData.GetExtractParamator(initData);
    return passData;
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