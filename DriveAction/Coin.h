#pragma once
#include <string>
#include "Actor.h"
#include "EditorObject.h"
class ConflictProcessor;
class SphereCollider;
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
    Coin(EditArrangementData arrangementData);
    ~Coin();
    /// <summary>
    /// 更新
    /// </summary>
    void Update();
    /// <summary>
    /// ぶつかった時の処理
    /// </summary>
    /// <param name="conflictInfo"></param>
    void ConflictProcess(const ConflictExamineResultInfo conflictInfo) override;
    /// <summary>
    /// Update関数と同じことをする
    /// </summary>
    void GameReserve()override;
private:
    /// <summary>
    /// 上下に回転しながら移動
    /// </summary>
    void MoveAndRotate();
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
    //衝突処理実行役
    ConflictProcessor* conflictProcessor;
};