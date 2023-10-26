#include "EditorManager.h"
#include "DxLib.h"
#include "Utility.h"
#include "UserInput.h"
#include "StageObjectController.h"
#include "StageDataEditor.h"
#include "EnemyDataEditor.h"
#include "CollectItemDataEditor.h"
#include "PlayerDataEditor.h"
#include "EffekseerForDXLib.h"
#include "EditManual.h"
#include "EditorEffect.h"
#include "CameraObserver.h"
#include "EditDataSaver.h"
/// <summary>
/// �ҏW�ɕK�v�Ȃ��̂��m��
/// </summary>
EditorManager::EditorManager()
{
    //�w�i
    stage = new StageObjectController();
    //�e�I�u�W�F�N�g��Editor
    editorVec.push_back(std::make_shared<PlayerDataEditor>());
    editorVec.push_back(std::make_shared<CollectItemDataEditor>());
    editorVec.push_back(std::make_shared<EnemyDataEditor>(InitObjKind::saw));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(InitObjKind::moveSaw));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(InitObjKind::circleLaserShip));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(InitObjKind::upDownLaserShip));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(InitObjKind::bomberShip));
    //���݂̕ҏW�N���X
    nowEditor = editorVec[0];
}
/// <summary>
/// �ҏW����X�e�[�W�̔w�i�Ȃǂ����
/// </summary>
EditorManager::~EditorManager()
{
    EditDataSaver* dataSaver = new EditDataSaver();
    SAFE_DELETE(stage);
    for (unsigned int i = 0; i < editorVec.size(); i++)
    {
        dataSaver->SaveEditData(editorVec[i]);
        editorVec[i].reset();
    }
    SAFE_DELETE(dataSaver);
}
/// <summary>
/// �ҏW�����ނ�e�ҏW���̕ҏW
/// </summary>
void EditorManager::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    //skey�ŏo�Ă���^�C�~���O��ύX
    if (UserInput::GetInputState(UserInput::KeyInputKind::SKey) == UserInput::InputState::Hold)
    {
        nowEditor->ChangeEditedCollectNum();
    }
    else//s��aKey�������ĂȂ��Ԃ͕ҏW
    {
        //���Ȃɂ��ҏW���Ă��Ȃ��Ȃ�
        if (nowEditor->IsEndEditing())
        {
            //�ҏW����I�u�W�F�N�g�̎�ނ�ύX
            SelectEditKind();
        }
        //�ҏW
        nowEditor->Update(cameraObserever);
    }
}
/// <summary>
/// �`��
/// </summary>
void EditorManager::Draw(std::weak_ptr<CameraObserver> cameraObserever) const
{
    //�X�e�[�W�ɔz�u����Ă��镨
    stage->Draw(cameraObserever);
    //�e�I�u�W�F�N�g�̕`��
    for (unsigned int i = 0; i < editorVec.size(); i++)
    {
        editorVec[i]->Draw();
    }
    //�G�t�F�N�g
    DrawEffekseer3D();
}
/// <summary>
/// �ҏW�����ǂ�����Ԃ�
/// </summary>
/// <returns>�ҏW���Ȃ�True</returns>
bool EditorManager::IsNowEdit() const
{
    return nowEditor->IsNowEdit();
}
/// <summary>
/// �ҏW���̈ʒu����������L
/// </summary>
PlacementData EditorManager::GetNowEditObjPlaceData() const
{
    return nowEditor->GetNowEditObjPlaceData();
}
/// <summary>
/// ���ɉ���ҏW���邩�I������
/// </summary>
void EditorManager::SelectEditKind()
{
    //�㉺�L�[�ŕҏW�ł���I�u�W�F�N�g�̎�ނ�ύX
    if (UserInput::GetInputState(UserInput::KeyInputKind::Up) == UserInput::InputState::Push) 
    {
        selectEditorNum--;
        //�����������Ɍq����
        if (selectEditorNum < 0)
        {
            selectEditorNum = editorVec.size() - 1;
        }
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Down) == UserInput::InputState::Push)
    {
        selectEditorNum++;
        //����������ԑO�Ɍq����
        if (selectEditorNum > static_cast<int>(editorVec.size() - 1))
        {
            selectEditorNum = 0;
        }
    }
    //���ݕҏW���̃G�f�B�^�[���X�V
    nowEditor = editorVec[selectEditorNum];
}