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

//initActorFileNameの先のファイルから所得したデータをまとめたVector
std::vector<std::string> InitActor::objectInitDataPassVec;
//初期化するパスを纏めているファイルの名前
std::string InitActor::initActorFileName = "data/model/InitObjPass.csv";
//描画モデルの管理担当
AssetManager* InitActor::assetManager;

using namespace rapidjson;
/// <summary>
/// 全てのactorの初期化をするためのパスが入ったファイルを読み込む
/// </summary>
InitActor::InitActor()
{
    if (initActorFileName.find("csv") != -1)//csvと書いてあるなら
    {
        CSVFileLoader* initDataLoader = new CSVFileLoader(initActorFileName);
        objectInitDataPassVec = initDataLoader->GeFileStringData();
        SAFE_DELETE(initDataLoader);
    }
    else//json形式
    {
        //ファイルを開く
        std::ifstream ifs(initActorFileName.c_str());
        //ファイルを開けたなら
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
/// 初期化に必要な色々なパスを所得
/// </summary>
/// <param name="obj">初期化したいオブジェクト</param>
/// <returns>引数のオブジェクトの追加情報や描画モデルまでのパス</returns>
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
    int num = static_cast<int>(objKind);
    //CSVファイルではなかったら
    if(initActorFileName.find("csv")!=-1)
    {
        //データ読み取り
        CSVFileLoader* initDataLoader = new CSVFileLoader(objectInitDataPassVec[num]);
        initData = initDataLoader->GeFileStringData();
        SAFE_DELETE(initDataLoader);
    }
    else
    {
        num = objKind / 3 - player;
        std::string path = objectInitDataPassVec[num];
        //ファイルを開く
        std::ifstream ifs(path.c_str());
        //ファイルを開けたなら
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