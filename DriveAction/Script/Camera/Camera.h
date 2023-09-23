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
    /// カメラに必要なパラメータ
    /// </summary>
    enum class CameraParameter
    {
        //描画範囲の開始距離
        setNearValue = 2,
        //描画範囲の最終距離
        setFarValue = 5,
        //オブジェクトの見える範囲角
        setLookingAngle = 8,
        //描画対象との距離
        setTargetBetween = 11,
        //カメラのY距離
        setYPosition = 14,
        //カメラの移動速度
        setCameraSpeed = 17,
    };
    /// <summary>
    /// カメラが使われるシーンの種類
    /// </summary>
    enum class UseCameraSceneKind
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
    /// <summary>
    /// カメラの向きを所得
    /// </summary>
    /// <returns>カメラの向きベクトル</returns>
    VECTOR GetNormDirection()const;
    /// <summary>
    /// カメラの位置を所得
    /// </summary>
    /// <returns>カメラの座標</returns>
    VECTOR GetPosition()const;
    /// <summary>
    /// 見える角度を所得
    /// </summary>
    /// <returns></returns>
    float GetLookingAngle()const;
protected:
    /// <summary>
    /// カメラのパラメータ等を読み取る
    /// </summary>
    /// <param name="type">シーンによってカメラの性能を変える</param>
    void LoadData(InitCamera::UseCameraSceneKind type);
    //見たいものの位置等を教えてくれるやつ
    std::weak_ptr<ObjectObserver> targetObserver;
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
    float targetBetweenSize;
    //高さ
    float posY;
    //カメラの追いつく速度
    float cameraSpeed;
    //カメラの見える範囲角
    static float lookingAngle;
};