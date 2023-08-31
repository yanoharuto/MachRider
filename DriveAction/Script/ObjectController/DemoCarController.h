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
class DemoCarController : public ActorController
{
public:
    /// <summary>
    /// タイトルで走らせる車
    /// </summary>
    /// <param name="setPos">初期位置</param>
    /// <param name="setDir">初期向き</param>
    DemoCarController(VECTOR setPos,VECTOR setDir);
    /// <summary>
    /// 走っている車と描画役の開放
    /// </summary>
    ~DemoCarController()override;
    /// <summary>
    /// 車の移動
    /// </summary>
    void Update()override;
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