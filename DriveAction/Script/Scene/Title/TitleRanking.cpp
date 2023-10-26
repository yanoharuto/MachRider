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
    highUI = new NumUI(UIKind::titleHiScoreNum);
    secondUI = new NumUI(UIKind::titleSecondScoreNum);
    thirdUI = new NumUI(UIKind::titleThirdScoreNum);
    //����UI
    highRankUI = new NumUI(UIKind::rank1);
    secondRankUI = new NumUI(UIKind::rank2);
    thirdRankUI = new NumUI(UIKind::rank3);
    //HighScore�̕���
    rankUIData = UIManager::CreateUIData(UIKind::titleHighScore);
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
    UIManager::DeleteUIGraph(&rankUIData);
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
    UIDrawer::DrawRotaUI(rankUIData);
}
/// <summary>
/// �����̗v�f���g���ĕ`��
/// </summary>
/// <param name="ui">�g�����������`��UI</param>
/// <param name="num">�`�悵��������</param>
/// <param name="color">�����̐F</param>
void TitleRanking::Draw(NumUI* ui, int num, VECTOR color) const
{
    SetDrawBright(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
    ui->Draw(num);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);
}
