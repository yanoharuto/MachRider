#pragma once
#include "ActorController.h"
/// <summary>
/// �v���C���[���͂�����΂��ۋ�
/// </summary>
class SawController :
    public ActorController
{
public:
    /// <summary>
    /// �v���C���[���͂�����΂��ۋ�
    /// </summary>
    SawController();
    /// <summary>
/// �ۋ���ǉ�
/// </summary>
/// <param name="editData">�ǉ�����ʒu�Ȃǂ̏��</param>
    void AddObject(std::vector<PlacementData> editData)override;
    /// <summary>
    /// �X�V�B�@�j�󂳂ꂽ��j��
    /// </summary>
    void Update()override;
};

