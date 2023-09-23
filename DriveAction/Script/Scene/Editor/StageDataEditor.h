#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
//�V�����ҏW���Ȃ�selectEditNum��-1
#define NEW_EDIT_NUM -1

class EditorObject;
class EditorDrawModel;
class CameraObserver;
enum ActionKind;
using namespace ObjectInit;
/// <summary>
/// �X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
/// </summary>
class StageDataEditor abstract
{

public:
    /// <summary>
    ///�X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
    /// </summary>
    /// <param name="setFileName">�ǂ̃t�@�C���ɕۑ����邩������</param>
    StageDataEditor(std::string setFileName,InitObjKind objKind);
    /// <summary>
    /// �`����ƕҏW�I�u�W�F�N�g�̉��
    /// </summary>
    virtual ~StageDataEditor();
    /// <summary>
    /// �V�����ҏW������ߋ��ɕҏW�������̂��ĕҏW�����肷��
    /// </summary>
    virtual void Update(std::weak_ptr<CameraObserver> cameraObserever);
    /// <summary>
    /// �ҏW����ҏW���I�����I�u�W�F�N�g�̕`��
    /// </summary>
    virtual void Draw()const;
    /// <summary>
    /// �ҏW���I��������
    /// </summary>
    /// <returns>�ҏW���I��������True</returns>
    bool IsEndEditing()const 
    {
        return nowEditAction == EditActionKind::select; 
    };
    /// <summary>
    /// �ҏW���Ă���I�u�W�F�N�g�̔z�u���
    /// </summary>
    /// <returns>�ҏW���Ă���I�u�W�F�N�g�̔z�u���</returns>
    PlacementData GetEditObjPlacementData()const;
    /// <summary>
    /// �ҏW�����ǂ�����Ԃ�
    /// </summary>
    /// <returns>�ҏW���Ȃ�True</returns>
    bool IsNowEdit();
    /// <summary>
    /// ���ݕҏW���Ă���A�C�e���̏o�Ă���^�C�~���O��ύX
    /// </summary>
    void ChangeEditedCollectNum();
    //�ҏW�ōs����
    enum class EditActionKind
    {
        //�ҏW��
        edit,
        //�ĕҏW��
        reEdit,
        //�ҏW���邩�ĕҏW���邩�I��
        select,
    };
protected:
    /// <summary>
    /// �ҏW�ς݃f�[�^�̍폜
    /// </summary>
    /// <param name="eraceNum">�폜����̂͐擪���牽�Ԗڂ�</param>
    void EraceEndEditData(int eraceNum);
    /// <summary>
    /// �ҏW�ς݂̃I�u�W�F�N�g��I������
    /// </summary>
    void SelectEditedObject();
    /// <summary>
    /// �ҏW����
    /// </summary>
    void Edit(std::weak_ptr<CameraObserver> cameraObserever);
    /// <summary>
    /// NowEditObjData�����o�ϐ����X�V����
    /// </summary>
    void UpdateNowEditObjData();
    
    //���ҏW���Ă���I�u�W�F�N�g�̏��
    static PlacementData nowEditObjPlaceData;
    // �ҏW�������G�l�~�[�̎��
    InitObjKind editKind = InitObjKind::saw;
    //�ҏW�I���t���O
    EditActionKind nowEditAction = EditActionKind::select;
    //���ݕҏW���̃I�u�W�F�N�g
    EditorObject* editObject;
    /// ���W�A�C�e���̐�
    static int collectNum;  
    /// ���W�A�C�e����������ǂ̃^�C�~���O�ŏo�Ă��邩
    static int getCollectNum;
    //�I�u�W�F�N�g�̕`��S��
    EditorDrawModel* drawer;
    //�ҏW�ς݃f�[�^
    std::vector<PlacementData> placementDataVec;
    //�ҏW�ς݂̕������E�L�[�őI�ڂ��Ƃ���ƕϓ�
    int selectEditedNum = -1;
};