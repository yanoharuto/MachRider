#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
#include "DxLib.h"
class DemoCar;
class Timer;
class ObjectObserver;
/// <summary>
/// タイトルで走らせる
/// </summary>
class DemoCarController :
    public ActorController
{
public:
    /// <summary>
    /// タイトルで走らせる車
    /// </summary>
    /// <param name="setPos"></param>
    /// <param name="setDir"></param>
    DemoCarController(VECTOR setPos,VECTOR setDir);
    ~DemoCarController()override;
    /// <summary>
    /// 車の移動
    /// </summary>
    void Update()override;
    /// <summary>
    /// 今動いているかどうか
    /// </summary>
    /// <returns></returns>
    bool IsAlive()const override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()const override;
    /// <summary>
    /// 位置の初期化
    /// </summary>
    void InitPosition();
    /// <summary>
    /// 車の位置などをカメラなどに渡せるようにする
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<ObjectObserver> CreateCarObserver();
private:
    //タイトルで走る車
    DemoCar* demoCar;
    //車の位置などを伝える
    std::shared_ptr<ObjectObserver> observer;
};