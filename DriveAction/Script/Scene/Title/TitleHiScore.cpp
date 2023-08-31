#include "TitleHiScore.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// �^�C�g���ŕ\������n�C�X�R�A
/// </summary>
TitleHiScore::TitleHiScore()
    :NumUI(titleHiScoreNum)
{
    
}

TitleHiScore::~TitleHiScore()
{
}
/// <summary>
/// ���ݑI�΂�Ă���X�e�[�W�̃n�C�X�R�A�\��
/// </summary>
/// <param name="num"></param>
void TitleHiScore::Draw() const
{
    int prevHiScore = StageDataManager::GetScoreBorder().highScore;

    NumUI::Draw(prevHiScore);   
}