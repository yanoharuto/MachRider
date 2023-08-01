#include "CollectItemDataEditor.h"
#include "EditorObject.h"
#include "UserInput.h"
#include "Utility.h"
#include "EditorModelViewer.h"
/// <summary>
/// ���W�A�C�e���̕ҏW����N���X
/// </summary>
CollectItemDataEditor::CollectItemDataEditor()
    :StageDataEditor("collectData.csv")
{
    nowEditCollect = new EditorObject(ObjectInit::collect);
    viewer = new EditorModelViewer(ObjectInit::collect);
}

CollectItemDataEditor::~CollectItemDataEditor()
{
    for (int i = 0; i < editDataVec.size(); i++)
    {
        SaveEditObjectData(editDataVec[i]);
    }
    SAFE_DELETE(nowEditCollect);
    SAFE_DELETE(viewer);
}
/// <summary>
/// �X�V
/// </summary>
void CollectItemDataEditor::Update()
{
    if (isEndEdit)
    {

        SelectEditedCollect();
        //�X�y�[�X�L�[�ŕҏW�J�n
        isEndEdit = UserInput::GetInputState(Space) != Push;
    }
    else if (!isEndEdit)//�ҏW��
    {
        //�ړ���]
        nowEditCollect->Update();
        //�ҏW�I��
        if (UserInput::GetInputState(Space) == Push)
        {
            isEndEdit = true;
            //���W�A�C�e���̏��
            auto editData = nowEditCollect->GetEditObjectData();
            //�ۑ�
            if (selectEditedCollectNum != -1)
            {
                editDataVec[selectEditedCollectNum] = editData;
                selectEditedCollectNum = -1;
            }
            else
            {
                editDataVec.push_back(editData);
            }
        }
        //�j��
        else if (UserInput::GetInputState(DKey) == Push)
        {
            if (selectEditedCollectNum != -1)//�̕ҏW�������̂�j��
            {
                EraceEndEditData(selectEditedCollectNum);
                selectEditedCollectNum = -1;
            }
            isEndEdit = true;
        }
    }
    //���W�A�C�e���̐��𑼂�Editor�ɂ����f
    if (!editDataVec.empty())
    {
        collectNum = editDataVec.size() - 1;
        collectNum = collectNum < 0 ? 0 : collectNum;
    }

    //�J�����Ɍ���ׂ��I�u�W�F�N�g��`����
    nowEditObjData = nowEditCollect->GetEditObjectData();
    UpdateEffect();
}
/// <summary>
/// �ҏW�ς݂̃I�u�W�F�N�g��`��
/// </summary>
void CollectItemDataEditor::DrawAllEditedObject() const
{
    if (!editDataVec.empty())
    {
        for (int i = 0; i < editDataVec.size(); i++)
        {
            viewer->Draw(editDataVec[i]);
        }
    }
}
/// <summary>
/// ���ݕҏW���Ă��镨��`��
/// </summary>
void CollectItemDataEditor::DrawNowEditObject() const
{
    viewer->SelectDraw(nowEditCollect->GetEditObjectData());
}
/// <summary>
/// ������`��
/// </summary>
void CollectItemDataEditor::DrawEditString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), GetColor(0, 0, 0));
    //���W�A�C�e���̐�
    DrawString(0, drawCollectNumY, std::to_string(collectNum).c_str(), GetColor(0, 0, 0));
    //�~�b�V�����̐�
    DrawString(0, drawMissionNumY, std::to_string(missionNum).c_str(), GetColor(0, 0, 0));
}
/// <summary>
/// �I������Ă���Ƃ��̕�����`��
/// </summary>
void CollectItemDataEditor::DrawSelectString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), selectColor);
}

/// <summary>
/// �ҏW�����ߋ��̎��W�A�C�e�����ĕҏW�ł���悤�ɂ���
/// </summary>
void CollectItemDataEditor::SelectEditedCollect()
{
    //�ҏW�ς݃A�C�e��������Ȃ�
    if (!editDataVec.empty())
    {
        int prevNum = selectEditedCollectNum;
        //���E�L�[�ōĕҏW������̂�ύX
        if (UserInput::GetInputState(Left) == Push) selectEditedCollectNum--;
        else if (UserInput::GetInputState(Right) == Push) selectEditedCollectNum++;
        //�ߋ��̃A�C�e�����㉺�L�[�őI��������
        if (selectEditedCollectNum > -1 && selectEditedCollectNum != prevNum)
        {
            //�ߋ��ɕҏW�����A�C�e���̐���菭�Ȃ��Ȃ��Ă��邩
            if (selectEditedCollectNum >= editDataVec.size())
            {    
                selectEditedCollectNum = editDataVec.size() - 1;
            }
            //�ߋ��ɕҏW�����f�[�^������
            auto editedData = editDataVec[selectEditedCollectNum];
            SAFE_DELETE(nowEditCollect);
            nowEditCollect = new EditorObject(editedData);
        }
        else if(selectEditedCollectNum < -1)//-1��������V������낤�Ƃ��Ă���
        {
            selectEditedCollectNum = -1;
        }
    }
}
