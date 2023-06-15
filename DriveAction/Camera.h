#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>
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
        setYBetween = 14,
        //�J�����̈ړ����x
        setCameraSpeed = 17,
    };
    enum CameraType
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
    Camera(InitCamera::CameraType type);
    virtual ~Camera();
    bool IsLookingCamera(const Actor* const actor) const;
 
protected:
    void LoadData(InitCamera::CameraType type);
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
};