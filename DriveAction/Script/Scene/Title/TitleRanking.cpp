#include "TitleRanking.h"
#include "NumUI.h"
#include "Utility.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// �^�C�g���Ŋe�X�e�[�W�̃X�R�A�����L���O��ʎO����`��
/// </summary>
TitleRanking::TitleRanking()
{
    //�X�R�AUI
    highUI = new NumUI(titleHiScoreNum);
    secondUI = new NumUI(titleSecondScoreNum);
    thirdUI = new NumUI(titleThirdScoreNum);
    //����UI
    highRankUI = new NumUI(rank1);
    secondRankUI = new NumUI(rank2);
    thirdRankUI = new NumUI(rank3);
    //HighScore�̕���
    rankUI = UIManager::CreateUIData(titleHiScore);
}
/// <summary>
/// �����L���O���\�����鐔��UI������
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
/// �����L���O�̏�ʎO����`��
/// </summary>
void TitleRanking::Draw() const
{
    auto borders = StageDataManager::GetScoreBorder();
    //1�ʃX�R�A�̕`��
    Draw(highUI, borders.highScore, firstColor);
    Draw(highRankUI, 1, firstColor);
    //2�ʃX�R�A�̕`��
    Draw(secondUI, borders.second, secondColor);
    Draw(secondRankUI, 2, secondColor);
    //3�ʃX�R�A�̕`��
    Draw(thirdUI, borders.third, thirdColor);
    Draw(thirdRankUI, 3, thirdColor);
    //HighScore�̕���
    UIDrawer::DrawRotaUI(rankUI);
}
/// <summary>
/// �����̗v�f���g���ĕ`��
/// </summary>
/// <param name="ui">�g�����������`��UI</param>
/// <param name="num">�`�悵��������</param>
/// <param name="color">�����̐F</param>
void TitleRanking::Draw(NumUI* ui, int num, VECTOR color) const
{
    SetDrawBright(color.x, color.y, color.z);
    ui->Draw(num);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
}