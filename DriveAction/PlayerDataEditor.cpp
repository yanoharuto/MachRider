#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorModelViewer.h"

/// <summary>
/// �v���C���[�̏����ʒu�̕ҏW
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor("playerData.csv")
{
    if (editDataVec.empty())
    {
        player = new EditorObject(ObjectInit::player);
    }
    else
    {
        player = new EditorObject(editDataVec[0]);
    }
    viewer = new EditorModelViewer(ObjectInit::player);
}

PlayerDataEditor::~PlayerDataEditor()
{
    SaveEditObjectData(player->GetEditObjectData());
    SAFE_DELETE(player);
}
/// <summary>
/// �X�V
/// </summary>
void PlayerDataEditor::Update()
{
    if (isEndEdit)
    {
        //�X�y�[�X�L�[�ŕҏW�J�n
        isEndEdit = UserInput::GetInputState(Space) != Push;
    }
    else if (!isEndEdit)
    {
        //�ړ���]
        player->Update();
        //�ҏW�I��
        if (UserInput::GetInputState(Space) == Push)
        {
            isEndEdit = true;
        }
    }
    //�J�����Ɍ���ׂ��I�u�W�F�N�g��`����
    nowEditObjData = player->GetEditObjectData();
    UpdateEffect();
}
/// <summary>
/// �v���C���[�̕`��
/// </summary>
void PlayerDataEditor::DrawNowEditObject() const
{
    viewer->SelectDraw(player->GetEditObjectData());
}
/// <summary>
/// �v���C���[�̕`��
/// </summary>
void PlayerDataEditor::DrawAllEditedObject() const
{
    if (isEndEdit)
    {
        viewer->Draw(player->GetEditObjectData());
    }
}
/// <summary>
/// ������`��
/// </summary>
void PlayerDataEditor::DrawEditString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), GetColor(0, 0, 0));
}
/// <summary>
/// �I������Ă���Ƃ��̕�����`��
/// </summary>
void PlayerDataEditor::DrawSelectString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), selectColor);
}
