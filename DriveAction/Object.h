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
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    Object()
    {
    };
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <returns></returns>
    virtual ~Object() {};

    /// <summary>
    /// 現在動けるかどうか
    /// </summary>
    /// <returns></returns>
    Object::ObjectState GetObjectState() const
    {
        return objState;
    };
    /// <summary>
    /// ポジション所得
    /// </summary>
    /// <returns></returns>
    VECTOR GetPos()const
    {
        return position;
    };
    /// <summary>
    /// objectの半径
    /// </summary>
    /// <returns></returns>
    float GetRadius() const
    {
        return radius;
    }
    //跳ね返す力を返す
    float GetBouncePower()
    {
        return bouncePower;
    }
    /// <summary>
    /// 向き所得
    /// </summary>
    /// <returns></returns>
    VECTOR GetDir() const
    {
        return direction;
    };
    /// <summary>
    /// 自分のタグを返す
    /// </summary>
    /// <returns></returns>
    ObjectTag GetTag() const
    {
        return tag;
    };

protected:
    //半径
    float radius = 0;
    //跳ね返す力
    float bouncePower = 0;
    //生存フラグ
    ObjectState objState = sleep;
    //自分が何なのか
    ObjectTag tag = ObjectTag::stage;
    //方向
    VECTOR direction = {1,0,0};
    //場所
    VECTOR position = {};
};