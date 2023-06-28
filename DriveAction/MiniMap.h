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
    MiniMap(std::weak_ptr<ObjectObserver> player);
    ~MiniMap();
    /// <summary>
    /// ミニマップに表示するマーカーの位置を更新
    /// </summary>
    void Update();
    /// <summary>
    /// マップに表示する点とレーダーの枠
    /// </summary>
    void Draw()const;
    /// <summary>
    /// マップに反映させたいアイテムの追加
    /// </summary>
    /// <param name="obserber"></param>
    static void AddMarker(ObjectObserver* obserber);
private:
    /// <summary>
    /// ゲームの３D マップのサイズに合わせて
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    static VECTOR ConvertPosition(VECTOR pos);
    //プレイヤーのマーカーの色
    const unsigned int playerColor = GetColor(255,0,0);
    //収集物の色
    const unsigned int coinColor = GetColor(0,115,255);
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
    //マップの中心軸にする
    std::weak_ptr<ObjectObserver> playerObserver;
    //マーカーの位置を更新するためのリスト
    static std::list<ObjectObserver*> markerObserverList;
    //描画位置のリスト
    std::list<VECTOR> drawPosList;
};