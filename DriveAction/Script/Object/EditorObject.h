#pragma once
#include <iostream>
#include <memory>
#include "Object.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
class CameraObserver;
/// <summary>
/// �G�f�B�^��ŕ\������I�u�W�F�N�g
/// </summary>
class EditorObject : public Object
{
public:
    /// <summary>
    /// �ҏW���������̂������ɉ�����
    /// </summary>
    EditorObject();
    /// <summary>
    /// �e�I�u�W�F�N�g�𓮂��������]�������肷��
    /// </summary>
    void Update(std::weak_ptr<CameraObserver> cameraObserever);
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
    void ReflectInput(std::weak_ptr<CameraObserver> cameraObserever);
    //��]���x
    static const int rotaSpeed;
    //�ړ����x
    static const int moveSpeed;
};