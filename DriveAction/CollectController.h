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
/// 収集アイテムの操作
/// </summary>
class CollectController final:public ActorController
{
public:
    /// <summary>
    /// コインの設置
    /// </summary>
    CollectController();
    /// <summary>
    /// actorListの先頭の収集アイテムだけ更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 収集アイテムの描画
    /// </summary>
    void Draw()const override;
    /// <summary>
    /// ゲームが始まる前の処理
    /// </summary>
    void GameReserve()override;
    /// <summary>
    /// 引数の場所と収集アイテムの位置の距離ベクトルを出す
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    static VECTOR GetBetween(VECTOR pos);
    /// <summary>
    /// 収集アイテムが動いているか
    /// </summary>
    /// <returns></returns>
    static bool IsActiveCollect();
    /// <summary>
    /// プレイヤーが集めなければいけないアイテムの数
    /// </summary>
    /// <returns></returns>
    static int GetTotalCollectNum();
    /// <summary>
    /// 残っているアイテムの数
    /// </summary>
    /// <returns></returns>
    static int GetRemainingCollectNum();
    /// <summary>
    /// プレイヤーが集めなければいけないアイテムの残っている数
    /// </summary>
    /// <returns></returns>
    static bool IsEndingChallenge();
private:

    /// 位置などを教えるクラスのリスト
    std::list<ObjectSubject*> subjectList;
    //収集アイテムが生きているか
    static bool isActive;
    //収集アイテムを取り終わった
    static bool isChallengeEnd;
    //収集アイテムの最大数
    static int totalCollectNum;
    //所得されたアイテムの数
    static int remainingCollectNum;
    /// 現在動いている収集アイテムの位置
    static VECTOR nowActiveCollectItemPos;
};
