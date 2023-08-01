#pragma once
#include "StageDataEditor.h"
#include <unordered_map>
#include <vector>

class EnemyDataEditor :
    public StageDataEditor
{
public:
    EnemyDataEditor();
    ~EnemyDataEditor();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// �ҏW�ς݂̃I�u�W�F�N�g��`��
    /// </summary>
    void DrawAllEditedObject()const override;
    /// <summary>
    /// ���ݕҏW���Ă��镨��`��
    /// </summary>
    void DrawNowEditObject()const override;
    /// <summary>
    /// ������`��
    /// </summary>
    void DrawEditString() const override;
    /// <summary>
    /// �I������Ă���Ƃ��̕�����`��
    /// </summary>
    void DrawSelectString()const override;
private:
    /// <summary>
    /// �ҏW����G�l�~�[��I��
    /// </summary>
    void SelectEnemy();
    /// <summary>
    /// �ҏW����ߋ��̃G�l�~�[��I��
    /// </summary>
    void SelectEditedEnemy();
    
    /// <summary>
    /// �e�G�l�~�[�̕`��S����
    /// </summary>
    std::unordered_map<ObjectInit::InitObjKind,EditorModelViewer*> eneViewerMap;
    /// <summary>
    /// ���ݕҏW���Ă���G�l�~�[
    /// </summary>
    EditorObject* nowEditEne;
    /// <summary>
    /// �ҏW�������G�l�~�[�̎��
    /// </summary>
    ObjectInit::InitObjKind kind = ObjectInit::saw;
    //�G�f�B�^�[�̖��O�̈ʒu
    const int drawStrY = 800;
    //�G�f�B�^�[�̐F
    const unsigned int selectColor = GetColor(0, 255, 0);
    //�G�f�B�^�[�̖��O
    const std::string drawEditString = "Enemy"; 
    //�I�����Ă���ҏW�ς݃G�l�~�[�̔ԍ� 
    int selectEditedEneNum = -1;
    //�ҏW�ς݃G�l�~�[��I�𒆂�
    bool isSelectEditedEne = false;
};