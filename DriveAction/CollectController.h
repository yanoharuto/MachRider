#pragma once
#include <iostream>
#include <memory>
#include <list>
#include "ActorController.h"
#include "DxLib.h"
class Coin;
class ObjectSubject;
class ObjectObserver;
/// <summary>
/// ���W�A�C�e���̑���
/// </summary>
class CollectController final:public ActorController
{
public:
    /// <summary>
    /// �R�C���̐ݒu
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
    void GameReserve()override;
    /// <summary>
    /// �����̏ꏊ�Ǝ��W�A�C�e���̈ʒu�̋����x�N�g�����o��
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    static VECTOR GetBetween(VECTOR pos);
    /// <summary>
    /// ���W�A�C�e���������Ă��邩
    /// </summary>
    /// <returns></returns>
    static bool IsActiveCollect();
    /// <summary>
    /// �v���C���[���W�߂Ȃ���΂����Ȃ��A�C�e���̐�
    /// </summary>
    /// <returns></returns>
    static int TotalCollectNum();
    /// <summary>
    /// �c���Ă���A�C�e���̐�
    /// </summary>
    /// <returns></returns>
    static int GetRemainingCollectNum();
    /// <summary>
    /// �v���C���[���W�߂Ȃ���΂����Ȃ��A�C�e���̎c���Ă��鐔
    /// </summary>
    /// <returns></returns>
    static bool IsEndingChallenge();
private:

    /// �ʒu�Ȃǂ�������N���X�̃��X�g
    std::list<ObjectSubject*> subjectList;
    //���W�A�C�e���������Ă��邩
    static bool isActive;
    //���W�A�C�e�������I�����
    static bool isChallengeEnd;
    //���W�A�C�e���̍ő吔
    static int totalCollectNum;
    //�������ꂽ�A�C�e���̐�
    static int remainingCollectNum;
    /// ���ݓ����Ă�����W�A�C�e���̈ʒu
    static VECTOR nowActiveCollectItemPos;
};
