#pragma once
#include "DxLib.h"

class Object
{
public:
    enum ObjectTag
    {
        player,
        coin,
        damageObject,
        obstacle,
        stage,
        goal,
        acelerationFloor,
        countSystem
    };
    enum ObjectState
    {
        sleep,
        alive,
        dead
    };
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <returns></returns>
    Object()
    {
    };
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <returns></returns>
    virtual ~Object() {};

    /// <summary>
    /// ���ݓ����邩�ǂ���
    /// </summary>
    /// <returns></returns>
    Object::ObjectState GetObjectState() const
    {
        return objState;
    };
    /// <summary>
    /// �|�W�V��������
    /// </summary>
    /// <returns></returns>
    VECTOR GetPos()const
    {
        return position;
    };
    /// <summary>
    /// object�̔��a
    /// </summary>
    /// <returns></returns>
    float GetRadius() const
    {
        return radius;
    }
    //���˕Ԃ��͂�Ԃ�
    float GetBouncePower()
    {
        return bouncePower;
    }
    /// <summary>
    /// ��������
    /// </summary>
    /// <returns></returns>
    VECTOR GetDir() const
    {
        return direction;
    };
    /// <summary>
    /// �����̃^�O��Ԃ�
    /// </summary>
    /// <returns></returns>
    ObjectTag GetTag() const
    {
        return tag;
    };

protected:
    //���a
    float radius = 0;
    //���˕Ԃ���
    float bouncePower = 0;
    //�����t���O
    ObjectState objState = sleep;
    //���������Ȃ̂�
    ObjectTag tag = ObjectTag::stage;
    //����
    VECTOR direction = {1,0,0};
    //�ꏊ
    VECTOR position = {};
};