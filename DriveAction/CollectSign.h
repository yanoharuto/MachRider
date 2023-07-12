#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class ObjectObserver;
/// <summary>
/// ���W�A�C�e���̕������L���G�t�F�N�g���o��
/// </summary>
class CollectSign
{
public:

    CollectSign(std::weak_ptr<ObjectObserver> player);
    ~CollectSign();
    /// <summary>
    /// �G�t�F�N�g�̈ʒu�ƌ�����ݒ�
    /// </summary>
    void Update();
private:
    //�v���C���[�̈ʒu�����������Ă���
    std::weak_ptr<ObjectObserver> playerObserver;
    //�G�t�F�N�g�n���h��
    int signEffect;
    //�G�t�F�N�g��Y���W
    const float addYPos=30;
};