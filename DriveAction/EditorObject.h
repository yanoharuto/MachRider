#pragma once
#include "Actor.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
/// <summary>
/// �G�f�B�^��ŕ\������I�u�W�F�N�g
/// </summary>
class EditorObject :
    public Actor
{
public:
    /// <summary>
    /// �ҏW���������̂������ɉ�����
    /// </summary>
    /// <param name="kind"></param>
    EditorObject(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �����ʒu���ŏ����猈�܂��Ă���z
    /// </summary>
    /// <param name="editData"> �ʒu�ƃI�u�W�F�N�g�̎�ނƌ���</param>
    EditorObject(EditArrangementData editData);
    ~EditorObject();
    /// <summary>
    /// �e�I�u�W�F�N�g�𓮂��������]�������肷��
    /// </summary>
    void Update()override;
    /// <summary>
    /// �I�u�W�F�N�g�̈ʒu���]�Ȃǂ�n��
    /// </summary>
    /// <returns></returns>
    EditArrangementData GetEditObjectData()const;
protected:
    /// <summary>
    /// ���͂𔽉f���Ĉړ��Ɖ�]���X�V
    /// </summary>
    void ReflectInput();
    //�I�u�W�F�N�g�̎��
    int objKind = 0;  
    //��]���x
    static const int rotaSpeed = 2;
    //�ړ����x
    static const int moveSpeed = 5;
};