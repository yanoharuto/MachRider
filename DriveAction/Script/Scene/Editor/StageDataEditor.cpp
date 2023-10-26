#include <fstream>
#include <string>
#include "StageDataEditor.h"
#include "UserInput.h"
#include "EditObjectData.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "EditorObject.h"
#include "EditorDrawModel.h"
#include "Utility.h"
#include "StageDataManager.h"
//���ҏW���Ă���I�u�W�F�N�g�̃|�W�V����
PlacementData StageDataEditor::nowEditObjPlaceData = {};
/// ���W�A�C�e���̐�
int StageDataEditor::collectNum = 0;
/// ���W�A�C�e����������ǂ̃^�C�~���O�ŏo�Ă��邩
int StageDataEditor::getCollectNum = 0;
//�ҏW�t�@�C���u����
const std::string StageDataEditor::editFilePath = "data/editFile/";
/// <summary>
///�X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
/// </summary>
/// <param name="setFileName">�ǂ̃t�@�C���ɕۑ����邩������</param>
StageDataEditor::StageDataEditor(std::string setFileName, InitObjKind objKind)
{
    editKind = objKind;
    auto a = StageDataManager::IsExistFile(editFilePath + setFileName + Utility::JSON_FILE);
    //�������łɃt�@�C��������Ȃ�f�[�^������Ă���
    editedPlacementDataVec = FirstPositionGetter::GetPlaceData(editFilePath + setFileName,objKind);
    //�ҏW�I�u�W�F�N�g
    editObject = new EditorObject();
    drawer = new EditorDrawModel(editKind);
}
/// <summary>
/// �`����ƕҏW�I�u�W�F�N�g�̉��
/// </summary>
StageDataEditor::~StageDataEditor()
{
    //�`����폜
    SAFE_DELETE(drawer);
    //�ҏW�I�u�W�F�N�g
    SAFE_DELETE(editObject);
}
/// <summary>
/// �V�����ҏW������ߋ��ɕҏW�������̂��ĕҏW�����肷��
/// </summary>
void StageDataEditor::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    if (nowEditAction == EditActionKind::select)
    {
        SelectEditedObject();
        //�X�y�[�X�L�[�ŕҏW�J�n
        if(UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
        {
            //selectEditedNum��NEW_EDIT_NUM�ȊO�̐����������Ă���Ȃ�ĕҏW
            nowEditAction = selectEditedNum != NEW_EDIT_NUM ? EditActionKind::reEdit : EditActionKind::edit;
        }
    }
    else//�ҏW���[�h
    {
        Edit(cameraObserever);
    }
    //DKey���������獡�I�����Ă��镨���폜
    if (UserInput::GetInputState(UserInput::KeyInputKind::DKey) == UserInput::InputState::Push)
    {
        //�ĕҏW���悤�Ƃ��Ă�����
        if (nowEditAction != EditActionKind::edit && selectEditedNum != NEW_EDIT_NUM)
        {
            //�ĕҏW���Ȃ炻����폜
            EraceEndEditData(selectEditedNum);
            selectEditedNum = NEW_EDIT_NUM;
        }
        nowEditAction = EditActionKind::select;
    }
    UpdateNowEditObjData();

}
/// <summary>
/// �ҏW����ҏW���I�����I�u�W�F�N�g�̕`��
/// </summary>
void StageDataEditor::Draw() const
{
    if (!editedPlacementDataVec.empty())
    {
        //�ҏW�ς݂̃I�u�W�F�N�g�S�ĕ`��
        for (unsigned int i = 0; i < editedPlacementDataVec.size(); i++)
        {
            //�`�悷��I�u�W�F�N�g�̎��
            InitObjKind drawKind = static_cast<InitObjKind>(editedPlacementDataVec[i].objKind);
            //�ҏW�ς݂̃I�u�W�F�N�g�̔z�u�����
            PlacementData editData = editedPlacementDataVec[i];
            //DrawKind�̎�ނ̃I�u�W�F�N�g�̕`���
            drawer->Draw(editData);
        }
    }
    //�����ݕҏW���Ȃ�
    if (nowEditAction != EditActionKind::select)
    {
        //�ҏW���̂��̂�\��
        auto editData = editObject->GePlacementData();
        drawer->SelectDraw(editData);
    }
    //�ҏW������Ȃ��Ă�editKind�Ɠ������̂�I�ڂ��Ƃ��Ă�����`��
    if (nowEditObjPlaceData.objKind == CAST_I(editKind))
    {
        drawer->SelectDraw(nowEditObjPlaceData);
    }
}


