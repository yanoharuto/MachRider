#include "EditManual.h"
#include "Utility.h"
#include "DxLib.h"
#include "UIDrawer.h"
#include "StageDataEditor.h"

/// <summary>
/// �t�H���g�T�C�Y�ƕ\���ʒu�̒���
/// </summary>
EditManual::EditManual()
{
    screenHeight = static_cast<int>(SCREEN_HEIGHT * UIDrawer::GetScreenRaito() - fontSize);
    SetFontSize(fontSize);
}
/// <summary>
/// ��������\��
/// </summary>
/// <param name="editor">���ҏW���������Ă��炤</param>
void EditManual::Draw(StageDataEditor* const editor)const
{
    //�`�敶��Y���W
    int charY = screenHeight - strBetweenY;
    //�`�敶��X���W
    int charX = strBetweenX;
    //�I�u�W�F�N�g��I��
    if (editor->IsEndEditing())
    {
        //�\���I�𒆐�����
        DrawManualString(selectCrossKeyAction, charX, charY);
        charX = GetNextDrawX(selectCrossKeyAction,charX);
        //SpaceKey�I�𒆐�����
        DrawManualString(selectSpaceKeyAction, charX, charY);
        charX = GetNextDrawX(selectSpaceKeyAction, charX);
    }
    else//�ҏW��
    {
        //�\���ҏW��������
        DrawManualString(editCrossAction, charX, charY);
        charX = GetNextDrawX(editCrossAction, charX);
        //SpaceKey�ҏW��������
        DrawManualString(editSpaceKeyAction, charX, charY);
        charX = GetNextDrawX(editSpaceKeyAction, charX);
        //WKey�̖�������
        DrawManualString(wKeyAction, charX, charY);
        charX = GetNextDrawX(editSpaceKeyAction, charX);
    }
    //���s
    charY -= strBetweenY;
    charX = strBetweenX;
    //�J���������폜���@
    //AKey�̖�������
    DrawManualString(aKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //DKey�̖�������
    DrawManualString(dKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //ESCKey�̖�������
    DrawManualString(escKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //SKey�̖�������
    DrawManualString(sKeyAction, charX, charY);
}
/// <summary>
/// �����������X�̏ꏊ�����߂�
/// </summary>
/// <param name="prevStr">���O�ɏ���������</param>
/// <param name="nowX">����X���W</param>
/// <returns>���ɏ����ׂ�X���W</returns>
int EditManual::GetNextDrawX(std::string prevStr, int nowX)const
{
    return static_cast<int>(prevStr.size()) * fontSize + strBetweenX + nowX;
}
/// <summary>
/// �������̕`��
/// </summary>
/// <param name="drawStr">������</param>
/// <param name="x">�`��ʒuX</param>
/// <param name="y">�`��ʒuY</param>
void EditManual::DrawManualString(std::string drawStr, int x, int y)const
{
    DrawString(x, y, drawStr.c_str(), GetColor(0, 0, 0));
}