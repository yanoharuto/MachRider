#pragma once
namespace ObjectInit
{
    /// <summary>
    /// 初期化するオブジェクトの種類
    /// </summary>
    enum InitObjKind
    {
        //プレイヤー機
        player = 2,
        //大きい岩
        moveSaw = 5,
        //回転丸鋸
        saw = 8,
        //爆撃機
        bomberShip = 11,
        //爆弾
        bomber = 14,
        //上下にレーザー撃つ飛行船
        upDownLaserShip = 17,
        //円状に並ぶ機体
        circleLaserShip = 20,
        //レーザー
        laser = 23,
        //コイン
        collect = 26,
        //床
        stageFloor = 29,
        //スカイドーム
        skyDome = 32,
        //ステージの外に出ないようにする壁
        wall = 35
    };
}