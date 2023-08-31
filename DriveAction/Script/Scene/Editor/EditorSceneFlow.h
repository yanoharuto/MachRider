#pragma once
#include "SceneFlowBase.h"
#include <unordered_map>
class EditorCamera;
class StageDataEditor;
class PlayerDataEditor;
class EnemyDataEditor;
class CollectItemDataEditor;
class StageObjectController;
class EditManual;
class EditorEffect;
/// <summary>
/// �ҏW�����̗���
/// </summary>
class EditorSceneFlow :public SceneFlowBase
{
public:
    /// <summary>
    /// �ҏW�v���Z�X
    /// </summary>
    enum EditProcessState
    {
        //player�ҏW
        editPlayer,
        //���W�A�C�e���ҏW
        editCollect,
        //�G�ҏW
        editEnemy,
    };
    /// <summary>
    /// �ҏW�ɕK�v�Ȃ��̂��m��
    /// </summary>
    EditorSceneFlow();
    /// <summary>
    /// �ҏW����X�e�[�W�̔w�i�Ȃǂ����
    /// </summary>
    ~EditorSceneFlow();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw() const override;
private:
    /// <summary>
    /// �ҏW������̂�I��
    /// </summary>
    void SelectEditKind();
    //�X�e�[�W�̒[
    StageObjectController* stage;
    //�ҏW�ӏ�
    EditProcessState editState;
    //���ݕҏW���Ă��镨
    StageDataEditor* nowEditor;
    //�ҏW�������
    EditManual* manual;
    //�ҏW���ɏo�Ă���G�t�F�N�g�̍X�V��
    EditorEffect* editorEffect;
    //�J����
    EditorCamera* camera;
    //�ҏW�N���X�̂܂Ƃ�
    std::vector<StageDataEditor*> editorVec;
    //�ҏW�N���X�̔ԍ�
    int selectEditorNum = 0;
};

