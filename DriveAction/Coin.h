#pragma once
#include <string>
#include "Actor.h"
#include "SphereCollider.h"
#include "ObjPosAndDir.h"
/// <summary>
/// ���W�A�C�e��
/// </summary>
class Coin :
    public Actor
{
public:
    /// <summary>
    /// �����ʒu��������
    /// </summary>
    /// <param name="firstPos"></param>
    Coin(VECTOR firstPos);
    ~Coin();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �Ԃ��������̏���
    /// </summary>
    /// <param name="conflictInfo"></param>
    void ConflictProccess(const ConflictExamineResultInfo conflictInfo);
    /// <summary>
    /// ������Ɖe��ύX���ĕ`��
    /// </summary>
    void Draw() const override;
private:
    //���b���������̒l���ω�����
    static const float rotateY;
    //�c�����Ɉړ������
    static const float moveYValue;
    //�c�����Ɉړ����鑬�x
    static const float moveYSpeed;
    //���a
    static const float setRadius;
    //�ŏ��̍���
    static const float firstY;
    //��]��
    float totalMoveYValue = 0;
    //�������蔻��
    SphereCollider* collider;
    //�ԂɂԂ�����
    bool isCarConflict = false;
    //�v���C���[���R�C�����Q�b�g�����Ƃ��̃G�t�F�N�g
    int coinPlayEffect = -1;
};

