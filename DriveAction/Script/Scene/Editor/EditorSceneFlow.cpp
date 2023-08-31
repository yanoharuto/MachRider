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
#include "EditManual.h"
#include "EditorEffect.h"
/// <summary>
/// �ҏW�ɕK�v�Ȃ��̂��m��
/// </summary>
EditorSceneFlow::EditorSceneFlow()
{
    //�w�i
    stage = new StageObjectController();
    editState = editPlayer;
    //�e�I�u�W�F�N�g��Editor
    editorVec.push_back(new PlayerDataEditor());
    editorVec.push_back(new CollectItemDataEditor());
    editorVec.push_back(new EnemyDataEditor(saw));
    editorVec.push_back(new EnemyDataEditor(moveSaw));
    editorVec.push_back(new EnemyDataEditor(circleLaserShip));
    editorVec.push_back(new EnemyDataEditor(upDownLaserShip));
    editorVec.push_back(new EnemyDataEditor(bomberShip));
    //�J����
    camera = new EditorCamera();
    camera->Update();
    //�Ƃ肠�����^�C�g���ɖ߂�悤�ɂ���
    nextSceneType=SceneType::TITLE;
    //���݂̕ҏW�N���X
    nowEditor = editorVec[0];
    //�����������
    manual = new EditManual();
    //�G�t�F�N�g
    editorEffect = new EditorEffect();
}
/// <summary>
/// �ҏW����X�e�[�W�̔w�i�Ȃǂ����
/// </summary>
EditorSceneFlow::~EditorSceneFlow()
{
    SAFE_DELETE(stage);
    SAFE_DELETE(manual);
    SAFE_DELETE(editorEffect);
    for (int i = 0; i < editorVec.size(); i++)
    {
        SAFE_DELETE(editorVec[i]);
    }
    SAFE_DELETE(camera);
}
/// <summary>
/// �X�V
/// </summary>
void EditorSceneFlow::Update()
{
    //�J�����̍X�V
    camera->Update();
    //Skey�ŏo�Ă���^�C�~���O��ύX
    if (UserInput::GetInputState(SKey) == Hold)
    {
        nowEditor->ChangeEditedCollectNum();
    }
    //s��aKey�������ĂȂ��Ԃ͕ҏW
    else if (UserInput::GetInputState(AKey) != Hold)
    {
        //���Ȃɂ��ҏW���Ă��Ȃ��Ȃ�
        if (nowEditor->IsEndEditing())
        {
            //�ҏW����I�u�W�F�N�g�̎�ނ�ύX
            SelectEditKind();
        }
        //�ҏW
        nowEditor->Update();
    }

    //�G�t�F�N�g�X�V
    editorEffect->Update(nowEditor);
    Effekseer_Sync3DSetting();
    //�G�t�F�N�g�X�V
    UpdateEffekseer3D();
}
/// <summary>
/// �`��
/// </summary>
void EditorSceneFlow::Draw() const
{
    //�X�e�[�W�ɔz�u����Ă��镨
    stage->Draw();
    //�e�I�u�W�F�N�g�̕`��
    for (int i = 0; i < editorVec.size(); i++)
    {
        editorVec[i]->Draw();
    }
    //�������
    manual->Draw(nowEditor);
    //�G�t�F�N�g
    DrawEffekseer3D();
}
/// <summary>
/// ���ɉ���ҏW���邩�I������
/// </summary>
void EditorSceneFlow::SelectEditKind()
{
    //�㉺�L�[�ŕҏW�ł���I�u�W�F�N�g�̎�ނ�ύX
    if (UserInput::GetInputState(Up) == Push) 
    {
        selectEditorNum--;
        //�����������Ɍq����
        if (selectEditorNum < 0)
        {
            selectEditorNum = editorVec.size() - 1;
        }
    }
    else if (UserInput::GetInputState(Down) == Push)
    {
        selectEditorNum++;
        //����������ԑO�Ɍq����
        if (selectEditorNum > editorVec.size() - 1)
        {
            selectEditorNum = 0;
        }
    }
    //���ݕҏW���̃G�f�B�^�[���X�V
    nowEditor = editorVec[selectEditorNum];
}