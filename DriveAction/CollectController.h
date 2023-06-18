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
/// 位置をミニマップに教えたりする
/// </summary>
class CollectController final:public ActorController
{
public:
    /// <summary>
    /// コインの設置
    /// </summary>
    CollectController();
    void Update()override;
    void Draw()const override;
    /// <summary>
    /// 引数のVectorとのクロス積のY成分
    /// </summary>
    /// <param name="vec"></param>
    /// <returns></returns>
    static float GetCollectItemDegreeDifference(std::weak_ptr<ObjectObserver> observer);
private:
    std::list<ObjectSubject*> subjectList;
    static VECTOR nowActiveCollectItemPos;
};
