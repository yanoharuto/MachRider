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
    /// <summary>
    /// �J�����ɕK�v�ȃp�����[�^
    /// </summary>
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
    /// <summary>
    /// �J�������g����V�[���̎��
    /// </summary>
    enum UseCameraSceneKind
    {
        //�^�C�g���V�[���̃J����
        title = 2,
        //�V��ł鎞�̃J����
        game = 5,
        //���U���g��ʂł̃J����
        editor = 8
    };
}
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
    Camera(InitCamera::UseCameraSceneKind type);
    /// <summary>
    /// �����̂��̂��J�����͈͓̔������ׂ�
    /// </summary>
    /// <param name="actor">���ׂ����I�u�W�F�N�g</param>
    /// <returns>�J�����͈͓̔��Ȃ�True</returns>
    bool IsLookingCamera(const Actor* const actor) const;
protected:
    /// <summary>
    /// �J�����̃p�����[�^����ǂݎ��
    /// </summary>
    /// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
    void LoadData(InitCamera::UseCameraSceneKind type);
    //���������̂̈ʒu���������Ă������
    std::weak_ptr<ObjectObserver> targetObserver;
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
    float targetBetweenSize;
    //����
    float posY;
    //�J�����̒ǂ������x
    float cameraSpeed;
    //�J�����̌�����͈͊p
    static float lookingDeg;
};