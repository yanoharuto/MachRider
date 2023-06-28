#pragma once
#include <iostream>
#include<memory>
class ObjectObserver;
/// <summary>
/// 音を聞いているオブジェクトの場所を更新
/// </summary>
class SoundListener
{
public:
    /// <summary>
    /// 音を聞くやつのポインターを貰う
    /// </summary>
    /// <param name="listener"></param>
     SoundListener(std::weak_ptr<ObjectObserver> listener);
     ~SoundListener();
    /// <summary>
    /// リスナーの位置を反映
    /// </summary>
    void Update();
private:
    
    //音を聞いているオブジェクト
    std::weak_ptr<ObjectObserver> listener;
};

