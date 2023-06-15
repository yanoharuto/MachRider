#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class ObjectObserver;
/// <summary>
/// �V��ł���Ƃ��̃J����
/// </summary>
class RaceCamera final : Camera
{
public:
    RaceCamera(std::shared_ptr<ObjectObserver> player);
    ~RaceCamera() override;
    void Update();
private:
    //�v���C���[�̈ʒu�������Ă������
    std::weak_ptr<ObjectObserver> playerObserver;
};

