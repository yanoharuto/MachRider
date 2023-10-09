#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "DxLib.h"
#include "Object.h"
#include "AssetManager.h"
namespace InitStage
{
    /// <summary>
    /// ステージごとに設定しているデータ
    /// </summary>
    enum StageData
    {
        //横幅
        width ,
        //縦幅
        length,
        //障害物の位置のファイルパス
        enemyFilePass,
        //収集アイテムと敵の位置のファイルパス
        collectFilePass,
        //プレイヤーの初期位置のファイルパス
        playerPositionFilePass,
        //制限時間
        gameTime,
        //ステージのスコア
        stageScoreFilePass
    };
    /// <summary>
    /// スコアの線引き
    /// </summary>
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
class ResultScore;
class StopTimer;
class ScoreRecordWriter;
/// <summary>
/// 遊ぶステージのデータを渡す
/// </summary>
class StageDataManager :public AssetManager
{
public:
    /// <summary>
    /// 所得するステージの変更
    /// </summary>
    /// <param name="select">今選んでいるステージを教えてもらう</param>
    static void ChangeStageData(StageSelect* const select);
    /// <summary>
    /// ステージの総数
    /// </summary>
    /// <returns>ステージの総数が返ってくる</returns>
    static int GetStageTotalNumber();
    /// <summary>
    /// 遊ぶステージのスコアのボーダーラインを返す
    /// </summary>
    /// <returns>現在遊んでいるステージのスコアの線引きを纏めたもの</returns>
    static ScoreBorder GetScoreBorder();
    /// <summary>
    /// 初期位置の文字列情報
    /// </summary>
    /// <param name="tag">欲しいオブジェクトの初期位置情報のタグ</param>
    /// <returns>tagのオブジェクトが初期位置を決めるときに必要な文字列情報</returns>
    static std::vector<std::string> GetPlaceStrData(Object::ObjectTag tag);
    /// <summary>
    /// ゲームの制限時間のタイマーを作成
    /// </summary>
    /// <returns>ゲーム制限時間タイマー</returns>
    static std::shared_ptr<StopTimer> CreateGameTimer();
    /// <summary>
    /// スコアの記録更新役を渡す
    /// </summary>
    /// <returns>スコアの記録更新役</returns>
    static ScoreRecordWriter* GetScoreRecordWriter();
private:
    /// <summary>
    /// ステージの情報管理者
    /// </summary>
    StageDataManager();
    /// <summary>
    /// 各ステージのデータを取ってくる
    /// </summary>
    /// <param name="dataKind">欲しいステージのデータの種類</param>
    /// <returns>ステージの制限時間や縦幅横幅、初期位置の入ったファイルのパスなどが返ってくる</returns>
    static std::string GetSelectStageData(StageData dataKind);
    /// <summary>
    /// どのステージを選んでいるか
    /// </summary>
    /// <returns>ステージの名前文字列を返す</returns>
    static std::string GetSelectStageName();
    /// <summary>
    /// 初期化
    /// </summary>
    static void InitStageData();
    //ステージのデータ
    static std::vector<std::string> dataVector;
    //各ステージのデータのパス
    static std::string fileAddres;
    //幅
    static int stageWidth;
    //長さ
    static int stageLength;
};