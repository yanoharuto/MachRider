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
        //マップの初期位置で使われている番号
        mapTiledNum = 17,
        //追加情報の置いてある場所
        addDataPass = 23
    };
    /// <summary>
    /// ゲームキャラの初期位置とか当たり判定の大きさとか
    /// </summary>
    struct ActorParameter
    {
        //初期高度
        float firstPosY;
        //modelの大きさ
        float setModelSize;
        //当たり判定の大きさ
        float setRadius;
        //跳ね返り力
        float setBouncePow;
        //描画モデル
        int modelHandle;
        //追加情報のPass
        std::string addData;
        /// <summary>
        /// 引数から初期化データ抽出
        /// </summary>
        /// <param name="paramatorString"></param>
        /// <returns></returns>
        void GetExtractParamator(std::vector <const char*> paramatorString)
        {
            char* end;
            firstPosY = strtof(paramatorString[InitObjParamator::firstPosY], &end);
            setModelSize = strtof(paramatorString[InitObjParamator::modelSize], &end);
            setBouncePow = strtof(paramatorString[InitObjParamator::bouncePower], &end);
            setRadius = strtof(paramatorString[InitObjParamator::collRadius], &end);
            
        }
        /// <summary>
        /// 引数から初期化データ抽出
        /// </summary>
        /// <param name="paramatorString"></param>
        /// <returns></returns>
        void GetExtractParamator(std::vector<std::string> paramatorString)
        {
            char* end;
            firstPosY = strtof(paramatorString[InitObjParamator::firstPosY].c_str(), &end);
            setModelSize = strtof(paramatorString[InitObjParamator::modelSize].c_str(), &end);
            setBouncePow = strtof(paramatorString[InitObjParamator::bouncePower].c_str(), &end);
            setRadius = strtof(paramatorString[InitObjParamator::collRadius].c_str(), &end);
        }
    };
    /// <summary>
    /// 初期化するのに必要なデータ先纏め
    /// </summary>
    struct InitDataPass
    {
        //modelのPass
        std::string modelPass;
        //追加情報のPass
        std::string addData;
        /// <summary>
        /// 引数から抽出
        /// </summary>
        /// <param name="paramatorString"></param>
        void GetExtractParamator(std::vector<std::string> paramatorString)
        {
            modelPass = paramatorString[InitObjParamator::assetPass];
            addData = paramatorString[InitObjParamator::addDataPass];
        }
        /// <summary>
        /// 引数から抽出
        /// </summary>
        /// <param name="paramatorString"></param>
        void GetExtractParamator(std::vector <const char*> paramatorString)
        {
            modelPass = paramatorString[InitObjParamator::assetPass];
            addData = paramatorString[InitObjParamator::addDataPass];
        }
    };
}
using namespace ObjectInit;
/// <summary>
/// actorの初期化をする
/// </summary>
class InitActor
{
public:
    InitActor();
    ~InitActor();
    /// <summary>
    /// 初期化に必要な情報を所得
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static ActorParameter GetActorParamator(InitObjKind obj);
    /// <summary>
    /// 初期位置の番号を返す
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static int GetActorTileNum(InitObjKind obj);
private:
    /// <summary>
    /// 初期化に必要な色々なパスを所得
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static InitDataPass GetActorInitPassData(InitObjKind obj);
    /// <summary>
    /// 初期化文字列を所得
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    static std::vector<std::string> GetActorParametorString(InitObjKind obj);
    //initActorFileNameの先のファイルから所得したデータをまとめたVector
    static std::vector<std::string> objectInitDataPassVec;
    //初期化するパスを纏めているファイルの名前
    static std::string initActorFileName; 
};