#pragma once
#include "DxLib.h"
#include "Object.h"
class ConflictProccesor;

/// <summary>
/// 観察対象 Observerに情報が入るようにする
/// </summary>
class ObjectSubject
{
public:
    /// <summary>
    /// 観察対象 Observerに情報が入るようにする
    /// </summary>
    ObjectSubject(Object* setObj);
    ObjectSubject(Object* setObj, ConflictProccesor* setConProccesor);
    ~ObjectSubject();
    /// <summary>
    /// オブジェクトの場所
    /// </summary>
    /// <returns></returns>
    VECTOR GetObjPos();
    /// <summary>
    /// オブジェクトの向き
    /// </summary>
    /// <returns></returns>
    VECTOR GetObjDir();
    /// <summary>
    /// オブジェクトの種類
    /// </summary>
    /// <returns></returns>
    Object::ObjectTag GetObjTag();
    /// <summary>
    /// オブジェクトの状態
    /// </summary>
    /// <returns></returns>
    Object::ObjectState GetObjectState();
    /// <summary>
    /// 引数のタグのオブジェクトに何回ぶつかったか
    /// </summary>
    /// <returns></returns>
    int GetTagObjectHitCount(Object::ObjectTag hitObjTag);

    
private:
    //観察対象のオブジェクト
    Object* subObject;
    //subObjectの当たり判定
    ConflictProccesor* subCollider;
};