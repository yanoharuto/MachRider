#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>
class Actor;
namespace InitParamater
{
    enum CameraParameter
    {
        //描画範囲の開始距離
        setNearValue = 2,
        //描画範囲の最終距離
        setFarValue = 5,
        //オブジェクトの見える範囲
        setLookingDegree = 8,
        //描画対象との距離
        setTargetBetween = 11,
        //カメラのY距離
        setYBetween = 14,
        //カメラの移動速度
        setCameraSpeed = 17,
    };
    enum CameraType
    {
        //タイトルシーンのカメラ
        title = 2,
        //遊んでる時のカメラ
        game = 5,
        //リザルト画面でのカメラ
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
    //カメラの位置
    static std::unordered_map<VECTOR*,VECTOR*> cameraPosDir;
    std::string initFileName= "data/Camera/CameraInitPass.csv";
    //カメラの位置
    VECTOR position;
    //カメラの方向
    VECTOR direction;
    //ポジションのポインター
    VECTOR* pPosition; 
    //方向のポインター
    VECTOR* pDirection;
    //描画しようとする範囲
    float nearValue;
    //描画しようとする範囲
    float farValue;
    float targetBetween;
    float posY;
    float cameraSpeed;
    static float lookingDeg;
};