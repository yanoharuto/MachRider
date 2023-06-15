#pragma once
#include <string>
#include "Actor.h"
#include "SphereCollider.h"
#include "ObjPosAndDir.h"
/// <summary>
/// 収集アイテム
/// </summary>
class Coin :
    public Actor
{
public:
    /// <summary>
    /// 初期位置を教えて
    /// </summary>
    /// <param name="firstPos"></param>
    Coin(VECTOR firstPos);
    ~Coin();
    /// <summary>
    /// 更新
    /// </summary>
    void Update();
    /// <summary>
    /// ぶつかった時の処理
    /// </summary>
    /// <param name="conflictInfo"></param>
    void ConflictProccess(const ConflictExamineResultInfo conflictInfo);
    void GameReserve()override;
    /// <summary>
    /// ちょっと影を変更して描画
    /// </summary>
    void Draw() const override;
private:
    
    //毎秒向きがこの値分変化する
    static const float rotateY;
    //縦方向に移動する量
    static const float moveYValue;
    //縦方向に移動する速度
    static const float moveYSpeed;
    //最初の高さ
    float firstY;
    //回転量
    float totalMoveYValue = 0;
    //球当たり判定
    SphereCollider* collider;
    //車にぶつかった
    bool isCarConflict = false;
    //プレイヤーがコインをゲットしたときのエフェクト
    int coinGetEffect = -1;
    //コインの出すオーラ
    int coinAuraEffect = -1;
};

