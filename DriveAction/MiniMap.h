#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include "DxLib.h"
#include "UIManager.h"

class ObjectObserver;
/// <summary>
/// プレイヤーを中心に近くにアイテムがあるか調べさせる
/// </summary>
class MiniMap
{
public:
    MiniMap(std::shared_ptr<ObjectObserver> player);
    ~MiniMap();
    void Update();
    void Draw()const;
    static void AddMarker(ObjectObserver* obserber);
private:
    static VECTOR ConvertPosition(VECTOR pos);
    //プレイヤーのマーカーの色
    const unsigned int playerColor = GetColor(255,0,0);
    //収集物の色
    const unsigned int coinColor = GetColor(200,0,200);
    
    //自機のIconの大きさ
    static const int iconSize = 5;
    //ミニマップの画像の横幅
    static int mapGraphWidth;
    //ミニマップの画像の縦幅
    static int mapGraphHeight;
    //マップの大きさ
    static const float mapSize;
    //収集物の位置の縮尺
    static const float collectBetween;
    //マップの大きさの係数
    static float mapSizeCoefficient;
    //回転度合い
    float mapRotate = 0;
    //ミニマップ
    static UIData miniMap;
    std::weak_ptr<ObjectObserver> playerObserver;

    static std::list<VECTOR> posList;
    std::list<VECTOR> drawPosList;
};