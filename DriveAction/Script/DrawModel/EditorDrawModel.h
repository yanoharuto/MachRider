#pragma once
#include "DrawModel.h"
#include "EditObjectData.h"
class EditorObject;
/// <summary>
/// �e�ҏW�I�u�W�F�N�g�̕`��S����
/// </summary>
class EditorDrawModel:public DrawModel
{
public:
    /// <summary>
    /// �e�ҏW�I�u�W�F�N�g�̕`��S����
    /// </summary>
    EditorDrawModel(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �����̏ꏊ�ɕ`��
    /// </summary>
    /// <param name="data"></param>
    virtual void Draw(PlacementData data)const;
    /// <summary>
    /// �ҏW�҂��I�����Ă��镨�̕\���@�኱��ɏオ��
    /// </summary>
    /// <param name="data"></param>
    virtual void SelectDraw(PlacementData data)const;
protected:

    /// <summary>
    /// �`�惂�f���̍s����Z�b�g
    /// </summary>
    /// <param name="dir"></param>
    void ModelSetMatrix(VECTOR dir) const;
    //�I������Ă���Ȃ炿����ƈʒu�������Ȃ�
    const int selectPosY = 75;
};