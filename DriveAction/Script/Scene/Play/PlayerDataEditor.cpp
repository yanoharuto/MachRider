#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "Utility.h"
//�ǂݍ��ރv���C���[�̈ʒu��������������t�@�C���̃p�X
const std::string PlayerDataEditor::loadEditFilePath = "playerData.csv";
/// <summary>
/// �v���C���[�̏����ʒu�̕ҏW
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor(loadEditFilePath,player)
{
    if (!placementDataVec.empty())
    {
        editObject->SetArrangementData(placementDataVec[0]);
    }
    
}

/// <summary>
/// �X�V
/// </summary>
void PlayerDataEditor::Update(std::weak_ptr<EditorCameraObserver> cameraObserever)
{
    if (nowEditAction == select && UserInput::GetInputState(Space) == Push)
    {
        //�X�y�[�X�L�[�ŕҏW�J�n
        nowEditAction = edit;
    }
    else if (nowEditAction == edit)
    {
        //�ړ���]
        editObject->Update(cameraObserever);
        //�ҏW�I��
        if (UserInput::GetInputState(Space) == Push)
        {
            nowEditAction = select;
            PlacementData editData = editObject->GePlacementData();
            editData.objKind = editKind;
            if(placementDataVec.empty())
            {
                placementDataVec.push_back(editData);
            }
            else
            {
                placementDataVec[0] = editData;
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
    if (nowEditAction != select)
    {
        //���ҏW���Ă���G�l�~�[
        drawer->SelectDraw(nowEditObjPlaceData);
    }
    else//�ҏW���Ă��Ȃ����Ƃ���
    {
        //�ҏW������Ȃ��Ă�editKind�Ɠ������̂�I�ڂ��Ƃ��Ă�����`��
        if (nowEditObjPlaceData.objKind == editKind)
        {
            drawer->SelectDraw(nowEditObjPlaceData);
        }
        else
        {
            drawer->Draw(nowEditObjPlaceData);
        }
    }
}