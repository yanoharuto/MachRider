#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "Utility.h"
//�ǂݍ��ރv���C���[�̈ʒu��������������t�@�C���̃p�X
const std::string PlayerDataEditor::loadFileName = "playerData";
/// <summary>
/// �v���C���[�̏����ʒu�̕ҏW
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor(loadFileName,InitObjKind::player)
{
    if (!editedPlacementDataVec.empty())//�t�@�C�����󂶂�Ȃ�������ҏW�I�u�W�F�N�g�Ɉʒu��n��
    {
        editObject->SetArrangementData(editedPlacementDataVec[0]);
    }
}

/// <summary>
/// �X�V
/// </summary>
void PlayerDataEditor::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    if (nowEditAction == EditActionKind::select && UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
    {
        //�X�y�[�X�L�[�ŕҏW�J�n
        nowEditAction = EditActionKind::edit;
    }
    else if (nowEditAction == EditActionKind::edit)
    {
        //�ړ���]
        editObject->Update(cameraObserever);
        //�ҏW�I��
        if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
        {
            nowEditAction = EditActionKind::select;
            PlacementData editData = editObject->GePlacementData();
            editData.objKind = CAST_I(editKind);
            //�v���C���[�͈�����Ȃ̂Ő擪�̂�
            if(editedPlacementDataVec.empty())
            {
                editedPlacementDataVec.push_back(editData);
            }
            else
            {
                editedPlacementDataVec[0] = editData;
            }
        }
    }
    UpdateNowEditObjData();
}
/// <summary>
/// �ҏW���A�ҏW�ς݂̃v���C���[��`��
/// </summary>
void PlayerDataEditor::Draw() const
{
    //�����ݕҏW���Ȃ�
    if (nowEditAction != EditActionKind::select)
    {
        //���ҏW���Ă���G�l�~�[
        drawer->SelectDraw(nowEditObjPlaceData);
    }
    else//�ҏW���Ă��Ȃ����Ƃ���
    {
        //�ҏW������Ȃ��Ă�editKind�Ɠ������̂�I�ڂ��Ƃ��Ă�����`��
        if (nowEditObjPlaceData.objKind == CAST_I(editKind))
        {
            drawer->SelectDraw(nowEditObjPlaceData);
        }
        else
        {
            drawer->Draw(nowEditObjPlaceData);
        }
    }
}