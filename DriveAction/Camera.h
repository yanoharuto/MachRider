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
        //描画範囲の開始距離
        setNearValue = 2,
        //描画範囲の最終距離
        setFarValue = 5,
        //オブジェクトの見える範囲角
        setLookingDegree = 8,
        //描画対象との距離
        setTargetBetween = 11,
        //カメラのY距離
        setYPosition = 14,
        //カメラの移動速度
        setCameraSpeed = 17,
    };
    enum UseCameraSceneKind
    {
        //タイトルシーンのカメラ
        title = 2,
        //遊んでる時のカメラ
        game = 5,
        //リザルト画面でのカメラ
        editor = 8
    };
}
/// <summary>
/// カメラ
/// </summary>
class Camera abstract
{
public:
    /// <summary>
    /// カメラの速度や高さの初期化
    /// </summary>
    /// <param name="type">どのタイミングで使うか教えて</param>
    Camera(InitCamera::UseCameraSceneKind type);
    virtual ~Camera();
    /// <summary>
    /// カメラの範囲内か調べる
    /// </summary>
    /// <param name="actor">調べたいオブジェクト</param>
    /// <returns></returns>
    bool IsLookingCamera(const Actor* const actor) const;
protected:
    /// <summary>
    /// カメラのパラメータ等を読み取る
    /// </summary>
    /// <param name="type">シーンによってカメラの性能を変える</param>
    void LoadData(InitCamera::UseCameraSceneKind type);
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
    //見たいものの位置等を教えてくれるやつ
    std::weak_ptr<ObjectObserver> targetObserver;
};