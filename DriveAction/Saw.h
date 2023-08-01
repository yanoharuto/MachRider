#pragma once
#include "Actor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
using namespace ObjectInit;
class SphereCollider;
/// <summary>
/// ��Q���@�i�ۂ̂��j
/// </summary>
class Saw :
    public Actor
{
public:
    /// <summary>
    /// �����̏ꏊ�ɐݒu����
    /// </summary>
    /// <param name="arrangementData">�ҏW�f�[�^</param>
    Saw(EditArrangementData arrangementData);
    /// <summary>
    /// �����蔻�����
    /// </summary>
    ~Saw()override;
    /// <summary>
    /// ��]������
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update() override;
protected:
    //��]��
    const float addRotate = 20.0f;
    //�͂����Ԃ���
    const float setBouncePower = 4.0f;
    //����
    const float thickness = 5.0f;
    //�����蔻��
    SphereCollider* collider;
};