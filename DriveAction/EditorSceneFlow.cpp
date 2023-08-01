#include "EditorSceneFlow.h"
#include "DxLib.h"
#include "Utility.h"
#include "UserInput.h"
#include "StageObjectController.h"
#include "StageDataEditor.h"
#include "EnemyDataEditor.h"
#include "CollectItemDataEditor.h"
#include "PlayerDataEditor.h"
#include "EditorCamera.h"
#include "EffekseerForDXLib.h"
/// <summary>
/// �ҏW�̗���
/// </summary>
EditorSceneFlow::EditorSceneFlow()
{
    stage = new StageObjectController();
    editState = EditPlayer;
    enemyEditor = new EnemyDataEditor();
    playerEditor = new PlayerDataEditor();
    collectEditor = new CollectItemDataEditor();
    camera = new EditorCamera();
    nextSceneType=SceneType::TITLE;
    nowEditor = playerEditor;
    camera->Update();
    SetFontSize(fontSize);
}

EditorSceneFlow::~EditorSceneFlow()
{
    SAFE_DELETE(stage);
    SAFE_DELETE(enemyEditor);
    SAFE_DELETE(playerEditor);
    SAFE_DELETE(collectEditor);
    SAFE_DELETE(camera);
}
/// <summary>
/// �X�V
/// </summary>
void EditorSceneFlow::Update()
{
    //�J�����̍X�V
    camera->Update();
    if (UserInput::GetInputState(SKey) == Hold)
    {
        nowEditor->ChangeMissionNum();
    }
    //s��aKey�������ĂȂ��Ԃ͕ҏW
    else if (UserInput::GetInputState(AKey) != Hold)
    {
        //�ҏW
        nowEditor->Update();
        //�ҏW�����玟��
        if (nowEditor->IsEndEditing())
        {
            SelectEditKind();
        }
    }
    //�G�t�F�N�g�X�V
    Effekseer_Sync3DSetting();
    UpdateEffekseer3D();
}
/// <summary>
/// �`��
/// </summary>
void EditorSceneFlow::Draw() const
{
    //�X�e�[�W�ɔz�u����Ă��镨
    stage->Draw();
    //�ҏW�������̂�S���`��
    playerEditor->DrawAllEditedObject();
    collectEditor->DrawAllEditedObject();
    enemyEditor->DrawAllEditedObject();
    //���ݕҏW���Ă��镨
    nowEditor->DrawNowEditObject();
    //�����̕`��
    playerEditor->DrawEditString();
    collectEditor->DrawEditString();
    enemyEditor->DrawEditString();
    nowEditor->DrawSelectString();
    DrawEffekseer3D();
}
/// <summary>
/// ���ɉ���ҏW���邩
/// </summary>
void EditorSceneFlow::SelectEditKind()
{
    if (UserInput::GetInputState(Up) == Push) 
    {
        switch (editState)
        {
        case EditorSceneFlow::EditCollect:
            editState = EditPlayer;
            nowEditor = playerEditor;
            break;
        case EditorSceneFlow::EditEnemy:
            editState = EditCollect;
            nowEditor = collectEditor;
            break;
        }
    }
    else if (UserInput::GetInputState(Down) == Push)
    {
        switch (editState)
        {
        case EditorSceneFlow::EditCollect:
            editState = EditEnemy;
            nowEditor = enemyEditor;
            break;
        case EditorSceneFlow::EditPlayer:
            editState = EditCollect;
            nowEditor = collectEditor;
            break;
        }
    }
}
