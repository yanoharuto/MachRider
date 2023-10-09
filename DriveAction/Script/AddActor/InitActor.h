#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "DxLib.h"
#include "InitObjKind.h"
#include "AssetManager.h"

namespace ObjectInit
{
    /// <summary>
    ///初期化する要素
    /// </summary>
    enum class InitObjParamator
    {
        //modelの相対パス
        assetPass = 0,
        //大きさ
        modelSize = 1,
        //最初のポジション
        firstPosY = 2,
        //modelの当たり半径
        collRadius = 3,
        //跳ね返りの大きさ
        bouncePower = 4
    };
    /// <summary>
    /// 各オブジェクトの追加情報
    /// </summary>
    enum class AddDataObject
    {
        playerSpeed = 0,
        circleFlyShip = 1,
        upDownFlyShip = 2,
        bomberShip = 3,
        moveSaw = 4
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
}
class DrawModelManager;
using namespace ObjectInit;
/// <summary>
/// actorの初期化をする
/// </summary>
class InitActor final:public AssetManager
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
    static std::string GetAddDataPass (AddDataObject obj);
private:
    /// <summary>
    /// 初期化したいパラメータを文字列で所得
    /// </summary>
    /// <param name="obj">初期化したいオブジェクト</param>
    /// <returns>初期化したいパラメータの文字列</returns>
    static std::vector<std::string> GetActorParametorStrVec(InitObjKind obj);
    //initActorFileNameの先のファイルから所得したデータをまとめたVector
    static std::vector<std::string> objectInitDataPassVec;
    //initActorJsonFilePassのJsonSchemaのパス
    static std::string initActorSchemaPass; 
    //初期化要素のJsonSchemaのパス
    static std::string initObjParamatorSchemaPass; 
    //描画モデルハンドル所得役
    static DrawModelManager* drawModelManager;
};