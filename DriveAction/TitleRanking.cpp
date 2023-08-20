#include "TitleRanking.h"
#include "NumUI.h"
#include "Utility.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// タイトルで各ステージのスコアランキング上位三名を描画
/// </summary>
TitleRanking::TitleRanking()
{
    //スコアUI
    highUI = new NumUI(titleHiScoreNum);
    secondUI = new NumUI(titleSecondScoreNum);
    thirdUI = new NumUI(titleThirdScoreNum);
    //順位UI
    highRankUI = new NumUI(rank1);
    secondRankUI = new NumUI(rank2);
    thirdRankUI = new NumUI(rank3);
    //HighScoreの文字
    rankUI = UIManager::CreateUIData(titleHiScore);
}
/// <summary>
/// ランキングを構成する数字UIを消去
/// </summary>
TitleRanking::~TitleRanking()
{
    SAFE_DELETE(highUI);
    SAFE_DELETE(secondUI);
    SAFE_DELETE(thirdUI);
    SAFE_DELETE(highRankUI);
    SAFE_DELETE(secondRankUI);
    SAFE_DELETE(thirdRankUI);
}
/// <summary>
/// ランキングの上位三名を描画
/// </summary>
void TitleRanking::Draw() const
{
    auto borders = StageDataManager::GetScoreBorder();
    //1位スコアの描画
    Draw(highUI, borders.highScore, firstColor);
    Draw(highRankUI, 1, firstColor);
    //2位スコアの描画
    Draw(secondUI, borders.second, secondColor);
    Draw(secondRankUI, 2, secondColor);
    //3位スコアの描画
    Draw(thirdUI, borders.third, thirdColor);
    Draw(thirdRankUI, 3, thirdColor);
    //HighScoreの文字
    UIDrawer::DrawRotaUI(rankUI);
}
/// <summary>
/// 引数の要素を使って描画
/// </summary>
/// <param name="ui">使いたい数字描画UI</param>
/// <param name="num">描画したい数字</param>
/// <param name="color">数字の色</param>
void TitleRanking::Draw(NumUI* ui, int num, VECTOR color) const
{
    SetDrawBright(color.x, color.y, color.z);
    ui->Draw(num);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
}
