#include "NumUI.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "UIDrawer.h"
/// <summary>
/// ������`�悷��
/// </summary>
NumUI::NumUI(UIKind kind)
{
    numData = UIManager::CreateUIData(kind);
    pointData = UIManager::CreateUIData(point);
    pointData.y = numData.y;
    pointData.size = numData.size;
}

NumUI::~NumUI()
{
}

void NumUI::Draw(int num) const
{
    Draw(numData.x, numData.y, num);
}

/// <summary>
/// ������`�悵�������p
/// </summary>
/// <param name="x">��ԉE�[</param>
/// <param name="y">Y���W</param>
/// <param name="num">����</param>
/// <param name="scale">�����̑傫��</param>
/// <returns>���[�̍��W</returns>
int NumUI::Draw(int x, int y, int num) const
{
    //����
    int digits = static_cast<int>(OriginalMath::GetDigits(num));
    //�\���ʒu���E�[�ɂ�������ړ�
    x -= static_cast<int> (numData.size * numData.width * digits);
    //�������[���ɂȂ�܂ŕ`�悷��@������`�悷��
    for (int i = digits; i > 0; i--)
    {
        //10�̂����Ŋ��������̂��܂�
        int drawNum = (static_cast<int>(num / pow(TIMER_FONT_NUM, i - 1))) % numData.dataHandle.size();
        //�`��
        UIData data = numData;
        data.x = x;
        data.y = y;
        UIDrawer::DrawRotaUI(data,drawNum);
        //�ʒu�����炷
        x += static_cast<int> (numData.size * numData.width);
        //���ɕ`�悵���������̏���
        num -= static_cast<int>(drawNum * pow(TIMER_FONT_NUM, i - 1));
    }
    return x;
}
/// <summary>
/// �����_���`�悵�������p
/// </summary>
/// <param name="x">��ԉE�[</param>
/// <param name="y">Y���W</param>
/// <param name="num">����</param>
/// <param name="scale">�����̑傫��</param>
/// <returns>���[�̍��W</returns>
void NumUI::Draw(float num) const
{
    //��������
    int iNum = static_cast<int>(num);
    //�������ʂ̕���
    int decimalNum1 = static_cast<int>((num - iNum) * 10);
    //������������
    int decimalNum2 = static_cast<int>(((num - iNum) * 100 - decimalNum1 * 10));
    //�`��I�������ꏊ��edge�ɓn��
    int edge = Draw(numData.x, numData.y, decimalNum2);
    edge -= static_cast<int> (numData.size * numData.width);
    edge = Draw(edge, numData.y, decimalNum1);
    edge -= static_cast<int> (numData.size * numData.width);
    //����������`��
    Draw(edge, numData.y, iNum);
    edge -= static_cast<int> (numData.size * numData.width);
    //�����_
    UIData data = pointData;
    data.x = edge;
    UIDrawer::DrawRotaUI(data);
}
/// <summary>
/// �ꕶ���̑傫��
/// </summary>
/// <returns></returns>
int NumUI::GetNumWidthSize()
{
    return numData.width;
}
