#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "Camera.h"
class ObjectObserver;
class Actor;
namespace InitCamera
{
    enum CameraParameter
    {
        //�`��͈͂̊J�n����
        setNearValue = 2,
        //�`��͈͂̍ŏI����
        setFarValue = 5,
        //�I�u�W�F�N�g�̌�����͈͊p
        setLookingDegree = 8,
        //�`��ΏۂƂ̋���
        setTargetBetween = 11,
        //�J������Y����
        setYPosition = 14,
        //�J�����̈ړ����x
        setCameraSpeed = 17,
    };
    enum UseCameraSceneKind
    {
        //�^�C�g���V�[���̃J����
        title = 2,
        //�V��ł鎞�̃J����
        game = 5,
        //���U���g��ʂł̃J����
        result = 8
    };
}
class Camera
{
public:
    /// <summary>
    /// �ǂ̃^�C�~���O�Ŏg����������
    /// </summary>
    /// <param name="type"></param>
    Camera(InitCamera::UseCameraSceneKind type);
    virtual ~Camera();
    /// <summary>
    /// �J�����͈͓̔������ׂ�
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    bool IsLookingCamera(const Actor* const actor) const;
protected:
    /// <summary>
    /// �J�����̃p�����[�^����ǂݎ��
    /// </summary>
    /// <param name="type"></param>
    void LoadData(InitCamera::UseCameraSceneKind type);
    //�������ɕK�v�ȃp�����[�^�[�ւ̃p�X
    std::string initFileName= "data/Camera/CameraInitPass.csv";
    //�J�����̈ʒu
    VECTOR position;
    //�J�����̕���
    VECTOR direction;
    //�`�悵�悤�Ƃ���͈�
    float nearValue;
    //�`�悵�悤�Ƃ���͈�
    float farValue;
    //�^�[�Q�b�g�Ƃ̋���
    float targetBetween;
    //����
    float posY;
    //�J�����̒ǂ������x
    float cameraSpeed;
    //�J���������Ă���͈͊p
    static float lookingDeg;
    //�v���C���[�̈ʒu�������Ă������
    std::weak_ptr<ObjectObserver> targetObserver;
};