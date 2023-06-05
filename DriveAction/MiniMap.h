#pragma once
#include <string>
#include <list>
#include "DxLib.h"
#include "UIManager.h"
class RacerManager;
class ObjectObserver;
class MiniMap
{
public:
    MiniMap(RacerManager* racerManager);
    ~MiniMap();
    void Update(std::list<VECTOR> setCoinPosList);
    void Draw();
private:
    VECTOR ConvertPosition(VECTOR pos);
    //プレイヤーのマーカーの色
    const unsigned int playerColor = GetColor(255,0,0);
    //収集物の色
    const unsigned int coinColor = GetColor(200,0,200);
    
    //自機のIconの大きさ
    const int iconSize = 5;
    //ミニマップの画像の横幅
    int mapGraphWidth = 0;
    //ミニマップの画像の縦幅
    int mapGraphHeight = 0;
    //マップの大きさ
    const float mapSize = 420;
    //収集物の縮尺
    const float collectBetween = 0.3f;
    //マップの大きさの係数
    float mapSizeCoefficient = 0;
    //回転度合い
    float mapRotate = 0;
    //ミニマップ
    UIData miniMap;
    ObjectObserver* playerObserver;
    std::list<VECTOR> coinPosList;
};