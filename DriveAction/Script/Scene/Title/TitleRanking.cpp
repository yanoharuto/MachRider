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
    highUI = new NumUI(UIKind::titleHiScoreNum);
    secondUI = new NumUI(UIKind::titleSecondScoreNum);
    thirdUI = new NumUI(UIKind::titleThirdScoreNum);
    //順位UI
    highRankUI = new NumUI(UIKind::rank1);
    secondRankUI = new NumUI(UIKind::rank2);
    thirdRankUI = new NumUI(UIKind::rank3);
    //HighScoreの文字
    rankUIData = UIManager::CreateUIData(UIKind::titleHighScore);
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
    UIManager::DeleteUIGraph(&rankUIData);
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
    UIDrawer::DrawRotaUI(rankUIData);
}
/// <summary>
/// 引数の要素を使って描画
/// </summary>
/// <param name="ui">使いたい数字描画UI</param>
/// <param name="num">描画したい数字</param>
/// <param name="color">数字の色</param>
void TitleRanking::Draw(NumUI* ui, int num, VECTOR color) const
{
    SetDrawBright(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
    ui->Draw(num);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);
}
