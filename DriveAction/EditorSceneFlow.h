#pragma once
#include "SceneFlowBase.h"
#include <unordered_map>
class EditorCamera;
class StageDataEditor;
class PlayerDataEditor;
class EnemyDataEditor;
class CollectItemDataEditor;
class StageObjectController;

/// <summary>
/// �ҏW�����̗���
/// </summary>
class EditorSceneFlow:public SceneFlowBase
{
public:
    /// <summary>
    /// �ҏW�v���Z�X
    /// </summary>
    enum EditProcessState
    {
        //player�ҏW
        EditPlayer,
        //���W�A�C�e���ҏW
        EditCollect,
        //�G�ҏW
        EditEnemy,
    };
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EditorSceneFlow();

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
    //�`�悷�镶���̃T�C�Y
    const int fontSize = 124;
    //�X�e�[�W�̒[
    StageObjectController* stage;
    //�ҏW�ӏ�
    EditProcessState editState;
    //���ݕҏW���Ă��镨
    StageDataEditor* nowEditor;
    //�J����
    EditorCamera* camera;
    //�G�l�~�[�ҏW�N���X
    EnemyDataEditor* enemyEditor;
    //�v���C���[�ҏW�N���X
    PlayerDataEditor* playerEditor;
    //���W�A�C�e���ҏW�N���X
    CollectItemDataEditor* collectEditor;
};

