#pragma once
#include <iostream>
#include <memory>
#include <list>
#include "ActorController.h"
#include "DxLib.h"
/// <summary>
/// ���W�A�C�e���̑���
/// </summary>
class CollectController final : public ActorController
{
public:
    /// <summary>
    /// �R�C����\��New���čő喇����ۑ�
    /// </summary>
    CollectController();
    /// <summary>
    /// actorList�̐擪�̎��W�A�C�e�������X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// ���W�A�C�e���̕`��
    /// </summary>
    void Draw()const override;
    /// <summary>
    /// �Q�[�����n�܂�O�̏���
    /// </summary>
    void PrepareGame()override;
    /// <summary>
    /// �����̏ꏊ�Ǝ��W�A�C�e���̈ʒu�̋����x�N�g�����o��
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    static VECTOR GetCollectItemBetween(VECTOR pos);
    /// <summary>
    /// ���W�A�C�e���������Ă��邩
    /// </summary>
    /// <returns></returns>
    static bool IsActiveCollect();
    /// <summary>
    /// �v���C���[���W�߂Ȃ���΂����Ȃ��A�C�e���̐�
    /// </summary>
    /// <returns></returns>
    static int GetTotalCollectNum();
    /// <summary>
    /// �c���Ă���A�C�e���̐�
    /// </summary>
    /// <returns></returns>
    static int GetRemainingCollectNum();
    /// <summary>
    /// �v���C���[�����W�A�C�e�����W�ߏI������
    /// </summary>
    /// <returns></returns>
    static bool IsEndingMission();
    /// <summary>
    /// �S�A�C�e�����j�󂳂ꂽ��
    /// </summary>
    static bool IsDestroyAllItem();
private:
    //���W�A�C�e���������Ă��邩
    static bool isActive;
    //���W�A�C�e�����S��Delete���ꂽ��
    static bool isDestroyAll;
    //���W�A�C�e�������I�����
    static bool isGameEnd;
    //���W�A�C�e���̍ő吔
    static int totalCollectNum;
    //�������ꂽ�A�C�e���̐�
    static int remainingCollectNum;
    /// ���ݓ����Ă�����W�A�C�e���̈ʒu
    static VECTOR nowActiveCollectItemPos;
};
