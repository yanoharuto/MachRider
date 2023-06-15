#pragma once
#include "ActorController.h"
#include "DxLib.h"
class Coin;
class ObjectSubject;
/// <summary>
/// 位置をミニマップに教えたりする
/// </summary>
class CollectController final:public ActorController
{
public:
    /// <summary>
    /// コインの設置
    /// </summary>
    CollectController(VECTOR generatePos);
    void Update()override;

private:
    ObjectSubject* subject;
};
