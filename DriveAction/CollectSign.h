#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class ObjectObserver;
class Timer;
class CollectSign
{
public:
    CollectSign(std::weak_ptr<ObjectObserver> player);
    void Update();
    void Draw()const;
    
private:
    std::weak_ptr<ObjectObserver> playerObserver;
    //���W�A�C�e���̃}�[�J�[
    UIData collectSignData;
    UIData markerAllowData;
    Timer* signTimer; 
    float degree;
    float signScale;

    bool drawIcon;
};