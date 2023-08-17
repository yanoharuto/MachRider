#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
namespace InitStage
{
    enum StageData
    {
        width = 1,//横幅
        length = 3,//縦幅
        enemyFilePass = 5,//障害物の位置のファイルパス
        collectFilePass = 7,//収集アイテムと敵の位置のファイルパス
        playerPositionFilePass = 9,//プレイヤーの初期位置のファイルパス
        gameTime = 11,//制限時間
        stageScoreFilePass = 13//ステージのスコア
    };
    //スコアの階級
    enum StageScore
    {
        //一番目にいいスコア
        goldScore,
        //二番目にいいスコア
        silverScore,
        //三番目にいいスコア
        bronzeScore,
        //遊んだ中で最高スコア
        highScore,
        //二番目にいいスコア
        secondScore,
        //3番目にいいスコア
        thirdScore
    };
    /// <summary>
    /// スコアの階級
    /// </summary>
    struct  ScoreBorder
    {
        //一番目にいいスコア
        int gold;
        //二番目にいいスコア
        int silver;
        //三番目にいいスコア
        int bronze;
        //遊んだ中で最高スコア
        int highScore;
        //二番目にいいスコア
        int second;
        //3番目にいいスコア
        int third;
    };
}
using namespace InitStage;
class StageSelect;
/// <summary>
/// 遊ぶステージのデータのパスを渡す
/// </summary>
class StageDataManager
{
public:
    /// <summary>
    /// 所得するステージの変更
    /// </summary>
    /// <param name="select">今選んでいるステージを教えてもらう</param>
    static void ChangeStageData(StageSelect* const select);
    /// <summary>
    /// ステージの数
    /// </summary>
    /// <returns></returns>
    static int GetStageTotalNumber();
    /// <summary>
    /// どのステージを選んでいるか
    /// </summary>
    /// <returns></returns>
    static std::string GetLoadeStageName();
    /// <summary>
    /// 各ステージのデータを取ってくる
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    static std::string GetStageData(StageData dataKind);
    /// <summary>
    /// ステージの横幅
    /// </summary>
    /// <returns></returns>
    static int GetStageWidth() { return stageWidth; };
    /// <summary>
    /// ステージの縦幅
    /// </summary>
    /// <returns></returns>
    static int GetStageLength() { return stageLength; };
    /// <summary>
    /// 遊ぶステージのスコアのボーダーラインを返す
    /// </summary>
    /// <returns></returns>
    static ScoreBorder GetScoreBorder();
    /// <summary>
    /// 遊ぶステージのハイスコアを更新
    /// </summary>
    static void SaveHiScore(int score);
private:
    /// <summary>
    /// 初期化
    /// </summary>
    static void InitStageData();
    //ステージの一覧的な奴
    static const std::string allStageAddresFile;
    //ステージのデータ
    static std::vector<std::string> dataVector;
    //各ステージのデータのパス
    static std::string fileAddres;
    //幅
    static int stageWidth;
    //長さ
    static int stageLength;
private:
    StageDataManager();
};