#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>
class Actor;
namespace InitCamera
{
    enum CameraParameter
    {
        //描画範囲の開始距離
        setNearValue = 2,
        //描画範囲の最終距離
        setFarValue = 5,
        //オブジェクトの見える範囲角
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
    Camera(InitCamera::CameraType type);
    virtual ~Camera();
    bool IsLookingCamera(const Actor* const actor) const;
 
protected:
    void LoadData(InitCamera::CameraType type);
    //初期化に必要なパラメーターへのパス
    std::string initFileName= "data/Camera/CameraInitPass.csv";
    //カメラの位置
    VECTOR position;
    //カメラの方向
    VECTOR direction;
    //描画しようとする範囲
    float nearValue;
    //描画しようとする範囲
    float farValue;
    //ターゲットとの距離
    float targetBetween;
    //高さ
    float posY;
    //カメラの追いつく速度
    float cameraSpeed;
    //カメラが見ている範囲角
    static float lookingDeg;
};