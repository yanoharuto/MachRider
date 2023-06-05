#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>
class Actor;
namespace InitParamater
{
    enum CameraParameter
    {
        //�`��͈͂̊J�n����
        setNearValue = 2,
        //�`��͈͂̍ŏI����
        setFarValue = 5,
        //�I�u�W�F�N�g�̌�����͈�
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
    Camera(InitParamater::CameraType type);
    virtual ~Camera();
    static bool IsLookingCamera(const Actor* actor);
 
protected:
    void LoadData(InitParamater::CameraType type);
    //�J�����̈ʒu
    static std::unordered_map<VECTOR*,VECTOR*> cameraPosDir;
    std::string initFileName= "data/Camera/CameraInitPass.csv";
    //�J�����̈ʒu
    VECTOR position;
    //�J�����̕���
    VECTOR direction;
    //�|�W�V�����̃|�C���^�[
    VECTOR* pPosition; 
    //�����̃|�C���^�[
    VECTOR* pDirection;
    //�`�悵�悤�Ƃ���͈�
    float nearValue;
    //�`�悵�悤�Ƃ���͈�
    float farValue;
    float targetBetween;
    float posY;
    float cameraSpeed;
    static float lookingDeg;
};