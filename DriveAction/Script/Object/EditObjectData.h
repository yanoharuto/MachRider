#pragma once
#include "DxLib.h"
/// <summary>
/// 保存したい情報
/// </summary>
struct PlacementData
{
    //オブジェクトの種類
    int objKind = 0;
    //何番目の収集アイテムのタイミングか
    int collectNum = 0;
    //ポジションX
    float posX = 0;
    //ポジションZ
    float posZ = 0;
    //方向X
    float dirX = 0;
    //方向Z
    float dirZ = 0;
};
/// <summary>
/// 保存したい情報の種類
/// </summary>
enum class EditArrangementDataKind
{
    //保存するオブジェクトの種類
    objectKindNum = 0,
    //出てくるタイミングの収集アイテムの数
    appearCollectNum = 1,
    //初期座標X
    positionX = 2,
    //初期座標Y
    positionZ = 3,
    //初期向きX
    directionX = 4,
    //初期向きZ
    directionZ = 5,
};
//初期化データの種類の数
#define EDIT_ARRANGEMENT_DATA_KIND_NUM 6