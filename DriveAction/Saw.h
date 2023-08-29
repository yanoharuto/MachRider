#pragma once
#include "Actor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
using namespace ObjectInit;
class SphereCollider;
class ConflictProcessor;
/// <summary>
/// 障害物　（丸のこ）
/// </summary>
class Saw :
    public Actor
{
public:
    /// <summary>
    /// 引数の場所に設置する
    /// </summary>
    /// <param name="arrangementData">編集データ</param>
    Saw(PlacementData arrangementData);
    /// <summary>
    /// 継承するならこっち
    /// </summary>
    Saw(ObjectInit::InitObjKind kind, PlacementData arrangementData);
    /// <summary>
    /// 当たり判定消去
    /// </summary>
    ~Saw();
    /// <summary>
    /// 回転させる
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update() override;
    /// <summary>
    /// 衝突処理実行 playerにぶつかったら破壊
    /// </summary>
    void OnConflict(const CollisionResultInfo conflictInfo) override;
    
protected:
    /// <summary>
    /// 共通初期化処理
    /// </summary>
    /// <param name="arrangementData"></param>
    void Init(PlacementData arrangementData);
    //回転量
    static const float addRotate;
    //当たり判定
    SphereCollider* collider;
    //衝突処理実行役
    ConflictProcessor* conflictProcessor;
    //破壊爆破エフェクト
    int breakExplosionEffect = -1;
};