#pragma once
#include "ActorController.h"
/// <summary>
/// �ړ������]�̂�����̊Ǘ���
/// </summary>
class MoveSawController :
    public ActorController
{
public:
    /// <summary>
    /// �ړ������]�̂�����̊Ǘ���
    /// </summary>
    MoveSawController();
    /// <summary>
    /// �ړ������]�̂�����̒ǉ�
    /// </summary>
    /// <param name="editData"></param>
    void AddObject(std::vector<EditArrangementData> editData)override;
    /// <summary>
    /// �X�V�B�@�j�󂳂ꂽ��j��
    /// </summary>
    void Update()override;
};