/// <summary>
/// ���ݕҏW���Ă���A�C�e���̏o�Ă���^�C�~���O��ύX
/// </summary>
void StageDataEditor::ChangeEditedCollectNum()
{
    if (UserInput::GetInputState(UserInput::KeyInputKind::Up) == UserInput::InputState::Push)
    {
        //���W�A�C�e���̐���葽���Ȃ�Ȃ�
        if (getCollectNum + 1 > collectNum)
        {
            getCollectNum = collectNum;
        }
        else
        {
            getCollectNum++;
        }
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Down) == UserInput::InputState::Push)
    {
        //0��菭�Ȃ��Ȃ�Ȃ�
        if (getCollectNum - 1 < 0)
        {
            getCollectNum = 0;
        }
        else
        {
            getCollectNum--;
        }
    }
}
/// <summary>
/// �ҏW�ς݃f�[�^�̍폜
/// </summary>
/// <param name="eraceNum">�폜����̂͐擪���牽�Ԗڂ�</param>
void StageDataEditor::EraceEndEditData(int eraceNum)
{
    auto editData = editedPlacementDataVec.begin();
    editData += eraceNum;
    editedPlacementDataVec.erase(editData);
}

/// <summary>
/// �ҏW����
/// </summary>
void StageDataEditor::Edit(std::weak_ptr<CameraObserver> cameraObserever)
{
    //�ړ���]
    editObject->Update(cameraObserever);
    //�X�y�[�X�L�[����������
    if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
    {
        //�ҏW�����I�u�W�F�N�g�̈ʒu�ƌ����Ǝ��
        PlacementData editData = editObject->GePlacementData();
        editData.objKind = CAST_I(editKind);
        //���ڂ̃A�C�e��������������ŏo�Ă��邩�ݒ肷��
        editData.collectNum = getCollectNum;
        //�ߋ��ɕҏW���Ă����I�u�W�F�N�g���ĕҏW���Ă�����
        if (nowEditAction == EditActionKind::reEdit)
        {
            //�z�u�����ĕۑ�
            editedPlacementDataVec[selectEditedNum] = editData;
            selectEditedNum = NEW_EDIT_NUM;
        }
        else
        {
            //�V�����ҏW�I�u�W�F�N�g���R���e�i�ɔ[�i
            editedPlacementDataVec.push_back(editData);
        }
        //�X�y�[�X�L�[����������ҏW�I��
        nowEditAction = EditActionKind::select;
    }
}
/// <summary>
/// NowEditObjData�����o�ϐ����X�V����
/// </summary>
void StageDataEditor::UpdateNowEditObjData()
{
    //�J�����Ɍ���ׂ��I�u�W�F�N�g��`����
    nowEditObjPlaceData = editObject->GePlacementData();
    nowEditObjPlaceData.objKind = static_cast<int>(editKind);
}
/// <summary>
/// �ҏW�ς݂̃I�u�W�F�N�g��I������
/// </summary>
void StageDataEditor::SelectEditedObject()
{
    //�ҏW�ς݃A�C�e��������Ȃ�
    if (!editedPlacementDataVec.empty())
    {
        int prevNum = selectEditedNum;
        //���L�[�ŌÂ��ۑ����ꂽ�I�u�W�F�N�g�������o����悤�ɂȂ�
        if (UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Push)
        {
            selectEditedNum--;
            //-1��������V������낤�Ƃ��Ă���
            if (selectEditedNum < 0)
            {
                selectEditedNum = NEW_EDIT_NUM;
                return;//�����𒆒f����
            }
        }
        //�E�L�[�ň�ԐV�����ۑ����ꂽ�I�u�W�F�N�g�������o����悤�ɂȂ�
        else if (UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Push)
        {
            selectEditedNum++;
            //�ߋ��ɕҏW�����A�C�e���̐���菭�Ȃ��Ȃ��Ă��邩
            if (selectEditedNum >= static_cast<int>(editedPlacementDataVec.size()))
            {
                selectEditedNum = editedPlacementDataVec.size() - 1;
            }
        }
        //�ߋ��̃A�C�e�������E�L�[�őI��������
        if (selectEditedNum != prevNum)
        {
            //�ߋ��ɕҏW�����f�[�^������
            PlacementData editedData = editedPlacementDataVec[selectEditedNum];
            editObject->SetArrangementData(editedData);
            getCollectNum = editedData.collectNum;
        }
    }
}