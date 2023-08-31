#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class PlayerObserver;
/// <summary>
/// ���W�A�C�e���̕������L���G�t�F�N�g���o��
/// </summary>
class CollectCompass
{
public:
    /// <summary>
    /// �G�t�F�N�g�̓ǂ݂���
    /// </summary>
    /// <param name="player">�v���C���[�̈ʒu�Ȃǂ�Ⴄ���Ƃ��o����I�u�U�[�o�[</param>
    CollectCompass(std::weak_ptr<PlayerObserver> player);
    /// <summary>
    /// �G�t�F�N�g�I��
    /// </summary>
    ~CollectCompass();
    /// <summary>
    /// �G�t�F�N�g�̈ʒu�ƌ�����ݒ�
    /// </summary>
    void Update();
private:
    //�v���C���[�̈ʒu�����������Ă���
    std::weak_ptr<PlayerObserver> playerObserver;
    //�G�t�F�N�g�n���h��
    int compassEffect = -1;
    //�G�t�F�N�g��Y���W
    const float addYPos = 13;
};