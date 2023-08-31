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
void EditManual::Draw(StageDataEditor* const editor)
{
    //�\��Y�ʒu
    int charY = screenHeight - strBetweenY;
    //�I�u�W�F�N�g��I��
    if (editor->IsEndEditing())
    {
        DrawString(0, charY, selectCrossKeyAction.c_str(), GetColor(0, 0, 0));
        DrawString(strBetweenX, charY, selectSpaceKeyAction.c_str(), GetColor(0, 0, 0));
    }
    else//�ҏW��
    {
        DrawString(0, charY, editCrossAction.c_str(), GetColor(0, 0, 0));
        DrawString(strBetweenX, charY, editSpaceKeyAction.c_str(), GetColor(0, 0, 0));
        DrawString(strBetweenX * 2, charY, wKeyAction.c_str(), GetColor(0, 0, 0));
    }
    //�J���������폜���@
    charY -= strBetweenY;
    DrawString(0, charY , aKeyAction.c_str(), GetColor(0, 0, 0));
    DrawString(strBetweenX, charY , dKeyAction.c_str(), GetColor(0, 0, 0));
    DrawString(strBetweenX * 2, charY , sKeyAction.c_str(), GetColor(0, 0, 0));
}

