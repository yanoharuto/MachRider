#pragma once
#include "ModelViewer.h"
#include "EditObjectData.h"
class EditorObject;
/// <summary>
/// �e�ҏW�I�u�W�F�N�g�̕`��S����
/// </summary>
class EditorModelViewer:public ModelViewer
{
public:
    /// <summary>
    /// �e�ҏW�I�u�W�F�N�g�̕`��S����
    /// </summary>
    EditorModelViewer(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �����̏ꏊ�ɕ`��
    /// </summary>
    /// <param name="data"></param>
    virtual void Draw(EditArrangementData data)const;
    /// <summary>
    /// �ҏW�҂��I�����Ă��镨�̕\���@�኱��ɏオ��
    /// </summary>
    /// <param name="data"></param>
    virtual void SelectDraw(EditArrangementData data)const;
protected:

    /// <summary>
    /// �`�惂�f���̍s����Z�b�g
    /// </summary>
    /// <param name="dir"></param>
    void ModelSetMatrix(VECTOR dir) const;
    //�I������Ă���Ȃ炿����ƈʒu�������Ȃ�
    const int selectPosY = 75;
    //model�̃T�C�Y
    float mSize = 0;
};