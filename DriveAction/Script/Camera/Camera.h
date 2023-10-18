#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "Camera.h"
#include "CameraManager.h"
class ObjectObserver;
class Actor;

/// <summary>
/// �J����
/// </summary>
class Camera abstract
{
public:
    /// <summary>
    /// �J�����̑��x�⍂���̏�����
    /// </summary>
    /// <param name="type">�ǂ̃^�C�~���O�Ŏg����������</param>
    Camera(CameraDataLoader::UseCameraSceneKind type);
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns>�J�����̌����x�N�g��</returns>
    VECTOR GetNormDirection()const;
    /// <summary>
    /// �J�����̈ʒu������
    /// </summary>
    /// <returns>�J�����̍��W</returns>
    VECTOR GetPosition()const;
    /// <summary>
    /// ������p�x������
    /// </summary>
    /// <returns></returns>
    float GetLookingAngle()const;
protected:
    /// <summary>
    /// �J�����̃p�����[�^����ǂݎ��
    /// </summary>
    /// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
    void LoadData(CameraDataLoader::UseCameraSceneKind type);
    //���������̂̈ʒu���������Ă������
    std::weak_ptr<ObjectObserver> targetObserver;
    //�J�����̈ʒu
    VECTOR position;
    //�J�����̕���
    VECTOR direction;
    //�`�悵�悤�Ƃ���͈�
    float nearValue;
    //�`�悵�悤�Ƃ���͈�
    float farValue;
    //�^�[�Q�b�g�Ƃ̋���
    float targetBetweenSize;
    //����
    float posY;
    //�J�����̒ǂ������x
    float cameraSpeed;
    //�J�����̌�����͈͊p
    static float lookingAngle;
};