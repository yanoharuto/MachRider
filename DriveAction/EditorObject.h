#pragma once
#include "Object.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
/// <summary>
/// �G�f�B�^��ŕ\������I�u�W�F�N�g
/// </summary>
class EditorObject :
    public Object
{
public:
    /// <summary>
    /// �ҏW���������̂������ɉ�����
    /// </summary>
    EditorObject();
    ~EditorObject();
    /// <summary>
    /// �e�I�u�W�F�N�g�𓮂��������]�������肷��
    /// </summary>
    void Update()override;
    /// <summary>
    /// �`��ɕK�v�ȍ\���̂�n��
    /// </summary>
    /// <returns>�ʒu�ƌ����ƕ`�悵�����I�u�W�F�N�g�̎��</returns>
    PlacementData GePlacementData()const;
    /// <summary>
    /// �����̔z�u�������p���ʒu��ς���
    /// </summary>
    /// <param name="setData">�z�u</param>
    void SetArrangementData(PlacementData setData);
protected:
    /// <summary>
    /// ���͂𔽉f���Ĉړ��Ɖ�]���X�V
    /// </summary>
    void ReflectInput();
  
    //��]���x
    static const int rotaSpeed = 2;
    //�ړ����x
    static const int moveSpeed = 5;
};