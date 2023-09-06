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
#include "EditDataSaver.h"
//���ҏW���Ă���I�u�W�F�N�g�̃|�W�V����
PlacementData StageDataEditor::nowEditObjData = {};
/// ���W�A�C�e���̐�
int StageDataEditor::collectNum = 0;
/// ���W�A�C�e����������ǂ̃^�C�~���O�ŏo�Ă��邩
int StageDataEditor::getCollectNum = 0;

/// <summary>
///�X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
/// </summary>
/// <param name="setFileName">�ǂ̃t�@�C���ɕۑ����邩������</param>
StageDataEditor::StageDataEditor(std::string setFileName, InitObjKind objKind)
{
    editKind = objKind;
    //�������łɃt�@�C��������Ȃ�f�[�^������Ă���
    placementDataVec = FirstPositionGetter::CSVConvertFirstData(setFileName,objKind);
    //�ҏW�I�u�W�F�N�g
    editObject = new EditorObject();
    drawer = new EditorDrawModel(editKind);
}
/// <summary>
/// �`����ƕҏW�I�u�W�F�N�g�̉��
/// </summary>
StageDataEditor::~StageDataEditor()
{
    EditDataSaver dataSaver;
    dataSaver.SaveEditData(placementDataVec, editKind);
    //�`����폜
    SAFE_DELETE(drawer);
    //�ҏW�I�u�W�F�N�g
    SAFE_DELETE(editObject);
}
/// <summary>
/// �V�����ҏW������ߋ��ɕҏW�������̂��ĕҏW�����肷��
/// </summary>
void StageDataEditor::Update()
{
    if (nowEditAction == select)
    {
        SelectEditedObject();
        //�X�y�[�X�L�[�ŕҏW�J�n
        if(UserInput::GetInputState(Space) == Push)
        {
            //selectEditedNum��NEW_EDIT_NUM�ȊO�̐����������Ă���Ȃ�ĕҏW
            nowEditAction = selectEditedNum != NEW_EDIT_NUM ? reEdit : edit;
        }
    }
    else//SpaceKey�������ĕҏW���[�h�ɐ؂�ւ�
    {
        Edit();
    }
    //DKey���������獡�I�����Ă��镨���폜
    if (UserInput::GetInputState(DKey) == Push)
    {
        //�ĕҏW���悤�Ƃ��Ă�����
        if (nowEditAction != edit && selectEditedNum != NEW_EDIT_NUM)
        {
            //�ĕҏW���Ȃ炻����폜
            EraceEndEditData(selectEditedNum);
            selectEditedNum = NEW_EDIT_NUM;
        }
        nowEditAction = select;
    }
    UpdateNowEditObjData();

}
/// <summary>
/// �ҏW����ҏW���I�����I�u�W�F�N�g�̕`��
/// </summary>
void StageDataEditor::Draw() const
{
    if (!placementDataVec.empty())
    {
        //�ҏW�ς݂̃I�u�W�F�N�g�S�ĕ`��
        for (unsigned int i = 0; i < placementDataVec.size(); i++)
        {
            //�`�悷��I�u�W�F�N�g�̎��
            InitObjKind drawKind = static_cast<InitObjKind>(placementDataVec[i].objKind);
            //�ҏW�ς݂̃I�u�W�F�N�g�̔z�u�����
            PlacementData editData = placementDataVec[i];
            //DrawKind�̎�ނ̃I�u�W�F�N�g�̕`���
            drawer->Draw(editData);
        }
    }
    //�����ݕҏW���Ȃ�
    if (nowEditAction != select)
    {
        //�ҏW���̂��̂�\��
        auto editData = editObject->GePlacementData();
        drawer->SelectDraw(editData);
    }
    //�ҏW������Ȃ��Ă�editKind�Ɠ������̂�I�ڂ��Ƃ��Ă�����`��
    if (nowEditObjData.objKind == editKind)
    {
        drawer->SelectDraw(nowEditObjData);
    }
}
/// <summary>
/// ���ҏW���Ă���I�u�W�F�N�g�̃|�W�V����
/// </summary>
/// <returns></returns>
VECTOR StageDataEditor::GetEditObjPos()
{
    return  VGet(nowEditObjData.posX,0,nowEditObjData.posZ);
}
VECTOR StageDataEditor::GetEditObjDir()
{
    return VGet(nowEditObjData.dirX, 0, nowEditObjData.dirZ);
}
/// <summary>
/// ���Ԗڂ̃~�b�V�������ύX����
/// </summary>
void StageDataEditor::ChangeEditedCollectNum()
{
    if (UserInput::GetInputState(SKey) == Hold)
    {
        if (UserInput::GetInputState(Up) == Push)
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
        else if (UserInput::GetInputState(Down) == Push)
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
}
/// <summary>
/// �ҏW�ς݃f�[�^�̍폜
/// </summary>
/// <param name="eraceNum">�폜����̂͐擪���牽�Ԗڂ�</param>
void StageDataEditor::EraceEndEditData(int eraceNum)
{
    auto editData = placementDataVec.begin();
    editData += eraceNum;
    placementDataVec.erase(editData);
}

/// <summary>
/// �ҏW����
/// </summary>
void StageDataEditor::Edit()
{
    //�ړ���]
    editObject->Update();
    //�X�y�[�X�L�[����������
    if (UserInput::GetInputState(Space) == Push)
    {
        //�ҏW�����I�u�W�F�N�g�̈ʒu�ƌ����Ǝ��
        PlacementData editData = editObject->GePlacementData();
        editData.objKind = editKind;
        //���ڂ̃A�C�e��������������ŏo�Ă��邩�ݒ肷��
        editData.collectNum = getCollectNum;
        //�ߋ��ɕҏW���Ă����I�u�W�F�N�g���ĕҏW���Ă�����
        if (nowEditAction == reEdit)
        {
            //�z�u�����ĕۑ�
            placementDataVec[selectEditedNum] = editData;
            selectEditedNum = NEW_EDIT_NUM;
        }
        else
        {
            //�V�����ҏW�I�u�W�F�N�g���R���e�i�ɔ[�i
            placementDataVec.push_back(editData);
        }
        //�X�y�[�X�L�[����������ҏW�I��
        nowEditAction = select;
    }
}
/// <summary>
/// NowEditObjData�����o�ϐ����X�V����
/// </summary>
void StageDataEditor::UpdateNowEditObjData()
{
    //�J�����Ɍ���ׂ��I�u�W�F�N�g��`����
    nowEditObjData = editObject->GePlacementData();
    nowEditObjData.objKind = static_cast<int>(editKind);
}
/// <summary>
/// �ҏW�ς݂̃I�u�W�F�N�g��I������
/// </summary>
void StageDataEditor::SelectEditedObject()
{
    //�ҏW�ς݃A�C�e��������Ȃ�
    if (!placementDataVec.empty())
    {
        int prevNum = selectEditedNum;
        //���L�[�ŌÂ��ۑ����ꂽ�I�u�W�F�N�g�������o����悤�ɂȂ�
        if (UserInput::GetInputState(Left) == Push)
        {
            selectEditedNum--;
            //-1��������V������낤�Ƃ��Ă���
            if (selectEditedNum < 0)
            {
                selectEditedNum = NEW_EDIT_NUM;
                return;
            }
        }
        //�E�L�[�ň�ԐV�����ۑ����ꂽ�I�u�W�F�N�g�������o����悤�ɂȂ�
        else if (UserInput::GetInputState(Right) == Push) 
        {
            selectEditedNum++;
            //�ߋ��ɕҏW�����A�C�e���̐���菭�Ȃ��Ȃ��Ă��邩
            if (selectEditedNum >= static_cast<int>(placementDataVec.size()))
            {
                selectEditedNum = placementDataVec.size() - 1;
            }
        }
        //�ߋ��̃A�C�e�������E�L�[�őI��������
        if (selectEditedNum != prevNum)
        {
            //�ߋ��ɕҏW�����f�[�^������
            PlacementData editedData = placementDataVec[selectEditedNum];
            editObject->SetArrangementData(editedData);
            getCollectNum = editedData.collectNum;
        }
    }
}