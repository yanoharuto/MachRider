#pragma once
#include <string>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
class EditorObject;
class EditorModelViewer;
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
    StageDataEditor(std::string setFileName);
    ~StageDataEditor();
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update() = 0;
    /// <summary>
    /// �ҏW�I���I�u�W�F�N�g�̕`��
    /// </summary>
    virtual void DrawAllEditedObject()const {};
    /// <summary>
    /// �����ݕҏW���̃I�u�W�F�N�g�̕`��
    /// </summary>
    virtual void DrawNowEditObject()const = 0;
    /// <summary>
    /// �ҏW���I��������
    /// </summary>
    /// <returns></returns>
    bool IsEndEditing()const { return isEndEdit; };
    /// <summary>
    /// ���ҏW���Ă���I�u�W�F�N�g�̃|�W�V����
    /// </summary>
    /// <returns></returns>
    static VECTOR GetEditObjPos();
    /// <summary>
    /// ���ݕҏW���Ă���A�C�e���̏o�Ă���^�C�~���O��ύX
    /// </summary>
    void ChangeMissionNum();
    /// <summary>
    /// �ҏW�ς݃f�[�^�̍폜
    /// </summary>
    /// <param name="eraceNum">�폜����̂͐擪���牽�Ԗڂ�</param>
    void EraceEndEditData(int eraceNum);
    /// <summary>
    /// ������`��
    /// </summary>
    /// <param name="data"></param>
    virtual void DrawEditString() const = 0;
    /// <summary>
    /// �I�𒆂̕����`��
    /// </summary>
    virtual void DrawSelectString() const = 0;
protected:
    /// <summary>
    /// �I�𕨂̌����ƈʒu���킩��G�t�F�N�g�̍X�V
    /// </summary>
    void UpdateEffect();
    //���ҏW���Ă���I�u�W�F�N�g�̃|�W�V����
    static EditArrangementData nowEditObjData;
    //�ҏW�I���t���O
    bool isEndEdit = true;
    /// <summary>
    /// �����̏�����������
    /// </summary>
    /// <param name="data"></param>
    void SaveEditObjectData(EditArrangementData data)const;
    /// <summary>
    /// �f�[�^�ۑ��t�@�C��
    /// </summary>
    std::string saveFileName;
    /// ���W�A�C�e���̐�
    static int collectNum;  
    /// ���W�A�C�e����������ǂ̃^�C�~���O�ŏo�Ă��邩
    static int missionNum;
    //�I�u�W�F�N�g�̕`��S��
    EditorModelViewer* viewer;
    //�I���G�t�F�N�g
    static int selectAura;
    //������������₷���Ȃ�G�t�F�N�g
    static int dirEffect;
    //�ҏW�ς݃f�[�^
    std::vector<EditArrangementData> editDataVec;
};