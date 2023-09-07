#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "DxLib.h"
#include "InitObjKind.h"

namespace ObjectInit
{
    /// <summary>
    ///初期化する要素
    /// </summary>
    enum InitObjParamator
    {
        //modelの相対パス
        assetPass = 2,
        //大きさ
        modelSize = 5,
        //最初のポジション
        firstPosY = 8,
        //modelの当たり半径
        collRadius = 11,
        //跳ね返りの大きさ
        bouncePower = 14,
        //追加情報の置いてある場所
        addDataPass = 17
    };
    /// <summary>
    /// ゲームキャラの初期位置とか当たり判定の大きさとか
    /// </summary>
    struct ActorParameter
    {
        //初期高度
        float firstPosY;
        //当たり判定の大きさ
        float setRadius;
        //跳ね返り力
        float setBouncePow;
    };
    /// <summary>
    /// 初期化するのに必要なデータのパス
    /// </summary>
    struct InitDataPass
    {
        //描画モデルのファイルのパス
        std::string modelPass;
        //追加情報のファイルのパス
        std::string addData;
        /// <summary>
        /// 引数から抽出
        /// </summary>
        /// <param name="pathStr"></param>
        void GetExtractParamator(std::vector<std::string> pathStr)
        {
            modelPass = pathStr[InitObjParamator::assetPass];
            addData = pathStr[InitObjParamator::addDataPass];
        }
        /// <summary>
        /// 引数から抽出
        /// </summary>
        /// <param name="pathStr"></param>
        void GetExtractParamator(std::vector <const char*> pathStr)
        {
            modelPass = pathStr[InitObjParamator::assetPass];
            addData = pathStr[InitObjParamator::addDataPass];
        }
    };
}
class AssetManager;
using namespace ObjectInit;
/// <summary>
/// actorの初期化をする
/// </summary>
class InitActor final
{
public:
    /// <summary>
    /// 全てのactorの初期化をするためのパスが入ったファイルを読み込む
    /// </summary>
    InitActor();
    /// <summary>
    /// 描画モデル管理担当の解放
    /// </summary>
    ~InitActor();
    /// <summary>
    /// 初期化に必要な情報を所得
    /// </summary>
    /// <param name="obj">初期化したいオブジェクト</param>
    /// <returns>初期化に必要な情報</returns>
    static ActorParameter GetActorParamator(InitObjKind obj);
    /// <summary>
    /// 引数の種類の描画モデルハンドルを渡す
    /// </summary>
    /// <param name="kind">取り出したい描画モデル</param>
    /// <returns>描画モデルハンドル</returns>
    static int GetModelHandle (InitObjKind obj);
    /// <summary>
    /// 追加情報の入ったファイルまでのパスを渡す
    /// </summary>
    /// <param name="obj">追加情報が欲しいオブジェクト</param>
    /// <returns>追加情報の入ったファイルまでのパス</returns>
    static std::string GetAddDataPass (InitObjKind obj);

private:
    /// <summary>
    /// 初期化に必要な色々なパスを所得
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static InitDataPass GetActorInitPassData(InitObjKind obj);
    /// <summary>
    /// 初期化したいパラメータを文字列で所得
    /// </summary>
    /// <param name="obj">初期化したいオブジェクト</param>
    /// <returns>初期化したいパラメータの文字列</returns>
    static std::vector<std::string> GetActorParametorStrVec(InitObjKind obj);
    //initActorFileNameの先のファイルから所得したデータをまとめたVector
    static std::vector<std::string> objectInitDataPassVec;
    //初期化するパスを纏めているファイルの名前
    static std::string initActorFileName; 
    //描画モデルハンドル所得役
    static AssetManager* assetManager;
};