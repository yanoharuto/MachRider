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
enum EditArrangementDataKind
{
    objectKindNum = 0,
    missionTurnNum = 1,
    positionX = 2,
    positionZ = 3,
    directionX = 4,
    directionZ = 5,
};
//初期化データの種類の数
#define EDIT_ARRANGEMENT_DATA_KIND_NUM 6