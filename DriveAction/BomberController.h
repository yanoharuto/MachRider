#pragma once
#include "DamageObjectController.h"
#include <vector>
class ObjectSubject;
class ObjectObserver;
/// <summary>
/// 爆弾の更新役
/// </summary>
class BomberController :
    public DamageObjectController
{
public:
    /// <summary>
    /// 爆弾の更新役
    /// </summary>
    BomberController() ;
    /// <summary>
    /// 爆弾を更新できるようにする
    /// </summary>
    /// <param name="sub">爆弾を投下したオブジェクト</param>
    void AddObject(std::unique_ptr<ObjectObserver> sub)override;
private:
   
};

