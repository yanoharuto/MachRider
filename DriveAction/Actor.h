#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "InitObjKind.h"

/// <summary>
/// 描画するオブジェクト
/// </summary>
class Actor abstract:
    public Object
{
public:
    Actor() ;
    Actor(ObjectInit::InitObjKind kind);
    virtual ~Actor()
    {
    };
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() {};
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() const;
    
    /// <summary>
    /// 衝突処理
    /// </summary>
    virtual void ConflictProccess(const ConflictExamineResultInfo conflictInfo) {};
    /// <summary>
    /// 速度所得
    // </summary>
    /// <returns></returns>
    VECTOR GetVelocity();
    /// <summary>
    /// 当たり判定で当たってたら渡す情報
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo();

protected:
    /// <summary>
    /// 他のオブジェクトに当たってるか調べる用の情報
    /// </summary>
    /// <returns></returns>
    ArgumentConflictResultInfo GetConflictArgumentInfo();
    /// <summary>
    /// 描画モデルの行列をセット
    /// </summary>
    virtual void ModelSetMatrix() const;
    
    //ポジションの位置に変更する
    virtual void UpdatePosition();
    
    //描画モデル
    int modelHandle;
    //速度
    VECTOR velocity;
    //modelのサイズ
    float modelSize = 1;
};