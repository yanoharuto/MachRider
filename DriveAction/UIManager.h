#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace UIInit
{
    //UIの種類
    enum UIKind
    {
        //ゲームの目標
gamePurose = 2,
//カウントダウン
countDownUI = 5,
//コレクトアイテムの残り数などのUI
collectItemUI = 8,
//収集物のスコアの文字
collectScore = 11,
//収集物のスコア
collectScoreIcon = 14,
//ダメージを受けると減少するスコアの文字
damageScore = 17,
//ダメージを受けると減少するスコア
damageScoreNum = 20,
//収集アイテムの最初の数についてのUI
allCollectItemNum = 23,
//操作説明
manual = 26,
//小数点
point = 29,
//レーダー
radar = 32,
//タイトルロゴ
tilteLogo = 35,
//タイマーの枠
timerFrame = 38,
//残り時間スコアの文字
timeScore = 41,
//残り時間のスコア
timeScoreNum = 44,
//合計スコアの文字
totalScore = 47,
//合計スコア
totalScoreNum = 50,
//収集アイテムのもうゲットした数について
getCollectItemNum = 53,
//残り時間
timeNum = 56,
//メニュー画面の枠
menuFrame = 59,
//プレイ続行
playUI = 62,
//リトライ
retryUI = 65,
//メニュー画面のカーソル
menuCursor = 68,
//ゲーム終了UI
exitUI = 71,
//タイトル画面でステージ選択をするときに使う
stageName = 74,
//タイトルスペースキー催促
titlePressSpaceKey = 77,
//タイトル画面に表示するハイスコア
titleHiScore = 80,
//タイトル画面に表示するハイスコア数字
titleHiScoreNum = 83,
//カウントダウン終了時
onGameStartCountDownEnd = 86,
//誉め言葉
PraiseWord = 89,
//ゲーム終了時のカウントダウン
onGameEndCountDownEnd = 92,
//残りの収集アイテムの数
remainingCollectItemNum = 95,
//残りの収集アイテムについてのフレーズ
remainingCollectItemPhrase = 98,
//収集アイテムのアイコン
collectIcon = 101,
//収集アイテムの集める数
collectTargetNumberUI = 104,
//リザルトスペースキー催促
resultSpaceKey = 107,
//チャージ方法説明マニュアル
chargeManual = 110,
//ターボ説明マニュアル
turboManual = 113,
//左ボタン
leftButton = 116,
//右のボタン
rightButton = 119,
//下ボタン
downButton = 122,
//ゲーム終了アナウンス
finishAnnounce = 125,
//タイトルに戻るボタン
returnTitleBottonUI = 128,
//操作方法の後ろに置いておくシート
playManualSheat = 131,
//タイトルでステージを決定するときのボタン
stageSelectButton = 134,
//パッドで遊ぶ場合の下ボタン
xDownButton = 137,
//そのステージで二番目にいいスコア
titleSecondScoreNum = 140,
//そのステージで3番目にいいスコア
titleThirdScoreNum = 143,
//ランキングの１
rank1 = 146,
//ランキングの２
rank2 = 149,
//ランキングの３
rank3 = 152, 
    };

    /// <summary>
    /// UIの初期化情報　数字は読み込み段数
    /// </summary>
    enum InitUIData
    {
        //描画場所X
        drawX = 1,
        //Y
        drawY = 3,
        //画像横幅
        width = 5,
        //画像縦幅
        height = 7,
        //横幅分割数
        xNum = 9,
        //縦分割数
        yNum = 11,
        //画像の相対パス
        graphPass = 13,
        //大きさ
        UISize = 15,
        //分割してある場合のコマ送りスピード
        frameSpeed = 17
    };
    /// <summary>
    /// UIで実際に使う情報
    /// </summary>
    struct  UIData
    {
        //描画場所X
        int x = 0;
        //描画場所Y
        int y = 0;
        //分割後の画像横幅
        int width = 0;
        //分割後の画像縦幅
        int height = 0;
        //画像ハンドル
        std::vector<int> dataHandle;
        //大きさ
        float size = 0.0f;
        //コマ送り速度
        float frameSpeed = 0.0f;
    };
}
using namespace UIInit;
/// <summary>
/// UIを纏めるマネージャー
/// </summary>
class UIManager
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    UIManager();
    ~UIManager();
    /// <summary>
    /// UIを所得
    /// </summary>
    /// <param name="uiKind">所得したいUI</param>
    /// <returns></returns>
    static UIData CreateUIData(UIKind uiKind);
    /// <summary>
/// UIを所得
/// </summary>
/// <param name="uiKind">所得したいUI</param>
/// <returns></returns>
    static UIData CreateUIData(int kindNum);
 private:
     //読み込んだ情報
    static std::vector<std::string> initDataVec;
    //読み込んだ画像
    static std::unordered_map<int,UIData> loadUIDataMap;
    //uiの情報を纏めておいてあるファイル
    const std::string initUIDataPassFile = "data/UI/InitUIPass.csv";
};