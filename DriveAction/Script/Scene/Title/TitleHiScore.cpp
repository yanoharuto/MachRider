#include "TitleHiScore.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// タイトルで表示するハイスコア
/// </summary>
TitleHiScore::TitleHiScore()
    :NumUI(titleHiScoreNum)
{
    
}

TitleHiScore::~TitleHiScore()
{
}
/// <summary>
/// 現在選ばれているステージのハイスコア表示
/// </summary>
/// <param name="num"></param>
void TitleHiScore::Draw() const
{
    int prevHiScore = StageDataManager::GetScoreBorder().highScore;

    NumUI::Draw(prevHiScore);   
}