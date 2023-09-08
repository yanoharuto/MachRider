#pragma once
#include <unordered_map>
#include <memory>
#include <iostream>
#include "EditObjectData.h"
class StageDataEditor;
class StageObjectController;
class EditorCameraObserver;

/// <summary>
/// �ҏW�����̗���
/// </summary>
class EditorManager final
{
public:
    /// <summary>
    /// �ҏW�ɕK�v�Ȃ��̂��m��
    /// </summary>
    EditorManager();
    /// <summary>
    /// �ҏW����X�e�[�W�̔w�i�Ȃǂ����
    /// </summary>
    ~EditorManager();
    /// <summary>
    /// �ҏW�����ނ�e�ҏW���̕ҏW
    /// </summary>
    void Update(std::weak_ptr<EditorCameraObserver> cameraObserever);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw() const;
    /// <summary>
    /// �ҏW�����ǂ�����Ԃ�
    /// </summary>
    /// <returns>�ҏW���Ȃ�True</returns>
    bool IsNowEdit() const;
    /// <summary>
    /// �ҏW���̈ʒu����������L
    /// </summary>
    PlacementData GetNowEditObjPlaceData()const;
private:
    /// <summary>
    /// �ҏW������̂�I��
    /// </summary>
    void SelectEditKind();
    //�X�e�[�W�̒[
    StageObjectController* stage;
    //���ݕҏW���Ă��镨
    std::shared_ptr<StageDataEditor> nowEditor;
    //�ҏW�N���X�̂܂Ƃ�
    std::vector<std::shared_ptr<StageDataEditor>> editorVec;
    //�ҏW�N���X�̔ԍ�
    int selectEditorNum = 0;
};