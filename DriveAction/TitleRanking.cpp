#include "TitleRanking.h"
#include "NumUI.h"
#include "Utility.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
TitleRanking::TitleRanking()
{
    highUI = new NumUI(titleHiScoreNum);
    secondUI = new NumUI(titleSecondScoreNum);
    thirdUI = new NumUI(titleThirdScoreNum);
    rankUI = UIManager::CreateUIData(titleHiScore);
    highRankUI = new NumUI(rank1);
    secondRankUI = new NumUI(rank2);
    thirdRankUI = new NumUI(rank3);
}

TitleRanking::~TitleRanking()
{
    SAFE_DELETE(highUI);
    SAFE_DELETE(secondUI);
    SAFE_DELETE(thirdUI);
}

void TitleRanking::Draw() const
{
    auto borders = StageDataManager::GetScoreBorder();
    //スコアの描画
    
    
    
    Draw(highUI, borders.highScore, firstColor);
    Draw(highRankUI, 1, firstColor);
    //スコアの描画
    Draw(secondUI, borders.second, secondColor);
    Draw(secondRankUI, 2, secondColor);
    //スコアの描画
    Draw(thirdUI, borders.third, thirdColor);
    Draw(thirdRankUI, 3, thirdColor);
    
    
    
    UIDrawer::DrawRotaUI(rankUI);
}

void TitleRanking::Draw(NumUI* ui, int score, VECTOR color) const
{
    SetDrawBright(color.x, color.y, color.z);
    ui->Draw(score);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
}
